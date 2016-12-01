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

#ifndef CASMI_LIBPARSE_VISITOR_H
#define CASMI_LIBPARSE_VISITOR_H

#include "Ast.h"
#include "Exceptions.h"

class AstNode;

template < class T, class V >
class AstWalker
{
  public:
    T& visitor;

    AstWalker( T& v )
    : visitor( v )
    {
    }

    void walk_specification( Ast* spec )
    {
        assert( spec->node_type_ == NodeType::SPECIFICATION );
        visitor.visit_specification( spec->getSpecification() );
        walk_body_elements( spec->getElements() );
    }

    void walk_body_elements( AstListNode* node )
    {
        for( auto e : node->nodes )
        {
            switch( e->node_type_ )
            {
                case NodeType::PROVIDER:
                    // TODO implement
                    break;
                case NodeType::OPTION:
                    // TODO implement
                    break;
                case NodeType::ENUM:
                    // TODO implement
                    break;
                case NodeType::FUNCTION:
                    walk_function_def(
                        reinterpret_cast< FunctionDefNode* >( e ) );
                    break;
                case NodeType::DERIVED:
                    // TODO implement
                    break;
                case NodeType::RULE:
                    walk_rule( reinterpret_cast< RuleNode* >( e ) );
                    break;
                case NodeType::INIT:
                    visitor.visit_init( reinterpret_cast< InitNode* >( e ) );
                    break;
                default:
                    throw RuntimeException( std::string( "Invalid node type: " )
                                            + type_to_str( e->node_type_ )
                                            + std::string( " at " )
                                            + e->location_str() );
            }
        }

        visitor.visit_body_elements( node );
    }

    void walk_function_def( FunctionDefNode* node )
    {
        if( node->sym->type == Symbol::SymbolType::FUNCTION )
        {
            std::vector< std::pair< V, V > > initializer_results;
            if( node->sym->intitializers_ )
            {
                initializer_results.reserve(
                    node->sym->intitializers_->size() );

                for( std::pair< ExpressionBase*, ExpressionBase* > p :
                    *node->sym->intitializers_ )
                {
                    V first;
                    if( p.first )
                    {
                        first = walk_atom( p.first );
                    }
                    else
                    {
                        UndefAtom foo = { p.second->location };
                        first = walk_atom( &foo );
                    }
                    initializer_results.push_back(
                        std::pair< V, V >( first, walk_atom( p.second ) ) );
                }
            }

            visitor.visit_function_def( node, initializer_results );
        }
        else
        {
            visitor.visit_derived_def_pre( node );
            const V v = walk_atom( node->sym->derived );
            visitor.visit_derived_def( node, v );
        }
    }

    void walk_rule( RuleNode* node )
    {
        visitor.visit_rule( node );
        walk_statement( node->child_ );
        visitor.visit_rule_post( node );
    }

    void walk_skip( AstNode* node )
    {
        visitor.visit_skip( node );
    }

    void walk_impossible( AstNode* node )
    {
        visitor.visit_impossible( node );
    }

    void walk_assert( UnaryNode* node )
    {
        const V v
            = walk_atom( reinterpret_cast< ExpressionBase* >( node->child_ ) );
        visitor.visit_assert( node, v );
    }

    void walk_assure( UnaryNode* node )
    {
        const V v
            = walk_atom( reinterpret_cast< ExpressionBase* >( node->child_ ) );
        visitor.visit_assure( node, v );
    }

    void walk_diedie( DiedieNode* node )
    {
        const V v = node->msg ? walk_atom( node->msg ) : V();
        visitor.visit_diedie( node, v );
    }

    void walk_statement( AstNode* node )
    {
        switch( node->node_type_ )
        {
            case NodeType::SEQBLOCK:
                walk_seqblock( reinterpret_cast< UnaryNode* >( node ) );
                break;
            case NodeType::PARBLOCK:
                walk_parblock( reinterpret_cast< UnaryNode* >( node ) );
                break;
            case NodeType::UPDATE:
                walk_update( reinterpret_cast< UpdateNode* >( node ) );
                break;
            case NodeType::ASSERT:
                walk_assert( reinterpret_cast< UnaryNode* >( node ) );
                break;
            case NodeType::ASSURE:
                walk_assure( reinterpret_cast< UnaryNode* >( node ) );
                break;
            case NodeType::SKIP:
                walk_skip( node );
                break;
            case NodeType::IFTHENELSE:
                walk_ifthenelse( reinterpret_cast< IfThenElseNode* >( node ) );
                break;
            case NodeType::CALL:
                walk_call( reinterpret_cast< CallNode* >( node ) );
                break;
            case NodeType::PRINT:
                walk_print( reinterpret_cast< PrintNode* >( node ) );
                break;
            case NodeType::LET:
                walk_let( reinterpret_cast< LetNode* >( node ) );
                break;
            case NodeType::POP:
                walk_pop( reinterpret_cast< PopNode* >( node ) );
                break;
            case NodeType::PUSH:
                walk_push( reinterpret_cast< PushNode* >( node ) );
                break;
            case NodeType::FORALL:
                walk_forall( reinterpret_cast< ForallNode* >( node ) );
                break;
            case NodeType::ITERATE:
                walk_iterate( reinterpret_cast< UnaryNode* >( node ) );
                break;
            case NodeType::CASE:
                walk_case( reinterpret_cast< CaseNode* >( node ) );
                break;
            case NodeType::DIEDIE:
                walk_diedie( reinterpret_cast< DiedieNode* >( node ) );
                break;
            case NodeType::IMPOSSIBLE:
                walk_impossible( node );
                break;
            default:
                throw RuntimeException( std::string( "Invalid node type: " )
                                        + type_to_str( node->node_type_ )
                                        + std::string( " at " )
                                        + node->location_str() );
        }
    }

    void walk_seqblock( UnaryNode* node )
    {
        visitor.visit_seqblock_pre( node );
        walk_statements( reinterpret_cast< AstListNode* >( node->child_ ) );
        visitor.visit_seqblock_post( node );
    }

    void walk_parblock( UnaryNode* node )
    {
        visitor.visit_parblock_pre( node );
        walk_statements( reinterpret_cast< AstListNode* >( node->child_ ) );
        visitor.visit_parblock_post( node );
    }

    void walk_statements( AstListNode* node )
    {
        visitor.visit_statements( node );
        for( auto stmt : node->nodes )
        {
            walk_statement( stmt );
        }
    }

    void walk_update( UpdateNode* node )
    {
        const V expr = walk_atom( node->expr_ );

        // we must walk the expression before walking update->func because it
        // sets the list of arguments and we do not want the update->expr_ to
        // overwrite the value_list
        walk_function_atom( node->func );

        const auto argumentValues
            = evaluateExpressions( node->func->arguments );
        visitor.visit_update( node, argumentValues, expr );
    }

    void walk_call( CallNode* node )
    {
        if( node->ruleref == nullptr )
        {
            visitor.visit_call_pre( node );
        }
        else
        {
            const V v = walk_atom( node->ruleref );
            visitor.visit_call_pre( node, v );
        }

        // we must evaluate all arguments, to set correct offset for bindings
        std::vector< V > arguments = evaluateExpressions( node->arguments );

        if( node->rule != nullptr )
        {
            visitor.visit_call( node, arguments );
            call_rule( node->rule );
            visitor.visit_call_post( node );
        }
        else
        {
            DEBUG( "rule not set!" );
        }
    }

    void walk_print( PrintNode* node )
    {
        const V v = walk_atom( node->getAtom() );
        visitor.visit_print( node, v );
    }

    void walk_let( LetNode* node )
    {
        const V v = walk_atom( node->expr );
        visitor.visit_let( node, v );
        walk_statement( node->stmt );
        visitor.visit_let_post( node );
    }

    void walk_pop( PopNode* node )
    {
        const V atom = walk_function_atom( node->from );
        visitor.visit_pop( node, atom );
    }

    void walk_push( PushNode* node )
    {
        const V expr = walk_atom( node->expr );
        const V atom = walk_function_atom( node->to );
        visitor.visit_push( node, expr, atom );
    }

    void walk_forall( ForallNode* node )
    {
        const auto expr = walk_atom( node->in_expr );
        visitor.visit_forall_pre( node );
        forall_iterate( node, expr );
        visitor.visit_forall_post( node );
    }

    void walk_iterate( UnaryNode* node )
    {
        visitor.visit_iterate( node );
        walk_statement( node->child_ );
    }

    void walk_case( CaseNode* node )
    {
        const V web = walk_atom( node->expr );
        visitor.visit_case_pre( node, web );

        std::vector< V > case_labels;
        case_labels.reserve( node->case_list.size() );
        for( const auto& pair : node->case_list )
        {
            // pair.first == nullptr for default:
            if( pair.first )
            {
                case_labels.push_back( walk_atom( pair.first ) );
            }
            walk_statement( pair.second );
        }

        visitor.visit_case( node, web, case_labels );
    }

    void walk_ifthenelse( IfThenElseNode* node )
    {
        const V cond = walk_atom( node->condition_ );
        visitor.visit_ifthenelse( node, cond );
        walk_statement( node->then_ );
        if( node->else_ )
        {
            walk_statement( node->else_ );
        }
    }

    V walk_function_atom( FunctionAtom* atom )
    {
        auto argumentValues = evaluateExpressions( atom->arguments );

        if( atom->symbol_type == FunctionAtom::SymbolType::DERIVED )
        {
            visitor.visit_derived_function_atom_pre( atom, argumentValues );
            const V expr = walk_atom( atom->symbol->derived );
            return visitor.visit_derived_function_atom( atom, expr );
        }
        else
        {
            return visitor.visit_function_atom( atom, argumentValues );
        }
    }

    V walk_builtin_atom( BuiltinAtom* atom )
    {
        auto argumentValues = evaluateExpressions( atom->arguments );
        return visitor.visit_builtin_atom( atom, argumentValues );
    }

    V walk_list_atom( ListAtom* atom )
    {
        const auto values = evaluateExpressions( atom->expr_list );
        return visitor.visit_list_atom( atom, values );
    }

    V walk_number_range( NumberRangeAtom* atom )
    {
        const V lhs = walk_atom( atom->left );
        const V rhs = walk_atom( atom->right );
        return visitor.visit_number_range_atom( atom, lhs, rhs );
    }

    V walk_binary_expression( BinaryExpression* expr )
    {
        // IMPORTANT: right hand side has to be evaluated first to assign the
        // correct typed zero value to the left hand side
        const V rhs = walk_atom( expr->right_ );
        const V lhs = walk_atom( expr->left_ );
        return visitor.visit_expression( expr, lhs, rhs );
    }

    V walk_unary_expression( UnaryExpression* expr )
    {
        const V v = walk_atom( expr->expr_ );
        return visitor.visit_expression_single( expr, v );
    }

    V walk_atom( ExpressionBase* atom )
    {
        switch( atom->node_type_ )
        {
            case NodeType::ZERO_ATOM:
                return visitor.visit_zero_atom(
                    reinterpret_cast< ZeroAtom* >( atom ) );
            case NodeType::INTEGER_ATOM:
            {
                auto ia = reinterpret_cast< IntegerAtom* >( atom );

                if( ia->type_.t == TypeType::BIT )
                {
                    return visitor.visit_bit_atom( ia );
                }

                return visitor.visit_int_atom( ia );
            }
            case NodeType::FLOATING_ATOM:
                return visitor.visit_floating_atom(
                    reinterpret_cast< FloatingAtom* >( atom ) );
            case NodeType::RATIONAL_ATOM:
                return visitor.visit_rational_atom(
                    reinterpret_cast< RationalAtom* >( atom ) );
            case NodeType::UNDEF_ATOM:
                return visitor.visit_undef_atom(
                    reinterpret_cast< UndefAtom* >( atom ) );
            case NodeType::BUILTIN_ATOM:
                return walk_builtin_atom(
                    reinterpret_cast< BuiltinAtom* >( atom ) );
            case NodeType::FUNCTION_ATOM:
                return walk_function_atom(
                    reinterpret_cast< FunctionAtom* >( atom ) );
            case NodeType::SELF_ATOM:
                return visitor.visit_self_atom(
                    reinterpret_cast< SelfAtom* >( atom ) );
            case NodeType::RULE_ATOM:
                return visitor.visit_rule_atom(
                    reinterpret_cast< RuleAtom* >( atom ) );
            case NodeType::BOOLEAN_ATOM:
                return visitor.visit_boolean_atom(
                    reinterpret_cast< BooleanAtom* >( atom ) );
            case NodeType::STRING_ATOM:
                return visitor.visit_string_atom(
                    reinterpret_cast< StringAtom* >( atom ) );
            case NodeType::LIST_ATOM:
                return walk_list_atom( reinterpret_cast< ListAtom* >( atom ) );
            case NodeType::NUMBER_RANGE_ATOM:
                return walk_number_range(
                    reinterpret_cast< NumberRangeAtom* >( atom ) );
            case NodeType::BINARY_EXPRESSION:
                return walk_binary_expression(
                    reinterpret_cast< BinaryExpression* >( atom ) );
            case NodeType::UNARY_EXPRESSION:
                return walk_unary_expression(
                    reinterpret_cast< UnaryExpression* >( atom ) );
            default:
                throw RuntimeException( "Invalid atom type:"
                                        + type_to_str( atom->node_type_ )
                                        + std::to_string( atom->node_type_ ) );
        }
    }

  protected:
    std::vector< V > evaluateExpressions(
        std::vector< ExpressionBase* >* expressions )
    {
        std::vector< V > values;
        if( expressions != nullptr )
        {
            values.reserve( expressions->size() );
            for( ExpressionBase* expression : *expressions )
            {
                values.emplace_back( walk_atom( expression ) );
            }
        }
        return values;
    }

  private:
    template < typename V_ = V >
    typename std::enable_if< not std::is_same< value_t, V_ >::value >::type
    forall_iterate( ForallNode* node, const V_& )
    {
        walk_statement( node->statement );
    }

    template < typename V_ = V >
    typename std::enable_if< std::is_same< value_t, V_ >::value >::type
    forall_iterate( ForallNode* node, const V_& expr )
    {
        switch( node->in_expr->type_.t )
        {
            case TypeType::LIST:
            {
                const auto l = expr.value.list;
                for( auto iter = l->begin(); iter != l->end(); iter++ )
                {
                    visitor.visit_forall_iteration_pre( node, *iter );
                    walk_statement( node->statement );
                    visitor.visit_forall_iteration_post( node );
                }
            }
            break;
            case TypeType::NUMBER_RANGE:
            {
                for( auto i : *expr.value.numberRange )
                {
                    visitor.visit_forall_iteration_pre( node, i );
                    walk_statement( node->statement );
                    visitor.visit_forall_iteration_post( node );
                }
            }
            break;

            case TypeType::INTEGER:
            {
                const auto end = expr.value.integer;
                if( end > 0 )
                {
                    for( INTEGER_T i = 1; i <= end; i++ )
                    {
                        visitor.visit_forall_iteration_pre( node, i );
                        walk_statement( node->statement );
                        visitor.visit_forall_iteration_post( node );
                    }
                }
                else
                {
                    for( INTEGER_T i = end; i <= -1; i++ )
                    {
                        visitor.visit_forall_iteration_pre( node, i );
                        walk_statement( node->statement );
                        visitor.visit_forall_iteration_post( node );
                    }
                }
                break;
            }

            case TypeType::ENUM:
            {
                const auto func
                    = reinterpret_cast< FunctionAtom* >( node->in_expr );
                assert( func->name == func->enum_->name );

                for( const auto& pair : func->enum_->mapping )
                {
                    // why is an element with the name of the enum in the map??
                    assert( func->name != pair.first );

                    visitor.visit_forall_iteration_pre( node, pair.second );
                    walk_statement( node->statement );
                    visitor.visit_forall_iteration_post( node );
                }
            }
            break;
            default:
                assert( 0 );
        }
    }

    template < typename V_ = V >
    typename std::enable_if< not std::is_same< value_t, V_ >::value >::type
    call_rule( RuleNode* )
    {
    }

    template < typename V_ = V >
    typename std::enable_if< std::is_same< value_t, V_ >::value >::type
    call_rule( RuleNode* node )
    {
        walk_rule( node );
    }
};

template < class T, class U = const T& >
class BaseVisitor
{
  public:
    virtual void visit_specification( SpecificationNode* )
    {
    }

    virtual void visit_init( InitNode* )
    {
    }

    virtual void visit_body_elements( AstListNode* )
    {
    }

    virtual void visit_function_def(
        FunctionDefNode*, const std::vector< std::pair< T, T > >& )
    {
    }

    virtual void visit_derived_def_pre( FunctionDefNode* )
    {
    }

    virtual void visit_derived_def( FunctionDefNode*, U )
    {
    }

    virtual void visit_rule( RuleNode* )
    {
    }

    virtual void visit_rule_post( RuleNode* )
    {
    }

    virtual void visit_statements( AstListNode* )
    {
    }

    virtual void visit_statement( AstNode* )
    {
    }

    virtual void visit_ifthenelse( IfThenElseNode*, U )
    {
    }

    virtual void visit_assert( UnaryNode*, U )
    {
    }

    virtual void visit_assure( UnaryNode*, U )
    {
    }

    virtual void visit_seqblock_pre( UnaryNode* )
    {
    }

    virtual void visit_seqblock_post( UnaryNode* )
    {
    }

    virtual void visit_parblock_pre( UnaryNode* )
    {
    }

    virtual void visit_parblock_post( UnaryNode* )
    {
    }

    virtual void visit_update( UpdateNode*, const std::vector< T >&, U )
    {
    }

    virtual void visit_call_pre( CallNode* )
    {
    }

    virtual void visit_call_pre( CallNode*, U )
    {
    }

    virtual void visit_call( CallNode*, std::vector< T >& )
    {
    }

    virtual void visit_call_post( CallNode* )
    {
    }

    virtual void visit_print( PrintNode*, U )
    {
    }

    virtual void visit_diedie( DiedieNode*, U )
    {
    }

    virtual void visit_impossible( AstNode* )
    {
    }

    virtual void visit_let( LetNode*, U )
    {
    }

    virtual void visit_let_post( LetNode* )
    {
    }

    virtual void visit_pop( PopNode*, U )
    {
    }

    virtual void visit_push( PushNode*, U, U )
    {
    }

    virtual void visit_case_pre( CaseNode*, U )
    {
    }

    virtual void visit_case( CaseNode*, U, const std::vector< T >& )
    {
    }

    virtual void visit_skip( AstNode* )
    {
    }

    virtual void visit_forall_pre( ForallNode* )
    {
    }

    virtual void visit_forall_post( ForallNode* )
    {
    }

    virtual void visit_forall_iteration_pre( ForallNode*, U )
    {
    }

    virtual void visit_forall_iteration_post( ForallNode* )
    {
    }

    virtual void visit_iterate( UnaryNode* )
    {
    }

    virtual T visit_expression( BinaryExpression*, U, U )
    {
        return T();
    }

    virtual T visit_expression_single( UnaryExpression*, U )
    {
        return T();
    }

    virtual T visit_zero_atom( ZeroAtom* )
    {
        return T();
    }

    virtual T visit_int_atom( IntegerAtom* )
    {
        return T();
    }

    virtual T visit_bit_atom( IntegerAtom* )
    {
        return T();
    }

    virtual T visit_floating_atom( FloatingAtom* )
    {
        return T();
    }

    virtual T visit_rational_atom( RationalAtom* )
    {
        return T();
    }

    virtual T visit_undef_atom( UndefAtom* )
    {
        return T();
    }

    virtual T visit_function_atom( FunctionAtom*, std::vector< T >& )
    {
        return T();
    }

    virtual T visit_builtin_atom( BuiltinAtom*, std::vector< T >& )
    {
        return T();
    }

    virtual void visit_derived_function_atom_pre(
        FunctionAtom*, std::vector< T >& )
    {
    }

    virtual T visit_derived_function_atom( FunctionAtom*, U )
    {
        return T();
    }

    virtual T visit_self_atom( SelfAtom* )
    {
        return T();
    }

    virtual T visit_rule_atom( RuleAtom* )
    {
        return T();
    }

    virtual T visit_boolean_atom( BooleanAtom* )
    {
        return T();
    }

    virtual T visit_string_atom( StringAtom* )
    {
        return T();
    }

    virtual T visit_list_atom( ListAtom*, const std::vector< T >& )
    {
        return T();
    }

    virtual T visit_number_range_atom( NumberRangeAtom*, U, U )
    {
        return T();
    }
};

#endif

//
//  Local variables:
//  mode: c++
//  indent-tabs-mode: nil
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//
