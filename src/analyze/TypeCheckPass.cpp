//
//  Copyright (c) 2014-2017 CASM Organization
//  All rights reserved.
//
//  Developed by: Philipp Paulweber
//                Emmanuel Pescosta
//                Florian Hahn
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

#include "../pass/src/PassRegistry.h"
#include "../pass/src/PassResult.h"
#include "../pass/src/PassUsage.h"

#include "../Logger.h"
#include "../ast/RecursiveVisitor.h"

#include "../stdhl/cpp/String.h"

using namespace libcasm_fe;
using namespace Ast;

char TypeCheckPass::id = 0;

static libpass::PassRegistration< TypeCheckPass > PASS(
    "ASTTypeCheckPass",
    "type check of all types in the AST representation", "ast-type-chk", 0 );

class TypeCheckVisitor final : public RecursiveVisitor
{
  public:
    TypeCheckVisitor( Logger& log, Namespace& symboltable );

    void visit( VariableDefinition& node ) override;

    void visit( DirectCallExpression& node ) override;

    void visit( CaseRule& node ) override;
    void visit( LetRule& node ) override;

    void visit( BasicType& node ) override;
    void visit( ComposedType& node ) override;
    void visit( RelationType& node ) override;
    void visit( FixedSizedType& node ) override;

    void visit( ExpressionCase& node ) override;
    void visit( DefaultCase& node ) override;

  private:
    void push( VariableDefinition& identifier );
    void pop( VariableDefinition& identifier );

    Logger& m_log;
    Namespace& m_symboltable;

    std::unordered_map< std::string, VariableDefinition* > m_id2var;
    std::vector< VariableDefinition* > m_stack;
    Expression* m_caseExpr = nullptr;
};

TypeCheckVisitor::TypeCheckVisitor( Logger& log, Namespace& symboltable )
: m_log( log )
, m_symboltable( symboltable )
{
}

void TypeCheckVisitor::visit( VariableDefinition& node )
{
    RecursiveVisitor::visit( node );

    if( not node.type() and node.variableType()->type() )
    {
        node.setType( node.variableType()->type() );
    }
}

void TypeCheckVisitor::visit( DirectCallExpression& node )
{
    const auto& path = *node.identifier();

    if( not node.type() )
    {
        auto result = m_id2var.find( path.path() );
        if( result != m_id2var.end() )
        {
            node.setType( result->second->type() );
        }
        else
        {
            if( node.targetType() == CallExpression::TargetType::UNKNOWN )
            {
                assert( path.type() == IdentifierPath::Type::RELATIVE );
                assert( path.identifiers()->size() == 1 );
                // can only be a relative addressed enumeration constant

                if( not m_caseExpr )
                {
                    // we are not in a 'case' context ... check latest
                    // m_stack entry!
                    if( not m_stack.empty() and m_stack.back()->type() )
                    {
                        const auto variable = m_stack.back();

                        std::vector< std::string > parts;
                        libstdhl::String::split(
                            variable->type()->name(), ".", parts );
                        parts.emplace_back( path.baseName() );

                        try
                        {
                            auto symbol = m_symboltable.find( parts );

                            node.setTargetType( symbol.targetType() );

                            assert( symbol.targetType()
                                    == CallExpression::TargetType::CONSTANT );

                            const auto& definition = std::
                                static_pointer_cast< EnumerationDefinition >(
                                    symbol.definition() );

                            assert( definition->type() );
                            node.setType( definition->type() );
                        }
                        catch( const std::domain_error& e )
                        {
                            m_log.error( { node.sourceLocation() },
                                "unknown symbol '" + path.path() + "' found" );
                        }
                    }
                    else
                    {
                        m_log.error( { node.sourceLocation() },
                            "unable to resolve symbol '" + path.path() + "'" );
                    }
                }
                else if( m_caseExpr and m_caseExpr->type() )
                {
                    std::vector< std::string > parts;
                    libstdhl::String::split(
                        m_caseExpr->type()->name(), ".", parts );
                    parts.emplace_back( path.baseName() );

                    try
                    {
                        auto symbol = m_symboltable.find( parts );

                        node.setTargetType( symbol.targetType() );

                        assert( symbol.targetType()
                                == CallExpression::TargetType::CONSTANT );

                        const auto& type = symbol.definition()->type();
                        assert( type );
                        node.setType( type );
                    }
                    catch( const std::domain_error& e )
                    {
                        m_log.error( { node.sourceLocation() },
                            "unknown symbol '" + path.path() + "' found" );
                    }
                }
                else
                {
                    m_log.error( { node.sourceLocation() },
                        "unknown symbol '" + path.path() + "' found" );
                }
            }
            else
            {
                try
                {
                    auto symbol = m_symboltable.find( node );

                    if( node.arguments()->size() != symbol.arity() )
                    {
                        const std::unordered_map< CallExpression::TargetType,
                            Code >
                            codes = {
                                { CallExpression::TargetType::FUNCTION,
                                    Code::
                                        TypeInferenceFunctionArgumentSizeMismatch },
                                { CallExpression::TargetType::DERIVED,
                                    Code::
                                        TypeInferenceDerivedArgumentSizeMismatch },
                                { CallExpression::TargetType::BUILTIN,
                                    Code::
                                        TypeInferenceBuiltinArgumentSizeMismatch },
                                { CallExpression::TargetType::RULE,
                                    Code::
                                        TypeInferenceRuleArgumentSizeMismatch },
                            };

                        const auto code = codes.find( node.targetType() );
                        assert( code != codes.end()
                                and " invalid target type with arguments " );

                        m_log.error( { node.sourceLocation() },
                            "invalid argument size: " + node.targetTypeName()
                                + " '"
                                + path.path()
                                + "' expects "
                                + std::to_string( symbol.arity() )
                                + " arguments",
                            code->second );
                    }
                }
                catch( const std::domain_error& e )
                {
                }
            }
        }
    }

    RecursiveVisitor::visit( node );
}

void TypeCheckVisitor::visit( LetRule& node )
{
    node.variable()->accept( *this );
    push( *node.variable() );
    node.expression()->accept( *this );

    if( not node.variable()->type() and node.expression()->type() )
    {
        node.variable()->setType( node.expression()->type()->ptr_result() );
    }

    node.rule()->accept( *this );
    pop( *node.variable() );
}

void TypeCheckVisitor::visit( CaseRule& node )
{
    // check the case expression itself
    node.expression()->accept( *this );

    // set case expression and its type
    assert( not m_caseExpr );
    m_caseExpr = node.expression().get();

    // iterate only over the expressions
    node.cases()->accept( *this );

    // clear case expression and its type
    assert( m_caseExpr );
    m_caseExpr = nullptr;

    // iterate over the case expression rules
    for( auto c : *node.cases() )
    {
        c->rule()->accept( *this );
    }
}

static const std::string TYPE_STRING_RULEREF = "RuleRef";
static const std::string TYPE_STRING_FUNCREF = "FuncRef";

static const std::unordered_set< std::string > TYPE_STRINGS_FOR_REFERENCE_TYPES
    = { TYPE_STRING_RULEREF, TYPE_STRING_FUNCREF };

static const std::string TYPE_STRING_TUPLE = "Tuple";
static const std::string TYPE_STRING_LIST = "List";

static const std::unordered_set< std::string > TYPE_STRINGS_FOR_COMPOSED_TYPES
    = { TYPE_STRING_TUPLE, TYPE_STRING_LIST };

void TypeCheckVisitor::visit( BasicType& node )
{
    RecursiveVisitor::visit( node );

    if( not node.type() )
    {
        const auto& name = node.name()->baseName();

        if( TYPE_STRINGS_FOR_REFERENCE_TYPES.count( name ) )
        {
            m_log.error( { node.sourceLocation() },
                "reference type '" + name
                    + "' defined without a relation, use '"
                    + name
                    + "< /* relation type */  >'",
                Code::TypeAnnotationRelationTypeHasNoSubType );
        }
        else if( TYPE_STRINGS_FOR_COMPOSED_TYPES.count( name ) )
        {
            m_log.error( { node.sourceLocation() },
                "composed type '" + name + "' defined without sub-types, use '"
                    + name
                    + "< /* sub-type(s) */  >'",
                Code::TypeAnnotationComposedTypeHasNoSubType );
        }
        else
        {
            try
            {
                auto symbol = m_symboltable.find( node );

                assert( symbol.targetType()
                        == CallExpression::TargetType::TYPE_DOMAIN );

                const auto& type = symbol.definition()->type();
                assert( type );
                node.setType( type );
            }
            catch( const std::domain_error& e )
            {
                m_log.error( { node.sourceLocation() },
                    "unknown type '" + name + "' found",
                    Code::TypeAnnotationInvalidBasicTypeName );
            }
        }
    }
}

void TypeCheckVisitor::visit( ComposedType& node )
{
    RecursiveVisitor::visit( node );

    if( node.type() )
    {
        return;
    }

    const auto& name = node.name()->baseName();

    libcasm_ir::Types subTypeList;
    for( auto subType : *node.subTypes() )
    {
        if( not subType->type() )
        {
            m_log.info( { subType->sourceLocation() },
                "TODO: '" + name + "' has a non-typed sub type" );
            return;
        }

        subTypeList.add( subType->type() );
    }

    if( name == TYPE_STRING_TUPLE )
    {
        const auto type
            = libstdhl::make< libcasm_ir::TupleType >( subTypeList );
        node.setType( type );
    }
    else if( name == TYPE_STRING_LIST )
    {
        if( subTypeList.size() == 1 )
        {
            const auto type
                = libstdhl::make< libcasm_ir::ListType >( subTypeList[ 0 ] );
            node.setType( type );
        }
        else
        {
            m_log.error( { node.sourceLocation() },
                "composed type '" + name + "' can only have one sub-type" );
        }
    }
    else
    {
        m_log.error( { node.sourceLocation() },
            "unknown composed type '" + name + "' found",
            Code::TypeAnnotationInvalidComposedTypeName );
    }
}

void TypeCheckVisitor::visit( RelationType& node )
{
    RecursiveVisitor::visit( node );

    if( node.type() )
    {
        return;
    }

    const auto& name = node.name()->baseName();

    std::vector< libcasm_ir::Type::Ptr > argTypeList;
    for( auto argumentType : *node.argumentTypes() )
    {
        if( not argumentType->type() )
        {
            m_log.info( { argumentType->sourceLocation() },
                "TODO: '" + name + "' has a non-typed argument(s)" );
            return;
        }

        argTypeList.emplace_back( argumentType->type() );
    }

    if( name == TYPE_STRING_RULEREF )
    {
        if( node.returnType()->type() )
        {
            const auto type = libstdhl::make< libcasm_ir::RuleReferenceType >(
                node.returnType()->type(), argTypeList );
            node.setType( type );
        }
    }
    else if( name == TYPE_STRING_FUNCREF )
    {
        if( node.returnType()->type() )
        {
            const auto type
                = libstdhl::make< libcasm_ir::FunctionReferenceType >(
                    node.returnType()->type(), argTypeList );
            node.setType( type );
        }
    }
    else
    {
        m_log.error( { node.sourceLocation() },
            "unknown relation type '" + name + "' found",
            Code::TypeAnnotationInvalidRelationTypeName );
    }
}

void TypeCheckVisitor::visit( FixedSizedType& node )
{
    RecursiveVisitor::visit( node );

    if( not node.type() )
    {
        const auto& name = node.name()->baseName();
        auto& expr = *node.size();

        if( name.compare( "Bit" ) == 0 )
        {
            if( expr.id() == Node::ID::VALUE_ATOM and expr.type()->isInteger() )
            {
                const auto& atom = static_cast< const ValueAtom& >( expr );

                const auto value
                    = std::static_pointer_cast< libcasm_ir::IntegerConstant >(
                        atom.value() );

                try
                {
                    auto type = libstdhl::get< libcasm_ir::BitType >( value );
                    node.setType( type );
                }
                catch( const std::domain_error& e )
                {
                    m_log.error( { expr.sourceLocation() }, e.what(),
                        Code::TypeBitSizeIsInvalid );
                }
            }
            else
            {
                m_log.error( { expr.sourceLocation() },
                    "unsupported expr for 'Bit' type, constant Integer value "
                    "expected" );
            }
        }
        else if( name.compare( "Integer" ) == 0 )
        {
            if( expr.id() == Node::ID::RANGE_EXPRESSION )
            {
                const auto& range_expr
                    = static_cast< const RangeExpression& >( expr );

                const auto& lhs = *range_expr.left();
                const auto& rhs = *range_expr.right();

                if( lhs.id() == Node::ID::VALUE_ATOM and lhs.type()->isInteger()
                    and rhs.id() == Node::ID::VALUE_ATOM
                    and rhs.type()->isInteger() )
                {
                    const auto ir_lhs = std::
                        static_pointer_cast< libcasm_ir::IntegerConstant >(
                            static_cast< const ValueAtom& >( lhs ).value() );

                    const auto ir_rhs = std::
                        static_pointer_cast< libcasm_ir::IntegerConstant >(
                            static_cast< const ValueAtom& >( rhs ).value() );

                    auto range
                        = libstdhl::make< libcasm_ir::Range >( ir_lhs, ir_rhs );

                    auto range_type
                        = libstdhl::get< libcasm_ir::RangeType >( range );

                    assert( not expr.type() );
                    expr.setType( range_type );

                    try
                    {
                        auto type = libstdhl::get< libcasm_ir::IntegerType >(
                            range_type );

                        node.setType( type );
                    }
                    catch( const std::domain_error& e )
                    {
                        m_log.error( { expr.sourceLocation() }, e.what() );
                    }
                }
            }
            else
            {
                m_log.error( { expr.sourceLocation() },
                    "unsupported expr for 'Integer' type, only range "
                    "expressions are allowed, e.g. `Integer'[5..10]`" );
            }
        }
        else
        {
            m_log.error( { node.sourceLocation() },
                "unknown type '" + name + "' found",
                Code::TypeAnnotationInvalidFixedSizeTypeName );
        }
    }
}

void TypeCheckVisitor::visit( ExpressionCase& node )
{
    // omit redundant traversal of rule(), see visit( CaseRule& )
    node.expression()->accept( *this );
}

void TypeCheckVisitor::visit( DefaultCase& node )
{
    // omit redundant traversal of rule(), see visit( CaseRule& )
}

void TypeCheckVisitor::push( VariableDefinition& node )
{
    const auto& name = node.identifier()->name();

    auto result = m_id2var.emplace( name, &node );
    assert( result.second && "symbol already defined!" );
    m_stack.push_back( &node );
}

void TypeCheckVisitor::pop( VariableDefinition& node )
{
    const auto& name = node.identifier()->name();

    if( m_id2var.erase( name ) != 1 )
    {
        assert( !" internal error! " );
    }
    assert( m_stack.back() == &node );
    m_stack.pop_back();
}

void TypeCheckPass::usage( libpass::PassUsage& pu )
{
    pu.require< SymbolResolverPass >();
}

u1 TypeCheckPass::run( libpass::PassResult& pr )
{
    Logger log( &id, stream() );

    const auto data = pr.result< SymbolResolverPass >();
    const auto specification = data->specification();

    TypeCheckVisitor visitor( log, *specification->symboltable() );
    specification->definitions()->accept( visitor );

#ifndef NDEBUG
    log.debug( "symbol table = \n" + specification->symboltable()->dump() );
#endif

    const auto errors = log.errors();
    if( errors > 0 )
    {
        log.debug( "found %lu error(s) during type checking", errors );
        return false;
    }

    pr.setResult< TypeCheckPass >( data );

    return true;
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
