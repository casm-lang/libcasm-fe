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

#include "TypeInferencePass.h"

#include "../pass/src/PassRegistry.h"
#include "../pass/src/PassResult.h"
#include "../pass/src/PassUsage.h"

#include "../Logger.h"
#include "../ast/RecursiveVisitor.h"

#include "../stdhl/cpp/String.h"

#include "../casm-ir/src/Builtin.h"

using namespace libcasm_fe;
using namespace Ast;

char TypeInferencePass::id = 0;

static libpass::PassRegistration< TypeInferencePass > PASS(
    "ASTTypeInferencePass",
    "type inference of all types in the AST representation", "ast-infer", 0 );

//
// TypeCheckVisitor
//

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
    std::stack< VariableDefinition* > m_stack;
    Expression* m_caseExpr = nullptr;
};

static const auto VOID = libstdhl::get< libcasm_ir::VoidType >();
static const auto RULEREF = libstdhl::get< libcasm_ir::RuleReferenceType >();
static const auto BOOLEAN = libstdhl::get< libcasm_ir::BooleanType >();
static const auto INTEGER = libstdhl::get< libcasm_ir::IntegerType >();
static const auto BIT_1 = libstdhl::get< libcasm_ir::BitType >( 1 );
static const auto STRING = libstdhl::get< libcasm_ir::StringType >();
static const auto FLOATING = libstdhl::get< libcasm_ir::FloatingType >();
static const auto RATIONAL = libstdhl::get< libcasm_ir::RationalType >();

static const std::unordered_map< std::string, libcasm_ir::Type::Ptr > basicTypes
    = {
        { "Void", VOID },

        { "Boolean", BOOLEAN },

        { "Integer", INTEGER },

        { "Bit", BIT_1 },

        { "String", STRING },

        { "Floating", FLOATING },

        { "Rational", RATIONAL },
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
                    if( not m_stack.empty() )
                    {
                        const auto variable = m_stack.top();

                        const auto searchPath
                            = Ast::make< Identifiers >( node.sourceLocation() );

                        for( auto i :
                            *variable->variableType()->name()->identifiers() )
                        {
                            searchPath->add( i );
                        }

                        for( auto i : *path.identifiers() )
                        {
                            searchPath->add( i );
                        }

                        IdentifierPath identifierSearchPath(
                            searchPath, IdentifierPath::Type::ABSOLUTE );

                        try
                        {
                            auto symbol
                                = m_symboltable.find( identifierSearchPath );

                            node.setTargetType( symbol.targetType() );

                            assert( symbol.targetType()
                                    == CallExpression::TargetType::CONSTANT );

                            auto& definition
                                = static_cast< EnumerationDefinition& >(
                                    symbol.definition() );

                            assert( definition.type() );
                            node.setType( definition.type() );
                        }
                        catch( const std::domain_error& e )
                        {
                            m_log.error( { node.sourceLocation() },
                                "unable to find symbol '"
                                    + identifierSearchPath.path()
                                    + "'" );
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

                        auto& definition
                            = static_cast< EnumerationDefinition& >(
                                symbol.definition() );

                        assert( definition.type() );
                        node.setType( definition.type() );
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
        }
    }

    // assert( node.targetType() != CallExpression::TargetType::UNKNOWN );

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

void TypeCheckVisitor::visit( BasicType& node )
{
    if( not node.type() )
    {
        const auto& name = node.name()->baseName();

        auto result = basicTypes.find( name );
        if( result != basicTypes.end() )
        {
            node.setType( result->second );
        }
        else if( name.compare( "Agent" ) == 0 )
        {
            auto symbol = m_symboltable.find( "self" );
            assert(
                symbol.targetType() == CallExpression::TargetType::FUNCTION );
            auto& definition
                = static_cast< FunctionDefinition& >( symbol.definition() );

            if( not definition.returnType()->type() )
            {
                auto kind
                    = libstdhl::make< libcasm_ir::Enumeration >( "Agent" );

                kind->add( "default" );

                const auto type
                    = libstdhl::make< libcasm_ir::EnumerationType >( kind );

                definition.returnType()->setType( type );
            }

            node.setType( definition.returnType()->type() );
        }
        else if( name.compare( "RuleRef" ) == 0
                 or name.compare( "FuncRef" ) == 0 )
        {
            m_log.error( { node.sourceLocation() },
                "reference type '" + name + "' defined without relation" );
        }
        else
        {
            try
            {
                auto symbol = m_symboltable.find( node );

                assert( symbol.targetType()
                        == CallExpression::TargetType::ENUMERATION );

                auto& definition = static_cast< EnumerationDefinition& >(
                    symbol.definition() );

                assert( definition.type() );

                node.setType( definition.type() );
            }
            catch( const std::domain_error& e )
            {
                m_log.error( { node.sourceLocation() },
                    "unknown type '" + name + "' found" );
            }
        }
    }

    RecursiveVisitor::visit( node );
}

void TypeCheckVisitor::visit( ComposedType& node )
{
    RecursiveVisitor::visit( node );

    if( node.type() )
    {
        return;
    }

    const auto& name = node.name()->baseName();

    std::vector< libcasm_ir::Type::Ptr > subTypeList;
    for( auto subType : *node.subTypes() )
    {
        if( not subType->type() )
        {
            m_log.info( { subType->sourceLocation() },
                "TODO: '" + name + "' has a non-typed sub type" );
            return;
        }

        subTypeList.emplace_back( subType->type() );
    }

    // if( name.compare( "Tuple" ) == 0 )
    // {
    // }
    // else if( name.compare( "List" ) == 0 )
    // {
    // }
    // else
    {
        m_log.error( { node.sourceLocation() },
            "unknown composed type '" + name + "' found" );
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

    if( name.compare( "RuleRef" ) == 0 )
    {
        if( node.returnType()->type() )
        {
            const auto type = libstdhl::make< libcasm_ir::RuleReferenceType >(
                node.returnType()->type(), argTypeList );
            node.setType( type );
        }
    }
    else if( name.compare( "FuncRef" ) == 0 )
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
            "unknown relation type '" + name + "' found" );
    }
}

void TypeCheckVisitor::visit( FixedSizedType& node )
{
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
                    m_log.error( { expr.sourceLocation() }, e.what() );
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
                    const auto& atom_lhs
                        = static_cast< const ValueAtom& >( lhs );

                    const auto& atom_rhs
                        = static_cast< const ValueAtom& >( rhs );

                    const auto ir_lhs = std::
                        static_pointer_cast< libcasm_ir::IntegerConstant >(
                            atom_lhs.value() );

                    const auto ir_rhs = std::
                        static_pointer_cast< libcasm_ir::IntegerConstant >(
                            atom_rhs.value() );

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
                "unknown type '" + name + "' found" );
        }
    }

    RecursiveVisitor::visit( node );
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
    if( not result.second )
    {
        m_log.error( { node.sourceLocation() },
            "symbol '" + name + "' already defined" );
    }
    m_stack.push( &node );
}

void TypeCheckVisitor::pop( VariableDefinition& node )
{
    const auto& name = node.identifier()->name();

    if( m_id2var.erase( name ) != 1 )
    {
        assert( !" internal error! " );
    }
    assert( m_stack.top() == &node );
    m_stack.pop();
}

//
// TypeInferenceVisitor
//

class TypeInferenceVisitor final : public RecursiveVisitor
{
  public:
    TypeInferenceVisitor( Logger& log, Namespace& symboltable );

    void visit( FunctionDefinition& node ) override;
    void visit( DerivedDefinition& node ) override;
    void visit( RuleDefinition& node ) override;

    void visit( UndefAtom& node ) override;
    void visit( ValueAtom& node ) override;
    void visit( ReferenceAtom& node ) override;
    void visit( DirectCallExpression& node ) override;
    void visit( IndirectCallExpression& node ) override;
    void visit( UnaryExpression& node ) override;
    void visit( BinaryExpression& node ) override;
    void visit( RangeExpression& node ) override;
    void visit( ListExpression& node ) override;
    void visit( ConditionalExpression& node ) override;
    void visit( UniversalQuantifierExpression& node ) override;
    void visit( ExistentialQuantifierExpression& node ) override;

    void visit( ConditionalRule& node ) override;
    void visit( CaseRule& node ) override;
    void visit( LetRule& node ) override;
    void visit( ForallRule& node ) override;
    void visit( UpdateRule& node ) override;

    void assignment( const Node& node, TypedNode& lhs, TypedNode& rhs,
        const std::string& dst, const std::string& src, const Code& dstErr,
        const Code& srcErr, const Code& assignmentErr );

    const libcasm_ir::Annotation* annotate(
        Node& node, const std::vector< Expression::Ptr >& expressions = {} );

    void inference( const std::string& description,
        const libcasm_ir::Annotation* annotation, TypedNode& node,
        const std::vector< Expression::Ptr >& arguments = {} );

    void inference( FunctionDefinition& node );
    void inference( DerivedDefinition& node,
        const std::vector< Expression::Ptr >& arguments );
    void inference(
        RuleDefinition& node, const std::vector< Expression::Ptr >& arguments );

    void inference( QuantifierExpression& node );

    void push( VariableDefinition& node );
    void pop( VariableDefinition& node );
    VariableDefinition& find( const IdentifierPath& node );

  private:
    Logger& m_log;
    Namespace& m_symboltable;
    u1 m_functionInitially;

    std::unordered_map< std::string, VariableDefinition* > m_id2var;

    std::unordered_map< const Node*, std::vector< libcasm_ir::Type::ID > >
        m_resultTypes;
};

TypeInferenceVisitor::TypeInferenceVisitor(
    Logger& log, Namespace& symboltable )
: m_log( log )
, m_symboltable( symboltable )
, m_functionInitially( false )
{
}

void TypeInferenceVisitor::visit( FunctionDefinition& node )
{
    m_functionInitially = true;

    RecursiveVisitor::visit( node );

    m_functionInitially = false;

    inference( node );
}

void TypeInferenceVisitor::visit( DerivedDefinition& node )
{
    for( const auto& argument : *node.arguments() )
    {
        push( *argument );
    }

    const auto type = node.returnType()->type();
    assert( type );
    m_resultTypes[ node.expression().get() ].emplace_back( type->id() );

    inference( node, {} );

    for( const auto& argument : *node.arguments() )
    {
        pop( *argument );
    }
}

void TypeInferenceVisitor::visit( RuleDefinition& node )
{
    for( const auto& argument : *node.arguments() )
    {
        push( *argument );
    }

    inference( node, {} );

    for( const auto& argument : *node.arguments() )
    {
        pop( *argument );
    }
}

void TypeInferenceVisitor::visit( UndefAtom& node )
{
    RecursiveVisitor::visit( node );

    auto result = m_resultTypes.find( &node );
    if( result != m_resultTypes.end() and result->second.size() == 1 )
    {
        inference( "undef atom", 0, node );
    }
}

void TypeInferenceVisitor::visit( ValueAtom& node )
{
    RecursiveVisitor::visit( node );

    auto result = m_resultTypes.find( &node );
    assert( node.value() and node.type() );

    std::vector< libcasm_ir::Type::ID > ty = { node.type()->id() };
    std::vector< libcasm_ir::Type::ID > tmp = {};

    if( result != m_resultTypes.end() )
    {
        std::set_intersection( result->second.begin(), result->second.end(),
            ty.begin(), ty.end(), std::back_inserter( tmp ) );
    }
    else
    {
        std::set_intersection( tmp.begin(), tmp.end(), ty.begin(), ty.end(),
            std::back_inserter( tmp ) );
    }

    m_resultTypes[&node ] = std::move( tmp );
}

void TypeInferenceVisitor::visit( ReferenceAtom& node )
{
    RecursiveVisitor::visit( node );

    assert( not node.type() );
    try
    {
        auto symbol = m_symboltable.find( *node.identifier() );

        switch( symbol.targetType() )
        {
            case CallExpression::TargetType::FUNCTION:
            {
                auto& definition
                    = static_cast< FunctionDefinition& >( symbol.definition() );

                inference( definition );
                assert( definition.type() and definition.type()->isRelation() );

                const auto type
                    = libstdhl::make< libcasm_ir::FunctionReferenceType >(
                        std::static_pointer_cast< libcasm_ir::RelationType >(
                            definition.type() ) );
                node.setType( type );

                node.setReferenceType( ReferenceAtom::ReferenceType::FUNCTION );
                node.setReference( definition.ptr< FunctionDefinition >() );
                break;
            }
            case CallExpression::TargetType::DERIVED:
            {
                auto& definition
                    = static_cast< DerivedDefinition& >( symbol.definition() );

                inference( definition, {} );
                assert( definition.type() and definition.type()->isRelation() );

                const auto type
                    = libstdhl::make< libcasm_ir::RuleReferenceType >(
                        std::static_pointer_cast< libcasm_ir::RelationType >(
                            definition.type() ) );
                node.setType( type );

                node.setReferenceType( ReferenceAtom::ReferenceType::DERIVED );
                node.setReference( definition.ptr< DerivedDefinition >() );
                break;
            }
            case CallExpression::TargetType::BUILTIN:
            {
                // TODO

                // node.setReferenceType(
                // ReferenceAtom::ReferenceType::BUILTIN
                // );
                // node.setBuiltinId( annotation.id() );
                break;
            }
            case CallExpression::TargetType::RULE:
            {
                auto& definition
                    = static_cast< RuleDefinition& >( symbol.definition() );

                inference( definition, {} );
                assert( definition.type() and definition.type()->isRelation() );

                const auto type
                    = libstdhl::make< libcasm_ir::RuleReferenceType >(
                        std::static_pointer_cast< libcasm_ir::RelationType >(
                            definition.type() ) );
                node.setType( type );

                node.setReferenceType( ReferenceAtom::ReferenceType::RULE );
                node.setReference( definition.ptr< RuleDefinition >() );
                break;
            }
            case CallExpression::TargetType::VARIABLE:
            {
                // TODO
                break;
            }
            default:
            {
                m_log.error( { node.sourceLocation() },
                    "cannot reference '" + CallExpression::targetTypeString(
                                               symbol.targetType() )
                        + "'" );
            }
        }
    }
    catch( const std::domain_error& e )
    {
        if( not m_functionInitially )
        {
            assert( !" inconsistent symbol table! " );
        }
    }
}

void TypeInferenceVisitor::visit( DirectCallExpression& node )
{
    const auto& path = *node.identifier();

    const libcasm_ir::Annotation* annotation
        = annotate( node, node.arguments()->data() );

    RecursiveVisitor::visit( node );

    switch( node.targetType() )
    {
        case CallExpression::TargetType::VARIABLE:
        {
            try
            {
                auto& definition = find( *node.identifier() );

                if( definition.type() )
                {
                    if( not node.type() )
                    {
                        node.setType( definition.type() );
                    }
                    else
                    {
                        assert( *definition.type() == *node.type() );
                    }
                }
                else
                {
                    if( not node.type() )
                    {
                        const auto description
                            = "variable '" + path.path() + "'";
                        inference( description, 0, node );
                    }

                    definition.setType( node.type() );
                }
            }
            catch( const std::domain_error& e )
            {
                assert( !" inconsistent symbol table! " );
            }
            break;
        }
        case CallExpression::TargetType::BUILTIN:
        {
            const auto description = "built-in '" + path.path() + "'";
            inference(
                description, annotation, node, node.arguments()->data() );

            std::vector< libcasm_ir::Type::Ptr > argTypeList;
            for( auto argumentType : *node.arguments() )
            {
                if( not argumentType->type() )
                {
                    m_log.debug( { argumentType->sourceLocation() },
                        "TODO: '" + path.path()
                            + "' has a non-typed argument(s)" );
                    return;
                }

                argTypeList.emplace_back( argumentType->type()->ptr_result() );
            }

            if( node.type() )
            {
                const auto type = libstdhl::make< libcasm_ir::RelationType >(
                    node.type(), argTypeList );

                node.setType( type );
            }
            break;
        }
        case CallExpression::TargetType::DERIVED:
        {
            assert( not node.type() );
            try
            {
                auto symbol = m_symboltable.find( node );
                assert( symbol.targetType()
                        == CallExpression::TargetType::DERIVED );

                auto& definition
                    = static_cast< DerivedDefinition& >( symbol.definition() );

                inference( definition, node.arguments()->data() );
                node.setType( definition.type() );
            }
            catch( const std::domain_error& e )
            {
                assert( !" inconsistent symbol table! " );
            }
            break;
        }
        case CallExpression::TargetType::FUNCTION:
        {
            assert( not node.type() );
            try
            {
                auto symbol = m_symboltable.find( node );
                assert( symbol.targetType()
                        == CallExpression::TargetType::FUNCTION );

                auto& definition
                    = static_cast< FunctionDefinition& >( symbol.definition() );

                inference( definition );
                node.setType( definition.type() );
            }
            catch( const std::domain_error& e )
            {
                assert( !" inconsistent symbol table! " );
            }
            break;
        }
        case CallExpression::TargetType::RULE:
        {
            assert( not node.type() );
            try
            {
                auto symbol = m_symboltable.find( node );
                assert(
                    symbol.targetType() == CallExpression::TargetType::RULE );

                auto& definition
                    = static_cast< RuleDefinition& >( symbol.definition() );

                inference( definition, node.arguments()->data() );
                node.setType( definition.type() );
            }
            catch( const std::domain_error& e )
            {
                assert( !" inconsistent symbol table! " );
            }
            break;
        }
        case CallExpression::TargetType::ENUMERATION:
        {
            if( not node.type() )
            {
                m_log.error( { node.sourceLocation() }, "TODO: ENUMERATION" );
            }
            break;
        }
        case CallExpression::TargetType::CONSTANT:
        {
            if( not node.type() )
            {
                m_log.error( { node.sourceLocation() }, "TODO: CONSTANT" );
            }
            break;
        }
        case CallExpression::TargetType::UNKNOWN:
        {
            assert( !" internal error" );
            break;
        }
    }
}

void TypeInferenceVisitor::visit( IndirectCallExpression& node )
{
    RecursiveVisitor::visit( node );

    if( not node.expression()->type() )
    {
        m_log.error( { node.sourceLocation() },
            "unable to resolve type of indirect call expression" );
    }

    node.setType( node.expression()->type() );
}

void TypeInferenceVisitor::visit( UnaryExpression& node )
{
    const auto* annotation = annotate( node, { node.expression() } );

    RecursiveVisitor::visit( node );

    const auto description
        = "operator '" + libcasm_ir::Value::token( node.op() ) + "'";
    inference( description, annotation, node, { node.expression() } );
}

void TypeInferenceVisitor::visit( BinaryExpression& node )
{
    const auto* annotation = annotate( node, { node.left(), node.right() } );

    RecursiveVisitor::visit( node );

    const auto description
        = "operator '" + libcasm_ir::Value::token( node.op() ) + "'";
    inference( description, annotation, node, { node.left(), node.right() } );
}

void TypeInferenceVisitor::visit( RangeExpression& node )
{
    RecursiveVisitor::visit( node );

    const auto& lhs = *node.left();
    const auto& rhs = *node.right();

    if( *lhs.type() != *rhs.type() )
    {
        m_log.error(
            { node.sourceLocation() }, "types of range does not match" );
        return;
    }

    const auto range_type
        = libstdhl::get< libcasm_ir::RangeType >( lhs.type() );

    node.setType( range_type );
}
void TypeInferenceVisitor::visit( ListExpression& node )
{
    RecursiveVisitor::visit( node );
}
void TypeInferenceVisitor::visit( ConditionalExpression& node )
{
    const auto& resTypes = m_resultTypes[&node ];
    for( auto type : resTypes )
    {
        m_resultTypes[ node.thenExpression().get() ].emplace_back( type );
        m_resultTypes[ node.elseExpression().get() ].emplace_back( type );
    }

    RecursiveVisitor::visit( node );

    const auto& condExpr = *node.condition();
    auto& thenExpr = *node.thenExpression();
    auto& elseExpr = *node.elseExpression();

    if( condExpr.type() )
    {
        if( *condExpr.type() != *BOOLEAN )
        {
            m_log.error( { condExpr.sourceLocation() },
                "condition type of conditional expression is not of type "
                "'Boolean', "
                "found type '"
                    + condExpr.type()->description()
                    + "'",
                Code::TypeInferenceInvalidConditionalExpressionCondition );
        }
    }

    if( resTypes.size() > 0 )
    {
        inference( "conditional expression", 0, node );
    }

    if( thenExpr.type() and elseExpr.type() )
    {
        if( *thenExpr.type() != *elseExpr.type() )
        {
            m_log.error(
                { thenExpr.sourceLocation(), elseExpr.sourceLocation() },
                "types of conditional expression paths does not match, "
                "found type '"
                    + thenExpr.type()->description()
                    + "' at 'then' path, and type '"
                    + elseExpr.type()->description()
                    + "' at 'else' path",
                Code::TypeInferenceInvalidConditionalExpressionPaths );
            return;
        }
    }

    if( thenExpr.type() and elseExpr.id() == Node::ID::UNDEF_ATOM )
    {
        elseExpr.setType( thenExpr.type() );
    }

    if( thenExpr.id() == Node::ID::UNDEF_ATOM and elseExpr.type() )
    {
        thenExpr.setType( elseExpr.type() );
    }

    if( node.type() and thenExpr.id() == Node::ID::UNDEF_ATOM
        and elseExpr.id() == Node::ID::UNDEF_ATOM )
    {
        thenExpr.setType( node.type() );
        elseExpr.setType( node.type() );
    }

    if( not node.type() )
    {
        node.setType( thenExpr.type() );
    }
}

void TypeInferenceVisitor::visit( UniversalQuantifierExpression& node )
{
    inference( node );
}

void TypeInferenceVisitor::visit( ExistentialQuantifierExpression& node )
{
    inference( node );
}

void TypeInferenceVisitor::visit( ConditionalRule& node )
{
    RecursiveVisitor::visit( node );

    const auto& condExpr = *node.condition();

    if( condExpr.type() )
    {
        if( condExpr.type()->result() != *BOOLEAN )
        {
            m_log.error( { condExpr.sourceLocation() },
                "invalid condition type '"
                    + condExpr.type()->result().description()
                    + ", shall be '"
                    + BOOLEAN->description()
                    + "'",
                Code::TypeInferenceConditionalRuleInvalidConditionType );
        }
    }
}

void TypeInferenceVisitor::visit( CaseRule& node )
{
    RecursiveVisitor::visit( node );
}

void TypeInferenceVisitor::visit( LetRule& node )
{
    node.variable()->accept( *this );

    if( node.variable()->type() )
    {
        m_resultTypes[ node.expression().get() ].emplace_back(
            node.variable()->type()->id() );
    }

    push( *node.variable() );
    node.expression()->accept( *this );

    if( not node.variable()->type() and node.expression()->type() )
    {
        node.variable()->setType( node.expression()->type()->ptr_result() );
    }

    node.rule()->accept( *this );
    pop( *node.variable() );

    assignment( node, *node.variable(), *node.expression(),
        "let variable '" + node.variable()->identifier()->name() + "'",
        "let expression", Code::TypeInferenceInvalidLetRuleVariableType,
        Code::TypeInferenceInvalidLetRuleExpressionType,
        Code::TypeInferenceLetRuleTypesMismatch );
}
void TypeInferenceVisitor::visit( ForallRule& node )
{
    node.universe()->accept( *this );

    if( node.universe()->type() )
    {
        node.variable()->setType( node.universe()->type()->ptr_result() );
    }

    push( *node.variable() );

    node.variable()->accept( *this );
    node.rule()->accept( *this );

    pop( *node.variable() );
}
void TypeInferenceVisitor::visit( UpdateRule& node )
{
    node.function()->accept( *this );

    if( node.function()->type() )
    {
        m_resultTypes[ node.expression().get() ].emplace_back(
            node.function()->type()->result().id() );
    }

    node.expression()->accept( *this );

    assignment( node, *node.function(), *node.expression(), "updated function",
        "updating expression", Code::TypeInferenceInvalidUpdateRuleFunctionType,
        Code::TypeInferenceInvalidUpdateRuleExpressionType,
        Code::TypeInferenceUpdateRuleTypesMismatch );
}

void TypeInferenceVisitor::assignment( const Node& node, TypedNode& lhs,
    TypedNode& rhs, const std::string& dst, const std::string& src,
    const Code& dstErr, const Code& srcErr, const Code& assignmentErr )
{
    if( lhs.type()
        and not rhs.type() ) // and rhs.id() == Node::ID::UNDEF_ATOM and  )
    {
        rhs.setType( lhs.type()->ptr_result() );
    }

    const auto error_count = m_log.errors();

    if( not lhs.type() )
    {
        m_log.error( { lhs.sourceLocation() }, "unable to infer type of " + dst,
            dstErr );
    }

    if( not rhs.type() )
    {
        m_log.error( { rhs.sourceLocation() }, "unable to infer type of " + src,
            srcErr );
    }

    if( error_count != m_log.errors() )
    {
        return;
    }

    if( lhs.type()->result() != rhs.type()->result() )
    {
        m_log.error( { lhs.sourceLocation(), rhs.sourceLocation() },
            "type of " + dst + " does not match type of " + src + ": '"
                + lhs.type()->description()
                + "' != '"
                + rhs.type()->description()
                + "'",
            assignmentErr );
    }
}

const libcasm_ir::Annotation* TypeInferenceVisitor::annotate(
    Node& node, const std::vector< Expression::Ptr >& expressions )
{
    const libcasm_ir::Annotation* annotation = nullptr;

    auto result = m_resultTypes.find( &node );

    if( node.id() == Type::ID::UNARY_EXPRESSION )
    {
        annotation = &libcasm_ir::Annotation::find(
            static_cast< const UnaryExpression& >( node ).op() );
    }
    else if( node.id() == Type::ID::BINARY_EXPRESSION )
    {
        annotation = &libcasm_ir::Annotation::find(
            static_cast< const UnaryExpression& >( node ).op() );
    }
    else if( node.id() == Type::ID::DIRECT_CALL_EXPRESSION )
    {

        auto& directCall = static_cast< DirectCallExpression& >( node );
        const auto& path = *directCall.identifier();

        switch( directCall.targetType() )
        {
            case CallExpression::TargetType::VARIABLE:
            {
                break;
            }
            case CallExpression::TargetType::BUILTIN:
            {
                try
                {
                    const auto& builtin_annotation
                        = libcasm_ir::Annotation::find( path.baseName() );

                    annotation = &builtin_annotation;
                    directCall.setTargetBuiltinId( builtin_annotation.id() );

                    if( builtin_annotation.id()
                        == libcasm_ir::Value::AS_BIT_BUILTIN )
                    {
                        const auto& asbit_args = directCall.arguments()->data();
                        assert( asbit_args.size() == 2 );
                        const auto& asbit_size
                            = static_cast< const ValueAtom& >(
                                *asbit_args[ 1 ] );
                        if( asbit_size.id() == Node::ID::VALUE_ATOM
                            and asbit_size.type()
                            and asbit_size.type()->id()
                                    == libcasm_ir::Type::INTEGER )
                        {
                            const auto asbit_size_value
                                = std::static_pointer_cast< libcasm_ir::
                                        IntegerConstant >( asbit_size.value() );

                            const auto type
                                = libstdhl::get< libcasm_ir::BitType >(
                                    asbit_size_value );
                            directCall.setType( type );
                        }
                        else
                        {
                            m_log.error( { directCall.arguments()->data()[ 1 ]->sourceLocation() },
                             "2nd argument of built-in '"
                             + path.path()
                                         + "' is required to be a compile time 'Integer' constant value", Code::TypeInferenceBuiltinAsBitInvalid2ndArgumentType );
                        }
                    }
                }
                catch( const std::domain_error& e )
                {
                    m_log.error( { directCall.sourceLocation() },
                             "unable to resolve built-in symbol '"
                             + path.path()
                             + "', due to missing annotation information from 'libcasm-ir'" );
                }
                break;
            }
            case CallExpression::TargetType::DERIVED:  // [[fallthrough]]
            case CallExpression::TargetType::FUNCTION: // [[fallthrough]]
            case CallExpression::TargetType::RULE:
            {
                try
                {
                    auto symbol = m_symboltable.find( path );
                    auto& definition = symbol.definition();

                    if( definition.type() )
                    {
                        for( std::size_t c = 0; c < expressions.size(); c++ )
                        {
                            std::vector< libcasm_ir::Type::ID > ty
                                = { definition.type()->arguments()[ c ]->id() };
                            std::vector< libcasm_ir::Type::ID > tmp = {};

                            std::copy( ty.begin(), ty.end(),
                                std::back_inserter(
                                    m_resultTypes[ expressions[ c ].get() ] ) );
                        }

                        std::vector< libcasm_ir::Type::ID > ty
                            = { definition.type()->result().id() };
                        std::vector< libcasm_ir::Type::ID > tmp = {};

                        if( result != m_resultTypes.end() )
                        {
                            std::set_intersection( result->second.begin(),
                                result->second.end(), ty.begin(), ty.end(),
                                std::back_inserter( tmp ) );
                        }
                        else
                        {
                            std::set_intersection( tmp.begin(), tmp.end(),
                                ty.begin(), ty.end(),
                                std::back_inserter( tmp ) );
                        }

                        m_resultTypes[&node ] = std::move( tmp );
                    }
                }
                catch( const std::domain_error& e )
                {
                    assert( !" inconsistent symbol table! " );
                }

                break;
            }
            case CallExpression::TargetType::ENUMERATION: // [[fallthrough]]
            case CallExpression::TargetType::CONSTANT:
            {
                break;
            }
            case CallExpression::TargetType::UNKNOWN:
            {
                assert( !" internal error" );
                break;
            }
        }
    }

    if( annotation )
    {
        if( result != m_resultTypes.end() )
        {
            const auto& map = annotation->map();

            for( auto t : result->second )
            {
                try
                {
                    const auto& map_result = map.at( t );

                    for( std::size_t c = 0; c < expressions.size(); c++ )
                    {
                        const auto& map_expr = map_result.at( c );

                        std::copy( map_expr.begin(), map_expr.end(),
                            std::back_inserter(
                                m_resultTypes[ expressions[ c ].get() ] ) );
                    }
                }
                catch( const std::out_of_range& e )
                {
                    continue;
                }
            }

            const auto& map_res = annotation->resultTypes();
            std::vector< libcasm_ir::Type::ID > tmp = {};

            std::set_intersection( result->second.begin(), result->second.end(),
                map_res.begin(), map_res.end(), std::back_inserter( tmp ) );

            m_resultTypes[&node ] = std::move( tmp );
        }
        else
        {
            for( std::size_t c = 0; c < expressions.size(); c++ )
            {
                const auto& map_expr = annotation->argumentTypes( c );

                std::copy( map_expr.begin(), map_expr.end(),
                    std::back_inserter(
                        m_resultTypes[ expressions[ c ].get() ] ) );
            }

            const auto& map_res = annotation->resultTypes();

            std::copy( map_res.begin(), map_res.end(),
                std::back_inserter( m_resultTypes[&node ] ) );
        }
    }

    return annotation;
}

void TypeInferenceVisitor::inference( const std::string& description,
    const libcasm_ir::Annotation* annotation, TypedNode& node,
    const std::vector< Expression::Ptr >& arguments )
{
    auto result = m_resultTypes.find( &node );
    if( result == m_resultTypes.end() )
    {
        m_log.error( { node.sourceLocation() },
            "unable to find type annotation for " + description );
        return;
    }

    if( annotation )
    {
        std::size_t pos = -1;
        std::size_t idx = 0;

        std::vector< libcasm_ir::Type::ID > argTypes;

        for( auto argument : arguments )
        {
            if( not argument->type() )
            {
                auto argTy = m_resultTypes.find( argument.get() );
                if( argTy != m_resultTypes.end() and argTy->second.size() == 1 )
                {
                    argTypes.emplace_back( *argTy->second.begin() );
                }
                else
                {
                    pos = idx;
                    argTypes.emplace_back( libcasm_ir::Type::ID::_TOP_ );
                }
            }
            else
            {
                const auto tid = argument->type()->result().id();
                argTypes.emplace_back( tid );
            }
            idx++;
        }

        try
        {
            const auto relation = annotation->resultTypeForRelation( argTypes );

            if( relation )
            {
                const std::vector< libcasm_ir::Type::ID > inf
                    = { relation->result };
                std::vector< libcasm_ir::Type::ID > tmp = {};

                std::set_intersection( result->second.begin(),
                    result->second.end(), inf.begin(), inf.end(),
                    std::back_inserter( tmp ) );

                m_resultTypes[&node ] = std::move( tmp );

                if( pos != -1
                    and arguments[ pos ]->id() == Node::ID::UNDEF_ATOM )
                {
                    auto undefAtom
                        = static_cast< UndefAtom* >( arguments[ pos ].get() );

                    m_resultTypes[ undefAtom ] = { relation->argument[ pos ] };
                    inference( "undef", 0, *undefAtom );
                }
            }
        }
        catch( const std::invalid_argument& e )
        {
            m_log.error( { node.sourceLocation() },
                "unable to infer result type of " + description );
        }
    }

    const auto& resTypes = m_resultTypes[&node ];

    if( resTypes.size() != 1 )
    {
        u1 first = true;
        std::string tmp = " from multiple possible types: ";
        for( auto t : resTypes )
        {
            tmp += ( first ? "" : ", " );
            tmp += "'" + libcasm_ir::Type::token( t ) + "'";
            first = false;
        }

        m_log.error( { node.sourceLocation() },
            "unable to infer result type of " + description
                + ( resTypes.size() > 0 ? tmp : "" ),
            ( resTypes.size() > 0 ? Code::TypeInferenceFoundMultipleResultTypes
                                  : Code::TypeInferenceFoundNoResultType ) );
        return;
    }

    libcasm_ir::Type::Ptr inferedType = nullptr;
    if( annotation and arguments.size() > 0 )
    {
        std::vector< libcasm_ir::Type::Ptr > argTypes = {};

        for( auto argument : arguments )
        {
            if( not argument->type() )
            {
                return;
            }
            argTypes.emplace_back( argument->type()->ptr_result() );
        }

        try
        {
            inferedType = annotation->inference( argTypes, {} );
        }
        catch( const std::invalid_argument& e )
        {
            m_log.debug( { node.sourceLocation() },
                "INFERENCE: " + description + ": " + e.what() );
            return;
        }
        catch( const std::domain_error& e )
        {
            m_log.error( { node.sourceLocation() },
                "unable to infer result type of " + description + ": "
                    + e.what(),
                Code::TypeInferenceNotDefinedForExpression );
        }
    }

    switch( *resTypes.begin() )
    {
        case libcasm_ir::Type::VOID:
        {
            node.setType( VOID );
            break;
        }
        case libcasm_ir::Type::BOOLEAN:
        {
            node.setType( BOOLEAN );
            break;
        }
        case libcasm_ir::Type::INTEGER:
        {
            node.setType( INTEGER ); // TODO: PPA: check for ranged integers
            break;
        }
        case libcasm_ir::Type::BIT:
        {
            if( node.type() )
            {
                return;
            }

            node.setType( inferedType );
            break;
        }
        case libcasm_ir::Type::STRING:
        {
            node.setType( STRING );
            break;
        }
        case libcasm_ir::Type::FLOATING:
        {
            node.setType( FLOATING );
            break;
        }
        case libcasm_ir::Type::RATIONAL:
        {
            node.setType( RATIONAL );
            break;
        }
        case libcasm_ir::Type::RULE_REFERENCE:
        {
            break;
        }
        case libcasm_ir::Type::FUNCTION_REFERENCE:
        {
            assert( 0 ); // TODO: PPA: retrieve relation to
                         // construct FuncRef type
            // node.setType( ? );
            break;
        }
        default:
        {
            assert( 0 );
        }
    }
}

void TypeInferenceVisitor::inference( FunctionDefinition& node )
{
    if( node.defaultValue()->id() == Node::ID::UNDEF_ATOM
        and not node.defaultValue()->type() )
    {
        node.defaultValue()->setType( node.returnType()->type() );
    }

    if( node.type() )
    {
        return;
    }

    std::vector< libcasm_ir::Type::Ptr > argTypeList;
    for( auto argumentType : *node.argumentTypes() )
    {
        if( not argumentType->type() )
        {
            m_log.info( { argumentType->sourceLocation() },
                "TODO: '" + node.identifier()->name()
                    + "' has a non-typed argument(s)" );
            return;
        }

        argTypeList.emplace_back( argumentType->type() );
    }

    const auto type = libstdhl::make< libcasm_ir::RelationType >(
        node.returnType()->type(), argTypeList );

    node.setType( type );
}

void TypeInferenceVisitor::inference(
    DerivedDefinition& node, const std::vector< Expression::Ptr >& arguments )
{
    if( node.type() )
    {
        return;
    }

    std::size_t pos = 0;
    std::vector< libcasm_ir::Type::Ptr > argTypeList;
    for( auto argumentType : *node.arguments() )
    {
        if( not argumentType->type() )
        {
            if( arguments.size() > 0 and arguments[ pos ]->type() )
            {
                argTypeList.emplace_back( arguments[ pos ]->type() );
                argumentType->setType( arguments[ pos ]->type() );
            }
            else
            {
                m_log.debug( "'" + node.identifier()->name()
                             + "' has a non-typed argument(s)" );
                return;
            }
        }
        else
        {
            argTypeList.emplace_back( argumentType->type() );
        }
        pos++;
    }

    RecursiveVisitor::visit( node );

    const auto type = libstdhl::make< libcasm_ir::RelationType >(
        node.returnType()->type(), argTypeList );

    node.setType( type );
}

void TypeInferenceVisitor::inference(
    RuleDefinition& node, const std::vector< Expression::Ptr >& arguments )
{
    if( node.type() )
    {
        return;
    }

    std::size_t pos = 0;
    std::vector< libcasm_ir::Type::Ptr > argTypeList;
    for( auto argumentType : *node.arguments() )
    {
        if( not argumentType->type() )
        {
            if( arguments.size() > 0 and arguments[ pos ]->type() )
            {
                argTypeList.emplace_back( arguments[ pos ]->type() );
                argumentType->setType( arguments[ pos ]->type() );
            }
            else
            {
                m_log.debug( "'" + node.identifier()->name()
                             + "' has a non-typed argument(s)" );
                return;
            }
        }
        else
        {
            argTypeList.emplace_back( argumentType->type() );
        }
        pos++;
    }

    RecursiveVisitor::visit( node );

    const auto type = libstdhl::make< libcasm_ir::RelationType >(
        node.returnType()->type(), argTypeList );

    node.setType( type );
}

void TypeInferenceVisitor::inference( QuantifierExpression& node )
{
    node.setType( BOOLEAN );

    node.predicateVariable()->accept( *this );

    if( node.predicateVariable()->type() )
    {
        m_resultTypes[ node.universe().get() ].emplace_back(
            node.predicateVariable()->type()->id() );
    }

    push( *node.predicateVariable() );
    node.universe()->accept( *this );

    if( not node.predicateVariable()->type() and node.universe()->type() )
    {
        node.predicateVariable()->setType(
            node.universe()->type()->ptr_result() );
    }

    m_resultTypes[ node.proposition().get() ].emplace_back( node.type()->id() );

    node.proposition()->accept( *this );
    pop( *node.predicateVariable() );

    if( not node.predicateVariable()->type() )
    {
        m_log.error( { node.predicateVariable()->sourceLocation() },
            "no type found", Code::TypeInferenceInvalidExpression );
    }
    else if( not node.universe()->type() )
    {
        m_log.error( { node.universe()->sourceLocation() }, "no type found",
            Code::TypeInferenceInvalidExpression );
    }
    else
    {
        if( *node.predicateVariable()->type()
            != node.universe()->type()->result() )
        {
            m_log.error( { node.predicateVariable()->sourceLocation(),
                             node.universe()->sourceLocation() },
                node.description() + " predicate variable '"
                    + node.predicateVariable()->identifier()->name()
                    + "' of type '"
                    + node.predicateVariable()->type()->description()
                    + "' does not match the universe of type '"
                    + node.universe()->type()->result().description()
                    + "'",

                ( node.id() == Node::ID::EXISTENTIAL_QUANTIFIER_EXPRESSION )
                    ? Code::
                          TypeInferenceQuantifierExistentialPredicateTypeMismatch
                    : Code::
                          TypeInferenceQuantifierUniversalPredicateTypeMismatch );
        }
    }

    if( not node.proposition()->type() )
    {
        m_log.error( { node.proposition()->sourceLocation() }, "no type found",
            Code::TypeInferenceInvalidExpression );
    }
    else
    {
        const auto& propType = node.proposition()->type()->result();
        if( *node.type() != propType )
        {
            m_log.error(
                { node.sourceLocation(), node.proposition()->sourceLocation() },

                node.description() + " has invalid proposition type '"
                    + propType.description()
                    + "' shall be '"
                    + node.type()->description()
                    + "'",

                ( node.id() == Node::ID::EXISTENTIAL_QUANTIFIER_EXPRESSION )
                    ? Code::
                          TypeInferenceQuantifierExistentialPropositionTypeMismatch
                    : Code::
                          TypeInferenceQuantifierUniversalPropositionTypeMismatch );
        }
    }
}

void TypeInferenceVisitor::push( VariableDefinition& node )
{
    const auto& name = node.identifier()->name();

    auto result = m_id2var.emplace( name, &node );
    if( not result.second )
    {
        m_log.error( { node.sourceLocation() },
            "symbol '" + name + "' already defined" );
    }
}

void TypeInferenceVisitor::pop( VariableDefinition& node )
{
    const auto& name = node.identifier()->name();

    if( m_id2var.erase( name ) != 1 )
    {
        assert( !" internal error! " );
    }
}

VariableDefinition& TypeInferenceVisitor::find( const IdentifierPath& node )
{
    auto result = m_id2var.find( node.baseName() );
    if( result == m_id2var.end() )
    {
        throw std::domain_error(
            "unable to find symbol '" + node.path() + "'" );
    }

    return *result->second;
}

//
// TypeInferencePass
//

void TypeInferencePass::usage( libpass::PassUsage& pu )
{
    pu.require< SymbolResolverPass >();
}

u1 TypeInferencePass::run( libpass::PassResult& pr )
{
    Logger log( &id, stream() );

    const auto data = pr.result< SymbolResolverPass >();
    const auto specification = data->specification();
    const auto symboltable = data->symboltable();

    TypeCheckVisitor typeCheck( log, *symboltable );
    specification->accept( typeCheck );

    const auto typChkErr = log.errors();
    if( typChkErr )
    {
        log.debug( "found %lu error(s) during type checking", typChkErr );
        return false;
    }

    TypeInferenceVisitor typeInfer( log, *symboltable );
    specification->accept( typeInfer );

    const auto typInfErr = log.errors();
    if( typInfErr )
    {
        log.debug( "found %lu error(s) during type inference", typInfErr );
        return false;
    }

    pr.setResult< TypeInferencePass >(
        libstdhl::make< Data >( specification, symboltable ) );

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
