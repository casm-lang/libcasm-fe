//
//  Copyright (c) 2014-2017 CASM Organization
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

#include "TypeCheckPass.h"

#include "../Driver.h"
#include "../Value.h"

#include "cpp/Math.h"

using namespace libcasm_fe;

extern Driver* global_driver;

char TypeCheckPass::id = 0;

static libpass::PassRegistration< TypeCheckPass > PASS( "TypeInferencePass",
    "type check the AST and translate it to a typed AST", "ast-typed", 0 );

void TypeCheckPass::usage( libpass::PassUsage& pu )
{
    pu.require< SourceToAstPass >();
}

bool TypeCheckPass::run( libpass::PassResult& pr )
{
    auto node = pr.result< SourceToAstPass >();

    try
    {
        AstWalker< TypeCheckPass, Type* > typecheck_walker( *this );
        typecheck_walker.walk_specification( node->root() );
    }
    catch( const CompiletimeException& e )
    {
        global_driver->error( e );
    }

    if( not m_specificationHasInitNode )
    {
        global_driver->error( node->root()->location, "no 'init' node defined",
            libcasm_fe::Codes::AgentInitRuleNotDefined );
    }

    pr.setResult< TypeCheckPass >( node );

    return global_driver->ok();
}

void TypeCheckPass::check_type_valid(
    const yy::location& location, const Type& type )
{
    if( type == TypeType::ENUM
        && !global_driver->function_table.get_enum( type.enum_name ) )
    {
        global_driver->error( location, "unknown type '" + type.enum_name + "'",
            libcasm_fe::Codes::TypeUnknown );
    }
}

void TypeCheckPass::visit_root( Ast* )
{
}

void TypeCheckPass::visit_specification( SpecificationNode* )
{
}

void TypeCheckPass::visit_init( InitNode* )
{
    m_specificationHasInitNode = true;
}

void TypeCheckPass::visit_function_def_pre(
    FunctionDefNode* def, Type* defaultValueType )
{
    m_isInFunctionDefinition = true;

    const auto function = def->sym;

    if( function->is_builtin() )
    {
        global_driver->error( def->location,
            "cannot use builtin name '" + function->name
                + "' as function identifier",
            libcasm_fe::Codes::FunctionIdentifierIsBuiltinName );
    }

    check_type_valid( def->location, *function->return_type_ );

    // Check if argument types are valid
    for( Type* argument_t : function->arguments_ )
    {
        check_type_valid( def->location, *argument_t );
    }

    // Check if the type of the default value is correct
    check_type_valid( def->location, defaultValueType );
    if( not function->return_type_->unify( defaultValueType ) )
    {
        global_driver->error( def->defaultValue()->location,
            "type of default value is '" + defaultValueType->to_str()
                + "', but should be '"
                + function->return_type_->to_str()
                + "'",
            libcasm_fe::Codes::FunctionDefaultValueTypeMismatch );
    }

    m_declaredFunctions.emplace( function->name );

    // function initialization ... (see check in visit_function_atom)
}

void TypeCheckPass::visit_function_def_post( FunctionDefNode* def )
{
    m_isInFunctionDefinition = false;
}

void TypeCheckPass::visit_derived_def_pre( DerivedDefNode* def )
{
    rule_binding_types.push_back( &def->sym->arguments_ );
    rule_binding_offsets.push_back( &def->sym->binding_offsets );
}

void TypeCheckPass::visit_derived_def( DerivedDefNode* def, Type* expr )
{
    rule_binding_types.pop_back();
    rule_binding_offsets.pop_back();

    if( not def->sym->return_type_->unify( expr ) )
    {
        global_driver->error(
            def->location, "type of derived expression is '" + expr->to_str()
                               + "', but specified as '"
                               + def->sym->return_type_->to_str() + "'" );
    }
    else if( not def->sym->return_type_->is_complete() )
    {
        global_driver->error( def->location,
            "type of derived expression is unknown because type of expression "
            "is "
                + expr->to_str(),
            libcasm_fe::Codes::DerivedExpressionInvalidType );
    }

    if( def->sym->return_type_->t == TypeType::BIT
        and def->sym->derived->type_.t == TypeType::BIT
        and def->sym->return_type_->bitsize
                != def->sym->derived->type_.bitsize )
    {
        global_driver->error( def->location,
            "expression bit size does not match the return type bit size" );
    }

    def->sym->parameter.resize( def->sym->binding_offsets.size(), nullptr );
    for( const auto& arg : def->sym->binding_offsets )
    {
        const auto i = arg.second;
        assert( i < def->sym->parameter.size()
                and "invalid parameter index found!" );
        def->sym->parameter[ i ] = arg.first.c_str();
    }
}

void TypeCheckPass::visit_rule( RuleNode* rule )
{
    m_isInRule = true;

    rule_binding_types.push_back( &rule->arguments );
    rule_binding_offsets.push_back( &rule->binding_offsets );

    for( const auto& pair : rule->dump_list )
    {
        for( const std::string& identifier : pair.second )
        {
            const auto sym
                = global_driver->function_table.get_function( identifier );
            if( sym )
            {
                global_driver->function_trace_map.emplace(
                    sym->id, pair.first );
            }
            else
            {
                global_driver->error( rule->location,
                    std::string(
                        "names in dumplist must be function identifiers" )
                        + " but `"
                        + identifier
                        + "` is not a function" );
            }
        }
    }

    rule->parameter.resize( rule->binding_offsets.size(), nullptr );
    for( const auto& arg : rule->binding_offsets )
    {
        const auto i = arg.second;
        assert(
            i < rule->parameter.size() and "invalid parameter index found!" );
        rule->parameter[ i ] = arg.first.c_str();
    }
}

void TypeCheckPass::visit_rule_post( RuleNode* )
{
    m_isInRule = false;
}

void TypeCheckPass::visit_ifthenelse( IfThenElseNode* node, Type* cond )
{
    if( *cond != TypeType::BOOLEAN )
    {
        global_driver->error( node->condition_->location,
            "type of 'if' expression should be 'Boolean', found '"
                + cond->to_str()
                + "'",
            libcasm_fe::Codes::TypeInferenceInvalidIfExpression );
    }
}

void TypeCheckPass::visit_assert( UnaryNode* assert, Type* val )
{
    if( *val != TypeType::BOOLEAN )
    {
        global_driver->error( assert->child_->location,
            "type of expression should be `Bool` but was `" + val->to_str()
                + "`" );
    }
}

void TypeCheckPass::visit_update(
    UpdateNode* update, std::vector< Type* >& argumentValues, Type* )
{
    visit_function_atom( update->func, argumentValues );

    if( update->func->symbol and update->func->symbol->is_static
        and not m_isInFunctionDefinition )
    {
        global_driver->error( update->location,
            "cannot update static function `" + update->func->name + "`" );
    }

    if( not update->func->type_.unify( &update->expr_->type_ ) )
    {
        global_driver->error( update->location,
            "type `"
                + update->func->type_.get_most_general_type( update->func )
                      ->to_str()
                + "` of `"
                + update->func->name
                + "` does not match type `"
                + update->expr_->type_.get_most_general_type( update->expr_ )
                      ->to_str()
                + "` of expression" );
    }

    const Type* lhs = update->func->type_.get_most_general_type( update->func );
    const Type* rhs
        = update->expr_->type_.get_most_general_type( update->expr_ );

    if( lhs->t == TypeType::BIT and lhs->bitsize < rhs->bitsize )
    {
        global_driver->error( update->location,
            "type of '" + lhs->to_str() + "' of '" + update->func->name
                + "' does not match type '"
                + rhs->to_str()
                + "' of expression",
            libcasm_fe::Codes::TypeBitSizeIsInvalid );
    }

    if( update->func->symbol_type == FunctionAtom::SymbolType::PARAMETER )
    {
        global_driver->error( update->location,
            "cannot update `" + update->func->name
                + "` because it is a parameter, not a function" );
    }

    update->type_ = update->func->type_;

    if( update->func->symbol
        and global_driver->function_trace_map.count( update->func->symbol->id )
                > 0 )
    {
        update->dump = true;
    }
}

void TypeCheckPass::visit_call_pre( CallNode* call )
{
    const auto it = global_driver->rules_map_.find( call->rule_name );
    if( it != global_driver->rules_map_.cend() )
    {
        call->rule = it->second;
    }
    else
    {
        global_driver->error( call->location,
            "no rule with name `" + call->rule_name + "` found",
            libcasm_fe::Codes::RuleDoesNotExist );
    }
}

void TypeCheckPass::visit_call_pre( CallNode* call, Type* expr )
{
    if( *expr != TypeType::RULEREF )
    {
        global_driver->error( call->ruleref->location,
            "Indirect target must be a `Ruleref` but was `" + expr->to_str()
                + "`" );
    }
}

void TypeCheckPass::visit_call(
    CallNode* call, std::vector< Type* >& arguments )
{
    // typecheck for indirect calls happens during execution
    if( call->ruleref )
    {
        return;
    }

    const size_t args_defined = call->rule->arguments.size();
    const size_t args_provided = arguments.size();

    if( args_defined != args_provided )
    {
        global_driver->error( call->location,
            "rule '" + call->rule_name + "' expects "
                + std::to_string( args_defined )
                + " arguments but "
                + std::to_string( args_provided )
                + " where provided",
            libcasm_fe::Codes::RuleArgumentsSizeInvalidAtCall );
    }
    else
    {
        for( size_t i = 0; i < args_defined; i++ )
        {
            if( not call->rule->arguments.at( i )->unify( arguments.at( i ) ) )
            {
                global_driver->error( call->arguments->at( i )->location,
                    "argument " + std::to_string( i + 1 ) + " of rule '"
                        + call->rule_name
                        + "' must be '"
                        + call->rule->arguments.at( i )->to_str()
                        + "' but was '"
                        + arguments.at( i )->to_str()
                        + "'",
                    libcasm_fe::Codes::RuleArgumentsTypeInvalidAtCall );
            }
        }
    }
}

void TypeCheckPass::visit_print( PrintNode* node, Type* type )
{
    if( node->getAtom()->type_.t == TypeType::UNKNOWN )
    {
        global_driver->error( node->getAtom()->location,
            "unable to annotate type of print statement",
            libcasm_fe::Codes::TypeInferenceInvalidPrint );
    }
}

void TypeCheckPass::visit_diedie( DiedieNode* node, Type* msg )
{
    if( node->msg and not node->msg->type_.unify( TypeType::STRING ) )
    {
        global_driver->error( node->msg->location,
            "expression of `diedie` must be a String but was "
                + msg->to_str() );
    }
}

void TypeCheckPass::visit_let( LetNode* node, Type* )
{
    if( node->type_ == TypeType::ENUM
        and not global_driver->function_table.get_enum(
                node->type_.enum_name ) )
    {
        global_driver->error(
            node->location, "unknown type '" + node->type_.enum_name + "'" );
    }

    if( node->type_.t == TypeType::BIT )
    {
        if( node->expr->type_.t == TypeType::INTEGER
            or node->expr->type_.t == TypeType::UNKNOWN )
        {
            node->expr->type_ = node->type_;
        }
    }

    if( not node->type_.unify( &node->expr->type_ ) )
    {
        global_driver->error(
            node->location, "type of let conflicts with type of expression" );
    }

    node->type_.get_most_general_type( node );
    node->expr->type_.get_most_general_type( node->expr );
    DEBUG( node->type_.unify_links_to_str() );

    if( node->type_.t == TypeType::BIT
        and node->expr->type_.t == TypeType::BIT )
    {
        INTEGER_T bitsize = node->type_.bitsize;
        INTEGER_T value = -1;
        INTEGER_T value_bitsize = -1;

        if( node->expr->node_type_ == NodeType::INTEGER_ATOM )
        {
            value = static_cast< IntegerAtom* >( node->expr )->val_;
            double v = (double)value;
            v = floor( log2( v ) ) + 1;
            value_bitsize = (INTEGER_T)v;
        }
        else
        {
            value_bitsize = node->expr->type_.bitsize;
        }

        if( value_bitsize > bitsize )
        {
            global_driver->error( node->expr->location,
                "let expression bitsize '" + std::to_string( value_bitsize )
                    + "' does not fit into the bitsize of '"
                    + std::to_string( bitsize )
                    + "'",
                libcasm_fe::Codes::TypeBitSizeInvalidInLetExpression );
        }

        node->expr->type_.bitsize = bitsize;
    }

    auto current_rule_binding_types = rule_binding_types.back();
    auto current_rule_binding_offsets = rule_binding_offsets.back();

    current_rule_binding_offsets->insert( std::pair< std::string, size_t >(
        node->identifier, current_rule_binding_types->size() ) );

    current_rule_binding_types->push_back( &node->type_ );
}

void TypeCheckPass::visit_let_post( LetNode* node )
{
    if( not node->type_.is_complete() )
    {
        global_driver->error( node->location,
            "unable to infer the type of let identifier '" + node->identifier
                + "'",
            libcasm_fe::Codes::TypeInferenceInvalidLet );
    }
    rule_binding_types.back()->pop_back();
    rule_binding_offsets.back()->erase( node->identifier );
}

void TypeCheckPass::visit_push( PushNode* node, Type* expr, Type* atom )
{
    if( node->to->symbol_type != FunctionAtom::SymbolType::FUNCTION )
    {
        global_driver->error(
            node->to->location, "can only push into functions" );
    }
    else
    {
        if( node->to->symbol->is_static )
        {
            global_driver->error(
                node->to->location, "cannot push into static function `"
                                        + node->to->symbol->name + "`" );
        }
        if( not expr->unify( atom->subtypes.at( 0 ) ) )
        {
            global_driver->error( node->expr->location,
                "cannot push " + expr->get_most_general_type( node )->to_str()
                    + " into "
                    + atom->to_str() );
        }
    }
}

void TypeCheckPass::visit_pop( PopNode* node, Type* atom )
{
    if( not node->from_type.unify( &node->from->type_ ) )
    {
        global_driver->error( node->from->location,
            "`pop from` argument must be List(A) but was "
                + node->from->type_.to_str() );
    }

    if( node->from->symbol_type != FunctionAtom::SymbolType::FUNCTION )
    {
        global_driver->error(
            node->from->location, "can only pop from functions" );
    }
    else
    {
        if( node->from->symbol->is_static )
        {
            global_driver->error(
                node->from->location, "cannot pop from static function `"
                                          + node->from->symbol->name + "`" );
        }
    }

    const auto sym
        = global_driver->function_table.get_function( node->to->name );
    if( sym )
    {
        if( sym->is_static )
        {
            global_driver->error( node->to->location,
                "cannot pop into static function `" + sym->name + "`" );
        }

        if( node->to->arguments )
        {
            // TODO this should be doable!
            global_driver->error(
                node->to->location, "cannot pop into function with arguments" );
        }
        std::vector< Type* > arguments{};
        visit_function_atom( node->to, arguments );
        if( !node->type_.unify( &node->to->type_ ) )
        {
            global_driver->error( node->from->location,
                "cannot pop from " + node->from->type_.to_str() + " into "
                    + node->to->type_.to_str() );
        }
    }
    else
    {
        auto current_rule_binding_types = rule_binding_types.back();
        auto current_rule_binding_offsets = rule_binding_offsets.back();

        if( current_rule_binding_offsets->count( node->to->name ) != 0 )
        {
            global_driver->error( node->to->location,
                "can only pop into functions or new bindings" );
        }
        current_rule_binding_offsets->insert( std::pair< std::string, size_t >(
            node->to->name, current_rule_binding_types->size() ) );
        current_rule_binding_types->push_back( &node->type_ );
        node->to->symbol_type = FunctionAtom::SymbolType::PUSH_POP;
        node->to->offset = current_rule_binding_offsets->at( node->to->name );
    }
}

void TypeCheckPass::visit_case(
    CaseNode* node, Type* expr, const std::vector< Type* >& case_labels )
{
    if( node->case_list.size() - case_labels.size() > 1 )
    {
        for( auto c = node->case_list.rbegin(); c != node->case_list.rend();
             c++ )
        {
            if( c->first )
            {
                continue;
            }

            global_driver->error( c->second->location,
                "found multiple 'default' labels for case, but only one is "
                "allowed",
                libcasm_fe::Codes::CaseLabelMultipleUseOfDefault );
        }
    }

    for( size_t i = 0; i < case_labels.size(); i++ )
    {
        if( expr->t == TypeType::BIT
            && case_labels[ i ]->t == TypeType::INTEGER )
        {
            if( not node->case_list[ i ].first )
            {
                // default case, omit!
                continue;
            }

            ExpressionBase* expr_value = node->case_list[ i ].first;
            if( expr_value->node_type_ != NodeType::INTEGER_ATOM )
            {
                global_driver->error( node->case_list[ i ].first->location,
                    "case item shall be an Integer constant" );
                continue;
            }

            IntegerAtom* expr_atom = static_cast< IntegerAtom* >( expr_value );
            INTEGER_T value = expr_atom->val_;
            INTEGER_T value_bitsize = -1;
            INTEGER_T bitsize = expr->bitsize;

            value = ( value <= 0 ) ? 1 : value;

            double v = (double)value;
            v = floor( log2( v ) ) + 1;
            value_bitsize = (INTEGER_T)v;

            if( value_bitsize > bitsize )
            {
                global_driver->error( node->case_list[ i ].first->location,
                    "bitsize " + std::to_string( value_bitsize )
                        + " of case list value does not fit into '"
                        + expr->to_str()
                        + "' of case expression" );
            }
            else
            {
                case_labels[ i ]->t = TypeType::BIT;
                case_labels[ i ]->bitsize = bitsize;

                node->case_list[ i ].first->type_.t = TypeType::BIT;
                node->case_list[ i ].first->type_.bitsize = bitsize;
            }

            // continue;
        }

        if( !expr->unify( case_labels[ i ] ) )
        {
            global_driver->error( node->case_list[ i ].first->location,
                "type of case expression ("
                    + expr->get_most_general_type( node )->to_str()
                    + ") and label ("
                    + case_labels[ i ]
                          ->get_most_general_type( node->case_list[ i ].first )
                          ->to_str()
                    + ") do not match" );
        }
    }
}

void TypeCheckPass::check_numeric_operator(
    const yy::location& loc, Type* type, const libcasm_ir::Value::ID op )
{
    if( *type == TypeType::UNKNOWN )
    {
        type->constraints.push_back( new Type( TypeType::INTEGER ) );
        if( op != libcasm_ir::Value::MOD_INSTRUCTION )
        {
            type->constraints.push_back( new Type( TypeType::RATIONAL ) );
            type->constraints.push_back( new Type( TypeType::FLOATING ) );
        }
    }
    else
    {
        if( op == libcasm_ir::Value::MOD_INSTRUCTION )
        {
            if( *type != TypeType::INTEGER && *type != TypeType::FLOATING )
            {
                global_driver->error( loc,
                    "operands of operator `" + operator_to_str( op )
                        + "` must be Integer or Floating but were "
                        + type->to_str() );
            }
        }
        else if( op == libcasm_ir::Value::ADD_INSTRUCTION )
        {
            if( *type != TypeType::INTEGER and *type != TypeType::FLOATING
                and *type != TypeType::BIT
                and *type != TypeType::RATIONAL
                and *type != TypeType::STRING )
            {
                global_driver->error
        ( loc
        , "operands of operator `"
          + operator_to_str( op )
          + "` must be Integer, Bit, String, Floating or Rational but were "
          + type->to_str()
        , libcasm_fe::Codes::OperatorAddInvalidOperandType
        );
            }
        }
        else if( *type != TypeType::INTEGER && *type != TypeType::FLOATING
                 && *type != TypeType::BIT
                 && *type != TypeType::RATIONAL )
        {
            global_driver->error( loc,
                "operands of operator `" + operator_to_str( op )
                    + "` must be Integer, Bit, Floating or Rational but were "
                    + type->to_str() );
        }
    }
}

Type* TypeCheckPass::visit_expression( BinaryExpression* expr, Type*, Type* )
{
    using Opcode = libcasm_ir::Value::ID;

    if( not expr->left_->type_.unify( &expr->right_->type_ ) )
    {
        global_driver->error( expr->location,
            "type of expressions did not match: "
                + expr->left_->type_.get_most_general_type( expr->left_ )
                      ->to_str()
                + " != "
                + expr->right_->type_.get_most_general_type( expr->right_ )
                      ->to_str(),
            libcasm_fe::Codes::TypeInferenceInvalidExpression );
    }

    const Type* lhs = expr->left_->type_.get_most_general_type( expr->left_ );
    const Type* rhs = expr->right_->type_.get_most_general_type( expr->right_ );

    if( lhs->t == TypeType::BIT and rhs->t == TypeType::BIT
        and lhs->bitsize != rhs->bitsize )
    {
        global_driver->error( expr->location,
            "size of 'Bit' types in expression did not match: " + lhs->to_str()
                + " != "
                + rhs->to_str(),
            libcasm_fe::Codes::TypeBitSizeInvalidExpression );
    }

    if( expr->left_->node_type_ == NodeType::ZERO_ATOM )
    {
        ZeroAtom* tmp = reinterpret_cast< ZeroAtom* >( expr->left_ );

        switch( tmp->getRef()->type_.t )
        {
            case TypeType::INTEGER:
            {
                tmp = (ZeroAtom*)new IntegerAtom( tmp->location, 0 );
                break;
            }
            case TypeType::FLOATING:
            {
                tmp = (ZeroAtom*)new FloatingAtom( tmp->location, 0 );
                break;
            }
            case TypeType::RATIONAL:
            {
                tmp = (ZeroAtom*)new RationalAtom(
                    tmp->location, rational_t( 0, 1 ) );
                break;
            }
            default:
            {
                global_driver->error( tmp->getRef()->location,
                    "invalid unary operator type '"
                        + tmp->getRef()->type_.to_str()
                        + "'" );
            }
        }
        delete expr->left_;
        expr->left_ = tmp;
    }

    switch( expr->op )
    {
        case Opcode::ADD_INSTRUCTION:
        case Opcode::SUB_INSTRUCTION:
        case Opcode::MUL_INSTRUCTION:
        case Opcode::DIV_INSTRUCTION:
        case Opcode::MOD_INSTRUCTION:
            check_numeric_operator(
                expr->location, &expr->left_->type_, expr->op );
            expr->type_.unify( &expr->left_->type_ );
            break;
        case Opcode::EQU_INSTRUCTION:
        case Opcode::NEQ_INSTRUCTION:
            expr->type_.unify( Type( TypeType::BOOLEAN ) );
            break;
        case Opcode::LTH_INSTRUCTION:
        case Opcode::GTH_INSTRUCTION:
        case Opcode::LEQ_INSTRUCTION:
        case Opcode::GEQ_INSTRUCTION:
            check_numeric_operator(
                expr->location, &expr->left_->type_, expr->op );
            expr->type_.unify( Type( TypeType::BOOLEAN ) );
            break;
        case Opcode::OR_INSTRUCTION:
        case Opcode::XOR_INSTRUCTION:
        case Opcode::AND_INSTRUCTION:
        {
            if( expr->left_->type_.t == TypeType::BIT
                or expr->right_->type_.t == TypeType::BIT )
            {
                assert( expr->right_->type_.t == TypeType::BIT );
                assert(
                    expr->right_->type_.bitsize == expr->left_->type_.bitsize );

                expr->type_.unify( Type( TypeType::BIT ) );
                expr->type_.bitsize = expr->left_->type_.bitsize;
            }
            else
            {
                if( not expr->left_->type_.unify(
                        new Type( TypeType::BOOLEAN ) ) )
                {
                    global_driver->error( expr->location,
                        "operands of operator `" + operator_to_str( expr->op )
                            + "` must be Boolean or Bit but are "
                            + expr->left_->type_.to_str() );
                }
                expr->type_.unify( Type( TypeType::BOOLEAN ) );
            }
            break;
        }
        default:
            assert( !"internal error" ); // PPA: FIXME: with better verbose info
                                         // etc.
    }

    return &expr->type_;
}

Type* TypeCheckPass::visit_expression_single( UnaryExpression* expr, Type* )
{
    using Opcode = libcasm_ir::Value::ID;

    switch( expr->op )
    {
        case Opcode::NOT_INSTRUCTION:
            if( not expr->expr_->type_.unify( new Type( TypeType::BOOLEAN ) ) )
            {
                global_driver->error( expr->location,
                    "operand of `not` must be Boolean but is "
                        + expr->expr_->type_.to_str() );
            }
            expr->type_.unify( Type( TypeType::BOOLEAN ) );
            break;
        default:
            assert( !"internal error" ); // PPA: FIXME: with better verbose info
                                         // etc.
    }

    return &expr->type_;
}

Type* TypeCheckPass::visit_function_atom(
    FunctionAtom* atom, std::vector< Type* >& arguments )
{
    Symbol* sym = global_driver->function_table.get( atom->name );
    if( sym && sym->type == Symbol::SymbolType::ENUM )
    {
        atom->symbol_type = FunctionAtom::SymbolType::ENUM;
        atom->enum_ = reinterpret_cast< Enum* >( sym );
        if( !forall_head && atom->enum_->name == atom->name )
        {
            global_driver->error( atom->location,
                "`" + atom->name + "` is an enum, not a member of an enum" );
        }
        atom->type_.unify( new Type( TypeType::ENUM, sym->name ) );
        return &atom->type_;
    }

    if( !sym )
    {
        // check if a rule parameter with this name was defined
        if( rule_binding_offsets.size() > 0 )
        {
            auto current_rule_binding_offsets = rule_binding_offsets.back();
            auto current_rule_binding_types = rule_binding_types.back();

            if( current_rule_binding_offsets->count( atom->name )
                && !atom->arguments )
            {
                atom->symbol_type = FunctionAtom::SymbolType::PARAMETER;
                atom->offset = current_rule_binding_offsets->at( atom->name );
                Type* binding_type
                    = current_rule_binding_types->at( atom->offset );
                atom->type_.unify( binding_type );
                return &atom->type_;
            }
        }

        throw CompiletimeException(
            atom->location, "use of undeclared function `" + atom->name + "`" );
    }

    Function* func = reinterpret_cast< Function* >( sym );

    if( m_isInFunctionDefinition
        and ( func->type == Symbol::SymbolType::FUNCTION ) )
    {
        // only declared functions are allowed in the function initialization
        if( m_declaredFunctions.count( atom->name ) == 0 )
        {
            throw CompiletimeException( atom->location,
                "use of undeclared function `" + atom->name + "` in initially",
                libcasm_fe::Codes::
                    TypeCheckUseOfUndeclaredFunctionInInitially );
        }
    }

    atom->symbol = func;
    if( atom->symbol->type == Symbol::SymbolType::FUNCTION )
    {
        atom->symbol_type = FunctionAtom::SymbolType::FUNCTION;
    }
    else
    {
        atom->symbol_type = FunctionAtom::SymbolType::DERIVED;
    }

    // check for function definitions with arguments
    if( atom->symbol->arguments_.size() != arguments.size() )
    {
        global_driver->error( atom->location,
            "number of provided arguments does not match definition of `"
                + atom->name
                + "`" );
    }
    else
    {
        for( size_t i = 0; i < atom->symbol->arguments_.size(); i++ )
        {

            Type* argument_t = atom->symbol->arguments_.at( i );

            if( !arguments.at( i )->unify( argument_t ) )
            {
                global_driver->error( atom->arguments->at( i )->location,
                    "type of " + std::to_string( i + 1 ) + " argument of `"
                        + atom->name
                        + "` is "
                        + arguments.at( i )->to_str()
                        + " but should be "
                        + argument_t->to_str() );
            }
        }
    }

    atom->type_.unify( func->return_type_ );
    return &atom->type_;
}

Type* TypeCheckPass::visit_builtin_atom(
    BuiltinAtom* atom, std::vector< Type* >& arguments )
{
    Builtin* built_in = Builtin::get( atom->name );
    assert( built_in );

    built_in->typecheck( *global_driver, atom, arguments );

    if( atom->types.size() != arguments.size() )
    {
        global_driver->error( atom->location,
            "number of provided arguments does not match definition of `"
                + atom->name
                + "`" );
    }
    else
    {
        for( size_t i = 0; i < atom->types.size(); i++ )
        {

            Type* argument_t = atom->types.at( i );

            if( !arguments.at( i )->unify( argument_t ) )
            {
                global_driver->error( atom->arguments->at( i )->location,
                    "type of " + std::to_string( i + 1 ) + " argument of `"
                        + atom->name
                        + "` is "
                        + arguments.at( i )->to_str()
                        + " but should be "
                        + argument_t->to_str() );
            }
        }
    }

    if( atom->name == "nth" )
    {
        if( *atom->types[ 0 ] == TypeType::TUPLE_OR_LIST
            && atom->types[ 0 ]->subtypes.size() > 0
            && atom->types[ 0 ]->subtypes[ 0 ]->t != TypeType::UNKNOWN )
        {
            Type first = *atom->types[ 0 ]->subtypes[ 0 ];
            bool all_equal = true;
            for( size_t i = 1; i < atom->types[ 0 ]->subtypes.size(); i++ )
            {
                if( first != *atom->types[ 0 ]->subtypes[ i ] )
                {
                    all_equal = false;
                    break;
                }
            }
            if( all_equal )
            {
                atom->types[ 0 ]->t = TypeType::LIST;
                atom->types[ 0 ]->subtypes = { new Type( first ) };
            }
        }

        if( *atom->types[ 0 ] == TypeType::TUPLE )
        {
            ExpressionBase* ind_expr = atom->arguments->at( 1 );
            if( ind_expr->node_type_ == NodeType::INTEGER_ATOM )
            {
                INTEGER_T ind
                    = reinterpret_cast< IntegerAtom* >( ind_expr )->val_;
                if( ind <= 0 )
                {
                    global_driver->error( atom->arguments->at( 1 )->location,
                        "second argument of nth must be a positive (>0) "
                        "Integer constant for tuples" );

                    return &atom->type_;
                }

                // this is needed to handle stuff like:
                //          assert nth(undef, 2) = undef
                if( atom->types[ 0 ]->is_unknown() && atom->type_.is_unknown() )
                {
                    return &atom->type_;
                }
                if( (size_t)ind < ( atom->types[ 0 ]->subtypes.size() + 1 ) )
                {
                    atom->type_.unify( atom->types[ 0 ]->subtypes[ ind - 1 ] );
                }
                else
                {
                    global_driver->error( atom->arguments->at( 1 )->location,
                        "index out of bounds for tuple, currently tuple only "
                        "has "
                            + std::to_string( atom->arguments->size() )
                            + " types" );
                }
            }
            else
            {
                global_driver->error( atom->arguments->at( 1 )->location,
                    "second argument of nth must be an Integer constant for "
                    "tuples but was `"
                        + type_to_str( ind_expr->node_type_ )
                        + "`" );
            }
        }
        else
        {
            atom->type_.unify( atom->types[ 0 ]->subtypes[ 0 ] );
            arguments[ 0 ]->unify( &atom->type_ );
            atom->type_.unify( atom->return_type );
        }
    }
    else
    {
        // TODO use type_ as return_type_ for builtins
        atom->type_.unify( atom->return_type );
    }
    return &atom->type_;
}

void TypeCheckPass::visit_derived_function_atom_pre(
    FunctionAtom* atom, std::vector< Type* >& arguments )
{
    const size_t args_defined = atom->symbol->arguments_.size();
    const size_t args_provided = arguments.size();

    if( args_defined != args_provided )
    {
        global_driver->error( atom->location,
            " expects " + std::to_string( args_defined ) + " arguments but "
                + std::to_string( args_provided )
                + " where provided" );
    }
    else
    {
        for( size_t i = 0; i < args_defined; i++ )
        {
            if( !arguments.at( i )->unify( atom->symbol->arguments_.at( i ) ) )
            {
                global_driver->error( atom->arguments->at( i )->location,
                    "argument " + std::to_string( i + 1 ) + " of must be `"
                        + atom->symbol->arguments_.at( i )->to_str()
                        + "` but was `"
                        + arguments.at( i )->to_str()
                        + "`" );
            }
        }
    }

    rule_binding_types.push_back( &atom->symbol->arguments_ );
    rule_binding_offsets.push_back( &atom->symbol->binding_offsets );
}

Type* TypeCheckPass::visit_derived_function_atom( FunctionAtom*, Type* expr )
{
    rule_binding_types.pop_back();
    rule_binding_offsets.pop_back();
    return expr;
}

Type* TypeCheckPass::visit_rule_atom( RuleAtom* atom )
{
    if( global_driver->rules_map_.count( atom->name ) == 1 )
    {
        atom->rule = global_driver->rules_map_[ atom->name ];
    }
    else
    {
        global_driver->error( atom->location,
            "no rule with name `" + atom->name + "` found",
            libcasm_fe::Codes::RuleDoesNotExist );
    }
    return &atom->type_;
}

Type* TypeCheckPass::visit_list_atom(
    ListAtom* atom, const std::vector< Type* >& vals )
{
    atom->type_.t = TypeType::TUPLE_OR_LIST;
    atom->type_.subtypes = vals;

    if( vals.size() > 0 )
    {
        Type first = *( vals[ 0 ] );
        bool all_known = first.is_complete();
        bool all_equal = true;
        for( size_t i = 1; i < vals.size(); i++ )
        {
            all_known = all_known && vals[ i ]->is_complete();
            if( first != *vals[ i ] )
            {
                all_equal = false;
                break;
            }
        }
        if( !all_equal && all_known )
        {
            atom->type_.t = TypeType::TUPLE;
        }
    }

    return &atom->type_;
}

Type* TypeCheckPass::visit_number_range_atom(
    NumberRangeAtom* atom, Type* left, Type* right )
{
    if( not left->unify( TypeType::INTEGER ) )
    {
        global_driver->error( atom->left->location,
            "left value of number range must be an Integer but was '"
                + left->to_str()
                + "'",
            libcasm_fe::Codes::TypeNumberRangeInvalidTypeAtLeftHandSide );
    }
    if( not right->unify( TypeType::INTEGER ) )
    {
        global_driver->error( atom->right->location,
            "right value of number range must be an Integer but was '"
                + right->to_str()
                + "'",
            libcasm_fe::Codes::TypeNumberRangeInvalidTypeAtRightHandSide );
    }
    return &atom->type_;
}

template <>
void AstWalker< TypeCheckPass, Type* >::walk_forall( ForallNode* node )
{
    visitor.forall_head = true;
    walk_atom( node->in_expr );
    visitor.forall_head = false;

    // TODO this leaks in some cases
    Type* list_t = new Type( TypeType::LIST, new Type( TypeType::UNKNOWN ) );

    if( node->in_expr->type_ == TypeType::INTEGER
        || node->in_expr->type_ == TypeType::ENUM )
    {
        node->type_.unify( &node->in_expr->type_ );
    }
    else if( node->in_expr->type_.unify( list_t ) )
    {
        node->type_.unify( node->in_expr->type_.subtypes[ 0 ] );
    }
    else if( node->in_expr->type_ == TypeType::NUMBER_RANGE )
    {
        node->type_.unify( TypeType::INTEGER );
    }
    else
    {
        global_driver->error( node->location,
            "expression must be a List, an Integer, a NumberRange or enum, but "
            "is '"
                + node->in_expr->type_.to_str()
                + "'" );
    }

    auto current_rule_binding_types = visitor.rule_binding_types.back();
    auto current_rule_binding_offsets = visitor.rule_binding_offsets.back();

    current_rule_binding_offsets->insert( std::pair< std::string, size_t >(
        node->identifier, current_rule_binding_types->size() ) );

    current_rule_binding_types->push_back( &node->type_ );

    walk_statement( node->statement );

    if( not node->type_.is_complete() )
    {
        global_driver->error( node->location,
            "type inference for '" + node->identifier + "' failed",
            libcasm_fe::Codes::TypeInferenceInvalidForallExpression );
    }

    visitor.rule_binding_types.back()->pop_back();
    visitor.rule_binding_offsets.back()->erase( node->identifier );
}

Type* TypeCheckPass::visit_zero_atom( ZeroAtom* atom )
{
    return &atom->type_;
}

Type* TypeCheckPass::visit_int_atom( IntegerAtom* atom )
{
    return &atom->type_;
}

Type* TypeCheckPass::visit_floating_atom( FloatingAtom* atom )
{
    return &atom->type_;
}

Type* TypeCheckPass::visit_rational_atom( RationalAtom* atom )
{
    return &atom->type_;
}

Type* TypeCheckPass::visit_undef_atom( UndefAtom* atom )
{
    return &atom->type_;
}

Type* TypeCheckPass::visit_self_atom( SelfAtom* atom )
{
    /*if( not m_isInRule ) TODO: enable this check once we can define agents
    {
        global_driver->error(
            atom->location, "agent 'self' reference shall not be used outside of
    a rule" );
    }*/

    return &atom->type_;
}

Type* TypeCheckPass::visit_boolean_atom( BooleanAtom* atom )
{
    return &atom->type_;
}

Type* TypeCheckPass::visit_string_atom( StringAtom* atom )
{
    return &atom->type_;
}

void TypeCheckPass::visit_body_elements_pre( AstListNode* )
{
}

void TypeCheckPass::visit_body_elements_post( AstListNode* )
{
}

void TypeCheckPass::visit_seqblock_pre( UnaryNode* )
{
}

void TypeCheckPass::visit_seqblock_post( UnaryNode* )
{
}

void TypeCheckPass::visit_parblock_pre( UnaryNode* )
{
}

void TypeCheckPass::visit_parblock_post( UnaryNode* )
{
}

void TypeCheckPass::visit_assure( UnaryNode*, Type* )
{
}

void TypeCheckPass::visit_skip( AstNode* )
{
}

void TypeCheckPass::visit_call_post( CallNode* )
{
}

void TypeCheckPass::visit_iterate( UnaryNode* )
{
}

void TypeCheckPass::visit_case_pre( CaseNode*, Type* )
{
}

void TypeCheckPass::visit_impossible( AstNode* )
{
}

void TypeCheckPass::visit_statements( AstListNode* )
{
}

Type* TypeCheckPass::visit_bit_atom( IntegerAtom* )
{
    return 0;
}

void TypeCheckPass::visit_statement( AstNode* )
{
}

void TypeCheckPass::visit_forall_pre( ForallNode* )
{
}

void TypeCheckPass::visit_forall_post( ForallNode* )
{
}

void TypeCheckPass::visit_forall_iteration_pre( ForallNode*, Type* )
{
}

void TypeCheckPass::visit_forall_iteration_post( ForallNode* )
{
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
