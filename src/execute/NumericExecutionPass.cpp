//
//  Copyright (c) 2014-2016 CASM Organization
//  All rights reserved.
//
//  Developed by: Florian Hahn
//                Philipp Paulweber
//                Emmanuel Pescosta
//                https://github.com/casm-lang/libcasm-fe
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

#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <sys/wait.h>
#include <unistd.h>
#include <utility>

#include "../Driver.h"
#include "../Exceptions.h"
#include "../Symbols.h"

using namespace libcasm_fe;

extern Driver* global_driver;

char NumericExecutionPass::id = 0;

static libpass::PassRegistration< NumericExecutionPass > PASS(
    "Numeric Execution Pass",
    "execute numerically over the AST input specification", "ast-exec-num", 0 );

bool NumericExecutionPass::run( libpass::PassResult& pr )
{
    walker = new NumericExecutionWalker( *this );

    const bool dump_updates = (bool)pr.getResults()[ (void*)2 ];

    Ast* root = (Ast*)pr.getResult< TypeCheckPass >();
    RuleNode* node
        = global_driver->rules_map_[ root->getInitRule()->identifier ];

    rule_bindings.push_back( &main_bindings );
    function_states
        = std::vector< FunctionState >( global_driver->function_table.size() );
    function_symbols = std::vector< const Function* >(
        global_driver->function_table.size() );
    Function* program_sym
        = global_driver->function_table.get_function( "program" );
    // TODO location is wrong here
    program_sym->intitializers_
        = new std::vector< std::pair< ExpressionBase*, ExpressionBase* > >();
    RuleAtom* init_atom
        = new RuleAtom( node->location, std::string( node->name ) );
    init_atom->rule = node;
    program_sym->intitializers_->push_back(
        std::make_pair( new SelfAtom( node->location ), init_atom ) );

    try
    {
        for( auto pair : global_driver->init_dependencies )
        {
            std::set< std::string > visited;
            if( initialized.count( pair.first ) > 0 )
            {
                continue;
            }
            if( not init_function( pair.first, visited ) )
            {
                Function* func
                    = global_driver->function_table.get_function( pair.first );
                std::string cycle = pair.first;
                for( const std::string& dep : visited )
                {
                    cycle = cycle + " => " + dep;
                }

                throw RuntimeException(
                    func->intitializers_->at( 0 ).second->location,
                    "initializer dependency cycle detected: " + cycle );
            }
        }

        for( auto pair : global_driver->function_table.table_ )
        {
            if( pair.second->type != Symbol::SymbolType::FUNCTION
                or initialized.count( pair.first ) > 0 )
            {
                continue;
            }

            std::set< std::string > visited;
            init_function( pair.first, visited );
        }

        for( List* l : temp_lists )
        {
            l->bump_usage();
        }
        temp_lists.clear();

        uint64_t stepCounter = 0;

        Function* program_sym
            = global_driver->function_table.get_function( "program" );
        const auto& function_map = function_states[ program_sym->id ];
        const value_t& program_val = function_map.get( { value_t() } );

        while( program_val.type != TypeType::UNDEF )
        {
            walker->walk_rule( program_val.value.rule );
            if( hasEmptyUpdateSet() )
            {
                break;
            }
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
        global_driver->error( ex.getLocations(), ex.what(), ex.getErrorCode() );
        return false;
    }
    catch( char* e )
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
    const auto end = updateSet->end();
    for( auto it = updateSet->begin(); it != end; ++it )
    {
        const Update* update = it.value();
        const Function* function = function_symbols[ update->func ];

        if( not firstDump )
        {
            std::cout << ", ";
        }

        std::cout << function->name << to_string( *update->args ) << " = "
                  << update->value.to_str();

        firstDump = false;
    }

    std::cout << "}" << std::endl;
}

bool NumericExecutionPass::init_function(
    const std::string& name, std::set< std::string >& visited )
{
    if( global_driver->init_dependencies.count( name ) != 0 )
    {
        visited.insert( name );
        const std::set< std::string >& deps
            = global_driver->init_dependencies[ name ];

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

    Function* func = global_driver->function_table.get_function( name );

    if( not func )
    {
        return true;
    }

    function_states[ func->id ] = FunctionState( 0 );
    function_symbols[ func->id ] = func;

    auto& function_map = function_states[ func->id ];

    if( func->intitializers_ != nullptr )
    {
        for( std::pair< ExpressionBase*, ExpressionBase* > init :
            *func->intitializers_ )
        {
            std::vector< value_t > arguments{};
            arguments.reserve( func->arguments_.size() );

            if( init.first != nullptr )
            {
                const value_t argument_v = walker->walk_atom( init.first );
                if( func->arguments_.size() > 1 )
                {
                    List* list = argument_v.value.list;
                    for( auto iter = list->begin(); iter != list->end();
                         iter++ )
                    {
                        arguments.emplace_back( *iter );
                    }
                }
                else
                {
                    arguments.emplace_back( argument_v );
                }
            }

            if( func->checkArguments )
            {
                try
                {
                    validateArguments( func->arguments_, arguments );
                }
                catch( const std::domain_error& e )
                {
                    throw RuntimeException( init.first->location, e.what(),
                        libcasm_fe::Codes::
                            FunctionArgumentsInvalidRangeAtInitially );
                }
            }

            if( function_map.hasKey( arguments ) )
            {
                throw RuntimeException( init.first->location,
                    "function '" + func->name + to_string( arguments )
                        + "' already initialized",
                    libcasm_fe::Codes::
                        FunctionValueAlreadyInitializedAtInitially );
            }

            const value_t v = walker->walk_atom( init.second );
            if( func->checkReturnValue )
            {
                try
                {
                    validateValue( func->return_type_, v );
                }
                catch( const std::domain_error& e )
                {
                    throw RuntimeException( init.second->location,
                        std::string( e.what() ) + " of `" + func->name + "`",
                        libcasm_fe::Codes::
                            FunctionValueInvalidRangeAtInitially );
                }
            }

            function_map.insert( arguments, v );
        }
    }

    initialized.insert( name );
    return true;
}

void NumericExecutionPass::visit_assure( UnaryNode* assure, const value_t& val )
{
    visit_assert( assure, val );
}

void NumericExecutionPass::visit_print(
    PrintNode* node, const value_t& argument )
{
    if( node->getFilter().size() > 0 )
    {
        if( filter_enabled( node->getFilter() ) )
        {
            std::cout << node->getFilter() << ": ";
        }
        else
        {
            return;
        }
    }

    std::cout << argument.to_str() << std::endl;
}

void NumericExecutionPass::visit_push(
    PushNode* node, const value_t& expr, const value_t& atom )
{
    std::vector< value_t > arguments{}; // TODO at the moment, functions with
                                        // arguments are not supported

    const value_t to_res = builtins::cons( temp_lists, expr, atom );
    addUpdate( node->to->symbol, arguments, to_res, node->location );
}

void NumericExecutionPass::visit_pop( PopNode* node, const value_t& val )
{
    std::vector< value_t > arguments{}; // TODO at the moment, functions with
                                        // arguments are not supported

    const value_t to_res = builtins::peek( val );

    if( node->to->symbol_type == FunctionAtom::SymbolType::FUNCTION )
    {
        addUpdate( node->to->symbol, arguments, to_res, node->location );
    }
    else
    {
        rule_bindings.back()->push_back( to_res );
    }

    const value_t from_res = builtins::tail( temp_lists, val );
    addUpdate( node->from->symbol, arguments, from_res, node->location );
}

value_t NumericExecutionPass::visit_expression(
    BinaryExpression* expr, const value_t& left_val, const value_t& right_val )
{
    using Opcode = libcasm_ir::Value::ID;

    switch( expr->op )
    {
        case Opcode::ADD_INSTRUCTION:
            return left_val + right_val;
        case Opcode::SUB_INSTRUCTION:
            return left_val - right_val;
        case Opcode::MUL_INSTRUCTION:
            return left_val * right_val;
        case Opcode::DIV_INSTRUCTION:
            return left_val / right_val;
        case Opcode::MOD_INSTRUCTION:
            return left_val % right_val;
        case Opcode::RIV_INSTRUCTION:
            return rat_div( left_val, right_val );
        case Opcode::EQU_INSTRUCTION:
            return value_t( left_val == right_val );
        case Opcode::NEQ_INSTRUCTION:
            return value_t( left_val != right_val );
        case Opcode::AND_INSTRUCTION:
            return left_val and right_val;
        case Opcode::OR_INSTRUCTION:
            return left_val or right_val;
        case Opcode::XOR_INSTRUCTION:
            return left_val ^ right_val;
        case Opcode::LTH_INSTRUCTION:
            return left_val < right_val;
        case Opcode::GTH_INSTRUCTION:
            return left_val > right_val;
        case Opcode::LEQ_INSTRUCTION:
            return left_val <= right_val;
        case Opcode::GEQ_INSTRUCTION:
            return left_val >= right_val;
        default:
            assert( !"internal error" ); // PPA: FIXME: with better verbose info
                                         // etc.
            return value_t();
    }
}

value_t NumericExecutionPass::visit_expression_single(
    UnaryExpression* expr, const value_t& val )
{
    using Opcode = libcasm_ir::Value::ID;

    if( val.is_undef() )
    {
        return value_t();
    }

    switch( expr->op )
    {
        case Opcode::NOT_INSTRUCTION:
            return value_t( not val.value.boolean );
        default:
            assert( !"internal error" ); // PPA: FIXME: with better verbose info
                                         // etc.
            return value_t();
    }
}

value_t NumericExecutionPass::visit_list_atom(
    ListAtom* atom, const std::vector< value_t >& vals )
{
    BottomList* list = new BottomList( vals );
    // context_.temp_lists.push_back(list);
    return value_t( atom->type_, list );
}

template <>
void NumericExecutionWalker::walk_ifthenelse( IfThenElseNode* node )
{
    const value_t cond = walk_atom( node->condition_ );

    if( cond.is_undef() )
    {
        throw RuntimeException( node->condition_->location,
            "condition must be true or false but was undef" );
    }
    else if( cond.value.boolean )
    {
        walk_statement( node->then_ );
    }
    else if( node->else_ )
    {
        walk_statement( node->else_ );
    }
}

template <>
void NumericExecutionWalker::walk_case( CaseNode* node )
{
    const value_t cond = walk_atom( node->expr );

    std::pair< AtomNode*, AstNode* >* default_pair = nullptr;
    for( auto& pair : node->case_list )
    {
        // pair.first == nullptr for default:
        if( pair.first )
        {
            if( walk_atom( pair.first ) == cond )
            {
                walk_statement( pair.second );
                return;
            }
        }
        else
        {
            default_pair = &pair;
        }
    }
    if( default_pair )
    {
        walk_statement( default_pair->second );
    }
}

template <>
void NumericExecutionWalker::walk_iterate( UnaryNode* node )
{
    visitor.fork( UpdateSet::Type::Sequential );

    while( true )
    {
        visitor.fork( UpdateSet::Type::Parallel );
        walk_statement( node->child_ );
        if( visitor.hasEmptyUpdateSet() )
        {
            visitor.merge(); // to remove the update set from the stack
            break;
        }
        visitor.merge();
    }

    visitor.merge();
}

template <>
void NumericExecutionWalker::walk_update( UpdateNode* node )
{
    const auto value = walk_atom( node->expr_ );
    const auto argumentValues = evaluateExpressions( node->func->arguments );
    visitor.visit_update( node, argumentValues, value );
}

//
//  Local variables:
//  mode: c++
//  indent-tabs-mode: nil
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//
