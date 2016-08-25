//  
//  Copyright (c) 2014-2016 CASM Organization
//  All rights reserved.
//  
//  Developed by: Florian Hahn
//                Philipp Paulweber
//                Emmanuel Pescosta
//                https://github.com/ppaulweber/libcasm-fe
//  
//  This file is part of libcasm-fe.
//  
//  libcasm-fe is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//  
//  libcasm-fe is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
//  GNU General Public License for more details.
//  
//  You should have received a copy of the GNU General Public License
//  along with libcasm-fe. If not, see <http://www.gnu.org/licenses/>.
//  

#include "NumericExecutionPass.h"

#include <iostream>
#include <algorithm>
#include <sstream>
#include <cmath>
#include <cassert>
#include <utility>
#include <unistd.h>
#include <sys/wait.h>
#include <cstdio>

#include "../Driver.h"
#include "../Symbols.h"
#include "../Exceptions.h"

using namespace libcasm_fe;

extern Driver *global_driver;

char NumericExecutionPass::id = 0;

static libpass::PassRegistration< NumericExecutionPass > PASS
( "Numeric Execution Pass"
, "execute numerically over the AST input specification"
, "ast-num"
, 0
);

static std::string arguments_to_string(uint32_t num_arguments, const value_t arguments[])
{
    std::stringstream ss;
    if (num_arguments == 0) {
        return "";
    }
    for (uint32_t i = 0; i < num_arguments; i++) {
        ss << arguments[i].to_str();
        ss << ", ";
    }
    // Strip trailing comma
    return "(" + ss.str().substr(0, ss.str().size() - 2) + ")";
}

bool NumericExecutionPass::run(libpass::PassResult& pr)
{
    walker = new NumericExecutionWalker(*this);

    Ast* root = (Ast*)pr.getResult< TypeCheckPass >();
    RuleNode* node = global_driver->rules_map_[ root->getInitRule()->identifier ];

    rule_bindings.push_back(&main_bindings);
    function_states = std::vector<std::unordered_map<ArgumentsKey, value_t>>(global_driver->function_table.size());
    function_symbols = std::vector<const Function*>(global_driver->function_table.size());
    Function *program_sym = global_driver->function_table.get_function("program");
    // TODO location is wrong here
    program_sym->intitializers_ = new std::vector<std::pair<ExpressionBase*, ExpressionBase*>>();
    RuleAtom *init_atom = new RuleAtom(node->location, std::string(node->name));
    init_atom->rule = node;
    program_sym->intitializers_->push_back(std::make_pair(new SelfAtom(node->location), init_atom));

    try
	{
        for( auto pair : global_driver->init_dependencies )
		{
            std::set<std::string> visited;
            if( initialized.count(pair.first) > 0 )
			{
                continue;
            }
            if( not init_function( pair.first, visited ) )
			{
                Function *func = global_driver->function_table.get_function(pair.first);
                std::string cycle = pair.first;
                for( const std::string& dep : visited )
				{
                    cycle = cycle + " => " + dep;
                }
				
                throw RuntimeException
				( func->intitializers_->at(0).second->location
				, "initializer dependency cycle detected: " + cycle
				);
            }
        }
		
        for( auto pair: global_driver->function_table.table_ )
		{
            if( pair.second->type != Symbol::SymbolType::FUNCTION or initialized.count(pair.first) > 0 )
			{
                continue;
            }

            std::set<std::string> visited;
            init_function(pair.first, visited);
        }

        for( List *l : temp_lists )
		{
            l->bump_usage();
        }
        temp_lists.clear();
		
        uint64_t stepCounter = 0;

        Function *program_sym = global_driver->function_table.get_function( "program" );
        const auto& function_map = function_states[program_sym->id];
        const value_t& program_val = function_map.at(ArgumentsKey(nullptr, 0, false));
		
        while( program_val.type != TypeType::UNDEF )
		{
            walker->walk_rule(program_val.value.rule);
            if( dump_updates )
			{
                dumpUpdates();
            }
            applyUpdates();
            ++stepCounter;
        }
		
        std::cout << stepCounter;
        if( stepCounter != 1 )
		{
            std::cout << " steps later..." << std::endl;
        }
		else
		{
            std::cout << " step later..." << std::endl;
        }
    }
	catch( const RuntimeException& ex )
	{
        global_driver->error( ex.getLocation(), std::string( ex.what() ), ex.getErrorCode() );
        return false;
    }
	catch( const ImpossibleException& ex )
	{
        std::cerr << ex.what() << std::endl;
        return false;
    }
	catch( char * e )
	{
        std::cerr << "Abort after catching a string: " << e << std::endl;
        return false;
    }
	
    return true;
}

void NumericExecutionPass::dumpUpdates() const
{
    std::cout << "{";

    bool firstDump = true;

    const auto updateSet = updateSetManager.currentUpdateSet();
    const auto end = updateSet->cend();
    for (auto it = updateSet->cbegin(); it != end; ++it) {
        const Update* update = it->second;
        const Function* function = function_symbols[update->func];

        if (not firstDump) {
          std::cout << ", ";
        }

        std::cout << function->name
                  << arguments_to_string(update->num_args, update->args)
                  << " = " << update->value.to_str();

        firstDump = false;
    }

    std::cout << "}" << std::endl;
}

const value_t NumericExecutionPass::get_function_value(Function *sym,
                                                       uint32_t num_arguments,
                                                       const value_t arguments[])
{
    try {
        return ExecutionPassBase::get_function_value(sym, num_arguments, arguments);
    } catch (const std::out_of_range &e) {
        static value_t undef = value_t();
        return undef;
    }
}

bool NumericExecutionPass::init_function(const std::string& name, std::set<std::string>& visited)
{
    if( global_driver->init_dependencies.count(name) != 0 )
	{
        visited.insert(name);
        const std::set<std::string>& deps = global_driver->init_dependencies[ name ];

		for( const std::string& dep : deps )
		{
            if( visited.count( dep ) > 0 )
			{
                return false;
            }
			else
			{
                if( not init_function( dep, visited ) )
				{
                    return false;
                }
            }
        }
    }

    std::vector<value_t> initializer_args;

    Function *func = global_driver->function_table.get_function( name );

	if( not func )
	{
        return true;
    }
	
    function_states[  func->id ] = std::unordered_map<ArgumentsKey, value_t>( 0 );
    function_symbols[ func->id ] = func;
	
    auto& function_map = function_states[ func->id ];

    if( func->intitializers_ != nullptr )
	{
        for( std::pair<ExpressionBase*, ExpressionBase*> init : *func->intitializers_ )
		{
            uint32_t num_arguments = 0;
            value_t *args = new value_t[10];
			
			if( init.first != nullptr )
			{
                const value_t argument_v = walker->walk_expression_base( init.first );
                if( func->arguments_.size() > 1 )
				{
                    List *list = argument_v.value.list;
                    for( auto iter = list->begin(); iter != list->end(); iter++ )
					{
                        args[ num_arguments ] = *iter;
                        num_arguments += 1;
                    }
                }
				else
				{
                    args[ num_arguments ] = argument_v;
                    num_arguments += 1;
                }
            }
			
            try
			{
                func->validateArguments( num_arguments, args );
            }
			catch( const std::domain_error& e )
			{
                throw RuntimeException
				( init.first->location
				, e.what()
				, libcasm_fe::Codes::FunctionArgumentsInvalidRangeAtInitially
				);
            }
			
            if( function_map.count( ArgumentsKey( args, num_arguments, false ) ) != 0 )
			{
                throw RuntimeException
				( init.first->location
				, "function '" + func->name + arguments_to_string(num_arguments, args) + "' already initialized"
				, libcasm_fe::Codes::FunctionValueAlreadyInitializedAtInitially
				);
            }
			
            const value_t v = walker->walk_expression_base(init.second);
            try
			{
                func->validateValue(v);
            }
			catch( const std::domain_error& e )
			{
                throw RuntimeException
				( init.second->location
				, e.what()
				, libcasm_fe::Codes::FunctionValueInvalidRangeAtInitially
				);
            }
			
            function_map.emplace( std::make_pair( ArgumentsKey( args, num_arguments, true ), v ) );

            initializer_args.push_back( args );
        }
    }

    initialized.insert( name );
    return true;
}


void NumericExecutionPass::visit_assure(UnaryNode* assure, const value_t& val)
{
    visit_assert(assure, val);
}

void NumericExecutionPass::visit_print( PrintNode *node, const value_t& argument )
{
    if( node->getFilter().size() > 0 )
	{
        if( filter_enabled( node->getFilter() ) )
		{
            std::cout << node->getFilter() << ": ";
        } else
		{
            return;
        }
    }
	
    std::cout << argument.to_str() << std::endl;
}

void NumericExecutionPass::visit_push(PushNode *node, const value_t& expr, const value_t& atom)
{
    num_arguments = 0; // TODO at the moment, functions with arguments are not supported

    const value_t to_res = builtins::cons(temp_lists, expr, atom);
    addUpdate(node->to->symbol, to_res, num_arguments, arguments, node->location);
}

void NumericExecutionPass::visit_pop(PopNode *node, const value_t& val)
{
    num_arguments = 0; // TODO at the moment, functions with arguments are not supported

    const value_t to_res = builtins::peek(val);

    if (node->to->symbol_type == FunctionAtom::SymbolType::FUNCTION) {
        addUpdate(node->to->symbol, to_res, num_arguments, arguments, node->location);
    } else {
        rule_bindings.back()->push_back(to_res);
    }

    const value_t from_res = builtins::tail(temp_lists, val);
    addUpdate(node->from->symbol, from_res, num_arguments, arguments, node->location);
}

const value_t NumericExecutionPass::visit_expression(Expression *expr,
                                                     const value_t &left_val,
                                                     const value_t &right_val)
{
    switch (expr->op) {
    case ExpressionOperation::ADD:
        return left_val + right_val;
    case ExpressionOperation::SUB:
        return left_val - right_val;
    case ExpressionOperation::MUL:
        return left_val * right_val;
    case ExpressionOperation::DIV:
        return left_val / right_val;
    case ExpressionOperation::MOD:
        return left_val % right_val;
    case ExpressionOperation::RAT_DIV:
        return rat_div(left_val, right_val);
    case ExpressionOperation::EQ:
        return value_t(left_val == right_val);
    case ExpressionOperation::NEQ:
        return value_t(left_val != right_val);
    case ExpressionOperation::AND:
        return left_val and right_val;
    case ExpressionOperation::OR:
        return left_val or right_val;
    case ExpressionOperation::XOR:
        return left_val ^ right_val;
    case ExpressionOperation::LESSER:
        return left_val < right_val;
    case ExpressionOperation::GREATER:
        return left_val > right_val;
    case ExpressionOperation::LESSEREQ:
        return left_val <= right_val;
    case ExpressionOperation::GREATEREQ:
        return left_val >= right_val;
    default:
        FAILURE();
    }
}

const value_t NumericExecutionPass::visit_expression_single(Expression *expr,
                                                            const value_t &val)
{
    if (val.is_undef()) {
        return value_t();
    }

    switch (expr->op) {
    case ExpressionOperation::NOT:
        return value_t(not val.value.boolean);
    default:
        FAILURE();
    }
}

const value_t NumericExecutionPass::visit_list_atom(ListAtom *atom,
                                                    const std::vector<value_t> &vals)
{
    BottomList *list = new BottomList(vals);
    //context_.temp_lists.push_back(list);
    return value_t(atom->type_, list);
}

template <>
value_t NumericExecutionWalker::walk_list_atom(ListAtom *atom)
{
    std::vector<value_t> expr_results;
    if (atom->expr_list) {
        for (auto iter = atom->expr_list->rbegin(); iter != atom->expr_list->rend(); iter++) {
            expr_results.push_back(walk_expression_base(*iter));
        }
    }
    return visitor.visit_list_atom(atom, expr_results);
}

template <>
void NumericExecutionWalker::walk_ifthenelse(IfThenElseNode* node)
{
    const value_t cond = walk_expression_base(node->condition_);

    if (cond.is_undef()) {
        throw RuntimeException(node->condition_->location,
                               "condition must be true or false but was undef");
    } else if (cond.value.boolean) {
        walk_statement(node->then_);
    } else if (node->else_) {
        walk_statement(node->else_);
    }
}

template <>
void NumericExecutionWalker::walk_seqblock(UnaryNode* seqblock)
{
    visitor.fork(UpdateSet::Type::Sequential);
    visitor.visit_seqblock(seqblock);
    walk_statements(reinterpret_cast<AstListNode*>(seqblock->child_));
    visitor.merge();
}

template <>
void NumericExecutionWalker::walk_parblock(UnaryNode* parblock)
{
    visitor.fork(UpdateSet::Type::Parallel);
    visitor.visit_parblock(parblock);
    walk_statements(reinterpret_cast<AstListNode*>(parblock->child_));
    visitor.merge();
}

template <>
void NumericExecutionWalker::walk_pop(PopNode* node)
{
    const value_t from = walk_function_atom(node->from);
    visitor.visit_pop(node, from);
}

template <>
void NumericExecutionWalker::walk_push(PushNode *node)
{
    const value_t expr = walk_expression_base(node->expr);
    const value_t atom = walk_function_atom(node->to);
    visitor.visit_push(node, expr, atom);
}

template <>
void NumericExecutionWalker::walk_case(CaseNode *node)
{
    const value_t cond = walk_expression_base(node->expr);

    std::pair<AtomNode*, AstNode*> *default_pair = nullptr;
    for (auto& pair : node->case_list) {
        // pair.first == nullptr for default:
        if (pair.first) {
            if (walk_atom(pair.first) == cond) {
                walk_statement(pair.second);
                return;
            }
        } else {
            default_pair = &pair;
        }
    }
    if (default_pair) {
        walk_statement(default_pair->second);
    }
}

template <>
void NumericExecutionWalker::walk_forall(ForallNode *node)
{
    const value_t in_list = walk_expression_base(node->in_expr);

    visitor.fork(UpdateSet::Type::Parallel);

    switch (node->in_expr->type_.t) {
    case TypeType::LIST: {
        List *l =  in_list.value.list;
        for (auto iter = l->begin(); iter != l->end(); iter++) {
            visitor.rule_bindings.back()->push_back(*iter);
            walk_statement(node->statement);
            visitor.rule_bindings.back()->pop_back();
        }
    }   break;
    case TypeType::INTEGER: {
        INTEGER_T end =  in_list.value.integer;
        if (end > 0) {
            for (INTEGER_T i = 0; i < end; i++) {
                visitor.rule_bindings.back()->push_back(value_t(i));
                walk_statement(node->statement);
                visitor.rule_bindings.back()->pop_back();
            }
        } else {
            for (INTEGER_T i = 0; end < i; i--) {
                visitor.rule_bindings.back()->push_back(value_t(i));
                walk_statement(node->statement);
                visitor.rule_bindings.back()->pop_back();
            }
        }
    }   break;
    case TypeType::ENUM: {
        FunctionAtom *func = reinterpret_cast<FunctionAtom*>(node->in_expr);
        if (func->name == func->enum_->name) {
            for (auto pair : func->enum_->mapping) {
                // why is an element with the name of the enum in the map??
                if (func->name == pair.first) {
                    continue;
                }
                value_t v = value_t(pair.second);
                v.type = TypeType::ENUM;
                visitor.rule_bindings.back()->push_back(std::move(v));
                walk_statement(node->statement);
                visitor.rule_bindings.back()->pop_back();
            }
        } else {
            assert(0);
        }
    }   break;
    default:
        assert(0);
    }

    visitor.merge();
}

template <>
void NumericExecutionWalker::walk_iterate(UnaryNode *node)
{
    visitor.fork(UpdateSet::Type::Sequential);

    while (true) {
        visitor.fork(UpdateSet::Type::Parallel);
        walk_statement(node->child_);
        if (visitor.hasEmptyUpdateSet()) {
            visitor.merge(); // to remove the update set from the stack
            break;
        }
        visitor.merge();
    }

    visitor.merge();
}

static void walk_function_arguments(NumericExecutionWalker* walker, std::vector<ExpressionBase*>* arguments)
{
    if (arguments) {
        for (uint16_t i = 0; i < arguments->size(); i++) {
            walker->visitor.arguments[i] = walker->walk_expression_base(arguments->at(i));
        }
        walker->visitor.num_arguments = arguments->size();
    } else {
        walker->visitor.num_arguments = 0;
    }
}

template <>
void NumericExecutionWalker::walk_update(UpdateNode *node)
{
    const value_t expr = walk_expression_base(node->expr_);
    walk_function_arguments(this, node->func->arguments);
    visitor.visit_update(node, expr);
}

template <>
void NumericExecutionWalker::walk_update_dumps(UpdateNode *node)
{
    const value_t expr = walk_expression_base(node->expr_);
    walk_function_arguments(this, node->func->arguments);
    visitor.visit_update_dumps(node, expr);
}

//  
//  Local variables:
//  mode: c++
//  indent-tabs-mode: t
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//  
