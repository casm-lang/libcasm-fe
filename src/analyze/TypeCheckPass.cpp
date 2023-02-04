//
//  Copyright (C) 2014-2023 CASM Organization <https://casm-lang.org>
//  All rights reserved.
//
//  Developed by: Philipp Paulweber et al.
//  <https://github.com/casm-lang/libcasm-fe/graphs/contributors>
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
//  Additional permission under GNU GPL version 3 section 7
//
//  libcasm-fe is distributed under the terms of the GNU General Public License
//  with the following clarification and special exception: Linking libcasm-fe
//  statically or dynamically with other modules is making a combined work
//  based on libcasm-fe. Thus, the terms and conditions of the GNU General
//  Public License cover the whole combination. As a special exception,
//  the copyright holders of libcasm-fe give you permission to link libcasm-fe
//  with independent modules to produce an executable, regardless of the
//  license terms of these independent modules, and to copy and distribute
//  the resulting executable under terms of your choice, provided that you
//  also meet, for each linked independent module, the terms and conditions
//  of the license of that module. An independent module is a module which
//  is not derived from or based on libcasm-fe. If you modify libcasm-fe, you
//  may extend this exception to your version of the library, but you are
//  not obliged to do so. If you do not wish to do so, delete this exception
//  statement from your version.
//

#include "TypeCheckPass.h"

#include "../various/GrammarToken.h"

#include <libcasm-fe/Logger>
#include <libcasm-fe/Namespace>
#include <libcasm-fe/Specification>
#include <libcasm-fe/TypeInfo>
#include <libcasm-fe/analyze/TemplatingPass>
#include <libcasm-fe/ast/Declaration>
#include <libcasm-fe/ast/Literal>
#include <libcasm-fe/ast/Visitor>
#include <libcasm-fe/import/SpecificationMergerPass>
#include <libcasm-fe/transform/SourceToCstPass>

#include <libpass/PassRegistry>
#include <libpass/PassResult>
#include <libpass/PassUsage>

using namespace libcasm_fe;
using namespace AST;

char TypeCheckPass::id = 0;

static libpass::PassRegistration< TypeCheckPass > PASS(
    "Type Check Pass", "type check of all types in the AST representation", "ast-type-chk", 0 );

//
//
// TypeCheckVisitor
//

namespace libcasm_fe
{
    namespace AST
    {
        class TypeCheckVisitor final : public RecursiveVisitor
        {
          public:
            TypeCheckVisitor( libcasm_fe::Logger& log, Namespace& symboltable );

            void visit( DerivedDefinition& node ) override;
            void visit( FunctionDefinition& node ) override;
            void visit( RuleDefinition& node ) override;
            void visit( EnumerationDefinition& node ) override;
            void visit( DomainDefinition& node ) override;
            void visit( BuiltinDefinition& node ) override;
            void visit( UsingDefinition& node ) override;
            void visit( StructureDefinition& node ) override;
            void visit( BehaviorDefinition& node ) override;
            void visit( ImplementDefinition& node ) override;
            void visit( VariableDefinition& node ) override;
            void visit( Declaration& node ) override;

            void visit( DirectCallExpression& node ) override;

            void visit( BasicType& node ) override;
            void visit( TupleType& node ) override;
            void visit( RecordType& node ) override;
            void visit( FixedSizedType& node ) override;
            void visit( RelationType& node ) override;
            void visit( TemplateType& node ) override;

          private:
            void resolveRelationType(
                TypedNode& node, VariableDefinitions& argumentTypes, Type& returnType );
            void resolveRelationType( TypedNode& node, Types& argumentTypes, Type& returnType );

            void pushSymbol( const VariableDefinition::Ptr& symbol );
            void pushSymbols( const VariableDefinitions::Ptr& symbols );
            void popSymbol( const VariableDefinition::Ptr& symbol );
            void popSymbols( const VariableDefinitions::Ptr& symbols );

            void pushVariableBindings( const VariableBindings::Ptr& variableBindings );
            void popVariableBindings( const VariableBindings::Ptr& variableBindings );

            libcasm_fe::Logger& m_log;
            Namespace& m_symboltable;

            std::unordered_map< std::string, VariableDefinition::Ptr > m_symbols;
        };
    }
}

TypeCheckVisitor::TypeCheckVisitor( libcasm_fe::Logger& log, Namespace& symboltable )
: m_log( log )
, m_symboltable( symboltable )
{
}

void TypeCheckVisitor::resolveRelationType(
    TypedNode& node, VariableDefinitions& argumentTypes, AST::Type& returnType )
{
    u1 valid = true;
    std::size_t position = 0;
    std::vector< libcasm_ir::Type::Ptr > argumentTypeList;
    argumentTypeList.reserve( argumentTypes.size() );
    for( const auto& argument : argumentTypes )
    {
        const auto& argumentType = *argument;
        position++;
        if( not argumentType.type() )
        {
            m_log.error(
                { argumentType.sourceLocation() },
                "unable to resolve argument type of " + argumentType.description() +
                    " at position " + std::to_string( position ),
                Code::Unspecified );
            valid = false;
            continue;
        }

        argumentTypeList.emplace_back( argumentType.type() );
    }

    if( not returnType.type() )
    {
        m_log.error(
            { returnType.sourceLocation() },
            "unable to resolve return type of " + node.description() + " '" +
                returnType.description() + "'",
            Code::Unspecified );
        valid = false;
    }

    if( not valid )
    {
        return;
    }

    const auto type =
        libstdhl::Memory::make< libcasm_ir::RelationType >( returnType.type(), argumentTypeList );
    node.setType( type );
}

void TypeCheckVisitor::resolveRelationType(
    TypedNode& node, Types& argumentTypes, AST::Type& returnType )
{
    u1 valid = true;
    std::size_t position = 0;
    std::vector< libcasm_ir::Type::Ptr > argumentTypeList;
    argumentTypeList.reserve( argumentTypes.size() );
    for( const auto& argument : argumentTypes )
    {
        const auto& argumentType = *argument;
        position++;
        if( not argumentType.type() )
        {
            m_log.error(
                { argumentType.sourceLocation() },
                "unable to resolve argument type of " + argumentType.description() +
                    " at position " + std::to_string( position ),
                Code::Unspecified );
            valid = false;
            continue;
        }

        argumentTypeList.emplace_back( argumentType.type() );
    }

    if( not returnType.type() )
    {
        m_log.error(
            { returnType.sourceLocation() },
            "unable to resolve return type of " + node.description() + " '" +
                returnType.description() + "'",
            Code::Unspecified );
        valid = false;
    }

    if( not valid )
    {
        return;
    }

    const auto type =
        libstdhl::Memory::make< libcasm_ir::RelationType >( returnType.type(), argumentTypeList );
    node.setType( type );
}

void TypeCheckVisitor::visit( DerivedDefinition& node )
{
    if( node.type() )
    {
        return;
    }

    const auto& argumentTypes = node.arguments();
    const auto& returnType = node.returnType();

    pushSymbols( node.arguments() );

    argumentTypes->accept( *this );
    returnType->accept( *this );

    popSymbols( node.arguments() );

    resolveRelationType( node, *argumentTypes, *returnType );

    node.expression()->accept( *this );
}

void TypeCheckVisitor::visit( FunctionDefinition& node )
{
    if( node.type() )
    {
        return;
    }

    const auto& argumentTypes = node.argumentTypes();
    const auto& returnType = node.returnType();

    argumentTypes->accept( *this );
    returnType->accept( *this );

    resolveRelationType( node, *argumentTypes, *returnType );

    node.defined()->accept( *this );
    node.initiallyRule()->accept( *this );
}

void TypeCheckVisitor::visit( RuleDefinition& node )
{
    if( node.type() )
    {
        return;
    }

    const auto& argumentTypes = node.arguments();
    const auto& returnType = node.returnType();

    pushSymbols( node.arguments() );

    argumentTypes->accept( *this );
    returnType->accept( *this );

    popSymbols( node.arguments() );

    resolveRelationType( node, *argumentTypes, *returnType );

    node.rule()->accept( *this );
}

void TypeCheckVisitor::visit( DomainDefinition& node )
{
    // if( node.type() ) // TODO: @ppaulweber: RE-ENABLE?
    // {
    //     return;
    // }

    const auto& domainType = node.domainType();

    pushSymbols( node.templateSymbols() );

    domainType->accept( *this );

    popSymbols( node.templateSymbols() );

    node.setType( domainType->type() );

    const auto& result = m_symboltable.findTypeDefinition( node.type()->id() );
    if( result )  // TODO: @ppaulweber: REMOVE?
    {
        // m_log.debug(
        //     { node.sourceLocation() },
        //     "already registered type/id/def '" + node.type()->description() + "'" );
        return;
    }

    if( node.type() )
    {
        try
        {
            m_symboltable.registerTypeDefinition( node );
        }
        catch( const std::domain_error& e )
        {
            m_log.debug( { node.sourceLocation() }, e.what() );
        }
    }
}

void TypeCheckVisitor::visit( EnumerationDefinition& node )
{
    if( node.type() and node.domainType()->type() )
    {
        return;
    }

    const auto& typeName = node.domainType()->signature();
    const auto kind = std::make_shared< libcasm_ir::Enumeration >( typeName );
    for( const auto& enumerator : *node.enumerators() )
    {
        try
        {
            kind->add( enumerator->identifier()->name() );
        }
        catch( const std::domain_error& e )
        {
            m_log.debug( { enumerator->sourceLocation() }, e.what() );
        }
    }

    const auto type = std::make_shared< libcasm_ir::EnumerationType >( kind );
    node.setType( type );
    node.domainType()->setType( type );

    for( const auto& enumerator : *node.enumerators() )
    {
        enumerator->setType( type );
    }

    m_symboltable.registerTypeDefinition( node );
}

void TypeCheckVisitor::visit( BuiltinDefinition& node )
{
    if( node.type() )
    {
        return;
    }

    const auto& argumentTypes = node.argumentTypes();
    const auto& returnType = node.returnType();

    pushSymbols( node.templateSymbols() );

    argumentTypes->accept( *this );
    returnType->accept( *this );

    popSymbols( node.templateSymbols() );

    resolveRelationType( node, *argumentTypes, *returnType );
}

void TypeCheckVisitor::visit( UsingDefinition& node )
{
    if( node.type() )
    {
        return;
    }

    RecursiveVisitor::visit( node );

    const auto& aliasType = node.aliasType();

    if( not aliasType->type() )
    {
        m_log.error(
            { aliasType->sourceLocation() },
            "unable to resolve using '" + node.identifier()->name() + "' with alias type '" +
                aliasType->description() + "'",
            Code::Unspecified );
        return;
    }

    node.setType( aliasType->type() );
}

void TypeCheckVisitor::visit( StructureDefinition& node )
{
    if( node.type() )
    {
        return;
    }

    const auto& typeName = node.domainType()->signature();
    const auto type = std::make_shared< libcasm_ir::ObjectType >( typeName );
    node.setType( type );

    pushSymbols( node.templateSymbols() );

    node.domainType()->accept( *this );
    node.functions()->accept( *this );

    popSymbols( node.templateSymbols() );

    m_symboltable.registerTypeDefinition( node );
}

void TypeCheckVisitor::visit( BehaviorDefinition& node )
{
    if( node.type() )
    {
        return;
    }

    const auto& typeName = node.domainType()->signature();
    const auto type = std::make_shared< libcasm_ir::ObjectType >( typeName );
    node.setType( type );

    pushSymbols( node.templateSymbols() );

    node.domainType()->accept( *this );
    node.definitions()->accept( *this );

    popSymbols( node.templateSymbols() );

    try
    {
        m_symboltable.registerTypeDefinition( node );
    }
    catch( const std::domain_error& e )
    {
        m_log.debug( { node.sourceLocation() }, e.what() );
    }
}

void TypeCheckVisitor::visit( ImplementDefinition& node )
{
    if( node.type() )
    {
        return;
    }

    const auto& symbol = node.domainType()->typeDefinition();
    assert( symbol and " inconsistent state @ SymbolResolverPass " );
    symbol->accept( *this );
    assert( symbol->type() and " inconsistent state " );

    if( symbol->id() != Node::ID::ENUMERATION_DEFINITION and
        symbol->id() != Node::ID::STRUCTURE_DEFINITION and
        symbol->id() != Node::ID::DOMAIN_DEFINITION )
    {
        m_log.error(
            { node.sourceLocation() },
            "implement not allowed on '" + symbol->description() + "' ",
            Code::Unspecified );
        return;
    }

    pushSymbols( node.templateSymbols() );

    node.behaviorType()->accept( *this );
    node.domainType()->accept( *this );
    node.definitions()->accept( *this );

    popSymbols( node.templateSymbols() );

    node.setType( node.domainType()->type() );
}

void TypeCheckVisitor::visit( VariableDefinition& node )
{
    if( node.type() )
    {
        return;
    }

    RecursiveVisitor::visit( node );

    if( node.variableType()->type() )
    {
        node.setType( node.variableType()->type() );
    }
    else if( node.objectDefinition() )
    {
        const auto& symbol = node.objectDefinition()->domainType()->typeDefinition();
        assert( symbol and " inconsistent state @ SymbolResolverPass " );
        symbol->accept( *this );
        assert( symbol->type() and " inconsistent state " );
        node.setType( symbol->type() );
    }
    else
    {
        node.setType( TypeInfo::instance().getType( TypeInfo::TYPE_NAME_OBJECT ) );
    }
}

void TypeCheckVisitor::visit( Declaration& node )
{
    if( node.type() )
    {
        return;
    }

    const auto& argumentTypes = node.argumentTypes();
    const auto& returnType = node.returnType();

    argumentTypes->accept( *this );
    returnType->accept( *this );

    resolveRelationType( node, *argumentTypes, *returnType );
}

void TypeCheckVisitor::visit( DirectCallExpression& node )
{
    RecursiveVisitor::visit( node );

    if( node.type() )
    {
        return;
    }

    const auto& symbolPath = node.identifier();
    const auto& symbolName = symbolPath->path();

    switch( node.targetType() )
    {
        case DirectCallExpression::TargetType::RULE:      // [[fallthrough]]
        case DirectCallExpression::TargetType::DERIVED:   // [[fallthrough]]
        case DirectCallExpression::TargetType::FUNCTION:  // [[fallthrough]]
        case DirectCallExpression::TargetType::BUILTIN:
        {
            const auto& symbol = node.targetDefinition();
            assert( symbol and " inconsistent state @ SymbolResolverPass " );
            symbol->accept( *this );
            assert( symbol->type() and " inconsistent state " );
            node.setType( symbol->type()->ptr_result() );
            return;
        }
        case DirectCallExpression::TargetType::CONSTANT:  // [[fallthrough]]
        case DirectCallExpression::TargetType::VARIABLE:
        {
            // resolved at type inference
            return;
        }
        case DirectCallExpression::TargetType::DOMAINTYPE:
        {
            const auto& symbol = node.targetDefinition();
            assert( symbol and " inconsistent state @ SymbolResolverPass " );
            symbol->accept( *this );
            assert( symbol->type() and " inconsistent state " );
            node.setType( symbol->type() );
            return;
        }
        case DirectCallExpression::TargetType::UNKNOWN:
        {
            break;
        }
    }

    m_log.error(
        { node.sourceLocation() },
        "unknown " + node.description() + " symbol '" + symbolName + "' found" );
}

void TypeCheckVisitor::visit( BasicType& node )
{
    if( node.type() )
    {
        return;
    }

    RecursiveVisitor::visit( node );

    const auto& typeName = node.signature();
    const auto& symbolName = node.signaturePath();

    const auto symbolResult = m_symbols.find( typeName );
    if( symbolResult != m_symbols.cend() )
    {
        const auto& symbol = symbolResult->second;
        symbol->accept( *this );
        const auto& symbolType = symbol->type();
        assert( symbolType and " inconsistent state " );
        node.setType( symbolType );
        return;
    }

    auto symbol = node.typeDefinition();
    assert( symbol and " inconsistent state @ SymbolResolverPass " );
    switch( symbol->id() )
    {
        case Node::ID::ENUMERATION_DEFINITION:  // [fallthrough]
        case Node::ID::STRUCTURE_DEFINITION:    // [fallthrough]
        case Node::ID::BEHAVIOR_DEFINITION:     // [fallthrough]
        case Node::ID::USING_DEFINITION:
        {
            symbol->accept( *this );
            const auto& type = symbol->type();
            if( type )
            {
                node.setType( type );
                return;
            }
            break;
        }
        case Node::ID::DOMAIN_DEFINITION:
        {
            const auto& domainDefinition = static_cast< const DomainDefinition& >( *symbol );
            const auto domainDefinitionType =
                static_cast< const AST::Type* >( domainDefinition.domainType().get() );

            if( node.id() != domainDefinitionType->id() )
            {
                const auto msg = node.description() + "  '" + typeName + "' is not a " +
                                 domainDefinitionType->description();
                m_log.error(
                    { node.sourceLocation() }, msg, Code::TypeAnnotationInvalidBasicTypeName );
                m_log.info( { domainDefinitionType->sourceLocation() }, msg );
                return;
            }

            const auto& type = symbol->type();
            if( type )
            {
                node.setType( type );
                return;
            }

            const auto domainName = node.name()->path();
            if( TypeInfo::instance().hasType( domainName ) )
            {
                const auto& type = TypeInfo::instance().getType( domainName );
                node.setType( type );
                return;
            }
            else
            {
                const auto type = std::make_shared< libcasm_ir::ObjectType >( typeName );
                node.setType( type );
                return;
            }
            break;
        }
        default:
        {
            m_log.error(
                { node.sourceLocation() },
                "cannot use " + symbol->description() + " '" + typeName + "' as " +
                    node.description(),
                Code::TypeAnnotationInvalidBasicTypeName );
            return;
        }
    }

    m_log.error(
        { node.sourceLocation() },
        "unknown " + node.description() + " '" + typeName + "' found",
        Code::TypeAnnotationInvalidBasicTypeName );
}

void TypeCheckVisitor::visit( TupleType& node )
{
    if( node.type() )
    {
        return;
    }

    RecursiveVisitor::visit( node );

    u1 valid = true;
    std::size_t position = 0;
    libcasm_ir::Types subTypeList;
    for( auto argument : *node.subTypes() )
    {
        position++;
        if( not argument->type() )
        {
            m_log.error(
                { argument->sourceLocation() },
                "unable to resolve tuple argument type '" + argument->description() +
                    "' at position " + std::to_string( position ),
                Code::Unspecified );
            valid = false;
            continue;
        }

        subTypeList.add( argument->type() );
    }

    if( not valid )
    {
        return;
    }

    assert( subTypeList.size() >= 2 and " inconsistent state @ GrammarParser " );

    const auto& typeName = node.signature();
    const auto type = std::make_shared< libcasm_ir::TupleType >( subTypeList );
    node.setType( type );
}

void TypeCheckVisitor::visit( RecordType& node )
{
    if( node.type() )
    {
        return;
    }

    RecursiveVisitor::visit( node );

    u1 valid = true;
    std::size_t position = 0;
    libcasm_ir::Types argumentTypeList;
    std::vector< std::string > argumentNameList;
    for( auto argument : *node.namedSubTypes() )
    {
        position++;
        if( not argument->type() )
        {
            m_log.error(
                { argument->sourceLocation() },
                "unable to resolve " + node.description() + " argument type '" +
                    argument->description() + "' at position " + std::to_string( position ),
                Code::Unspecified );
            valid = false;
            continue;
        }

        argumentTypeList.add( argument->variableType()->type() );
        argumentNameList.emplace_back( argument->identifier()->name() );
    }

    if( not valid )
    {
        return;
    }

    assert( argumentTypeList.size() >= 1 and " inconsistent state @ GrammarParser " );

    const auto& typeName = node.signature();
    const auto type =
        std::make_shared< libcasm_ir::RecordType >( argumentTypeList, argumentNameList );
    node.setType( type );
}

void TypeCheckVisitor::visit( FixedSizedType& node )
{
    if( node.type() )
    {
        return;
    }

    RecursiveVisitor::visit( node );

    const auto& typeName = node.signature();

    const auto& expression = node.size();
    if( not expression->type() )
    {
        if( expression->id() == Node::ID::DIRECT_CALL_EXPRESSION )
        {
            const auto& type = libstdhl::Memory::get< libcasm_ir::ObjectType >( typeName );
            node.setType( type );
            return;
        }
        else if(
            expression->id() != Node::ID::VALUE_LITERAL and
            expression->id() != Node::ID::RANGE_LITERAL )
        {
            m_log.error(
                { expression->sourceLocation() },
                "unable to resolve " + node.description() + " expression type of " +
                    expression->description(),
                Code::Unspecified );
            return;
        }
    }

    const auto& symbol = node.typeDefinition();
    assert( symbol and " inconsistent state @ SymbolResolverPass " );

    switch( symbol->id() )
    {
        case Node::ID::DOMAIN_DEFINITION:
        {
            const auto& domainDefinition = static_cast< const DomainDefinition& >( *symbol );
            const auto domainDefinitionType =
                static_cast< const AST::Type* >( domainDefinition.domainType().get() );
            if( node.id() != domainDefinitionType->id() )
            {
                m_log.error(
                    { node.sourceLocation() },
                    node.description() + "  '" + typeName + "' is not a " +
                        domainDefinitionType->description(),
                    Code::Unspecified );
                return;
            }

            const auto& type = symbol->type();
            if( type )
            {
                node.setType( type );
                return;
            }

            const auto typeKind = node.name()->path();
            if( typeKind == TypeInfo::TYPE_NAME_BINARY )
            {
                if( expression->id() == Node::ID::VALUE_LITERAL and
                    expression->type()->isInteger() )
                {
                    const auto& literal = static_cast< const ValueLiteral& >( *expression );
                    const auto value =
                        std::static_pointer_cast< libcasm_ir::IntegerConstant >( literal.value() );

                    libcasm_ir::Type::Ptr type = nullptr;
                    try
                    {
                        type = libstdhl::Memory::get< libcasm_ir::BinaryType >( value );
                    }
                    catch( const std::domain_error& e )
                    {
                        m_log.error(
                            { expression->sourceLocation() },
                            e.what(),
                            Code::TypeBinarySizeIsInvalid );
                        return;
                    }

                    node.setType( type );
                    return;
                }
                else if( expression->id() == Node::ID::DIRECT_CALL_EXPRESSION )
                {
                    const auto& type = libstdhl::Memory::get< libcasm_ir::ObjectType >( typeName );
                    node.setType( type );
                    return;
                }
                else
                {
                    m_log.error(
                        { node.sourceLocation() },
                        "invalid expression for " + node.description() + " '" + typeName +
                            "' found",
                        Code ::TypeAnnotationInvalidFixedSizeExpression );
                    return;
                }
            }
            else if( typeKind == TypeInfo::TYPE_NAME_INTEGER )
            {
                if( expression->id() == Node::ID::RANGE_LITERAL )
                {
                    const auto& literal = static_cast< const RangeLiteral& >( *expression );

                    u1 valid = true;
                    u1 lhsNegative = false;
                    u1 rhsNegative = false;

                    auto lhs = literal.left();
                    if( lhs->id() == Node::ID::UNARY_EXPRESSION )
                    {
                        const auto& lhsUnaryExpression =
                            static_cast< const UnaryExpression& >( *lhs );
                        lhs = lhsUnaryExpression.expression();
                        if( lhsUnaryExpression.operationToken() == Grammar::Token::MINUS )
                        {
                            lhsNegative = true;
                        }
                    }

                    if( not( lhs->id() == Node::ID::VALUE_LITERAL and lhs->type()->isInteger() ) )
                    {
                        valid = false;
                        m_log.error(
                            { lhs->sourceLocation() },
                            "unsupported left-hand side expression '" + lhs->description() +
                                "', Integer literal constant expected",
                            Code::TypeAnnotationInvalidFixedSizeExpression );
                    }

                    auto rhs = literal.right();
                    if( rhs->id() == Node::ID::UNARY_EXPRESSION )
                    {
                        const auto& rhsUnaryExpression =
                            static_cast< const UnaryExpression& >( *rhs );
                        rhs = rhsUnaryExpression.expression();
                        if( rhsUnaryExpression.operationToken() == Grammar::Token::MINUS )
                        {
                            rhsNegative = true;
                        }
                    }

                    if( not( rhs->id() == Node::ID::VALUE_LITERAL and rhs->type()->isInteger() ) )
                    {
                        valid = false;
                        m_log.error(
                            { rhs->sourceLocation() },
                            "unsupported right-hand side expression '" + rhs->description() +
                                "', Integer literal constant expected",
                            Code::TypeAnnotationInvalidFixedSizeExpression );
                    }

                    if( not valid )
                    {
                        return;
                    }

                    auto lhsValue = std::static_pointer_cast< libcasm_ir::IntegerConstant >(
                        static_cast< const ValueLiteral& >( *lhs ).value() );
                    if( lhsNegative )
                    {
                        lhsValue =
                            std::make_shared< libcasm_ir::IntegerConstant >( -lhsValue->value() );
                    }

                    auto rhsValue = std::static_pointer_cast< libcasm_ir::IntegerConstant >(
                        static_cast< const ValueLiteral& >( *rhs ).value() );
                    if( rhsNegative )
                    {
                        rhsValue =
                            std::make_shared< libcasm_ir::IntegerConstant >( -rhsValue->value() );
                    }

                    const auto& range =
                        libstdhl::Memory::make< libcasm_ir::Range >( lhsValue, rhsValue );
                    const auto& rangeType = libstdhl::Memory::get< libcasm_ir::RangeType >( range );
                    assert( not expression->type() and " inconsistent state " );
                    expression->setType( rangeType );

                    try
                    {
                        const auto& type =
                            libstdhl::Memory::get< libcasm_ir::IntegerType >( rangeType );
                        node.setType( type );
                    }
                    catch( const std::domain_error& e )
                    {
                        m_log.error( { expression->sourceLocation() }, e.what() );
                    }
                    return;
                }
                else
                {
                    m_log.error(
                        { node.sourceLocation() },
                        "invalid expression for " + node.description() + " '" + typeName +
                            "' found",
                        Code ::TypeAnnotationInvalidFixedSizeExpression );
                    return;
                }
            }
            break;
        }
        default:
        {
            m_log.error(
                { node.sourceLocation() },
                "cannot use " + symbol->description() + " '" + typeName + "' as " +
                    node.description(),
                Code::TypeAnnotationInvalidFixedSizeTypeName );
            return;
        }
    }

    const auto& type = libstdhl::Memory::make< libcasm_ir::ObjectType >( node.signature() );
    node.setType( type );
}

void TypeCheckVisitor::visit( TemplateType& node )
{
    if( node.type() )
    {
        return;
    }

    if( node.varadic() )
    {
        return;
    }

    const auto& typeName = node.signature();
    const auto& symbol = node.typeDefinition();
    assert( symbol and " inconsistent state @ SymbolResolverPass " );

    if( not symbol->isTemplate() )
    {
        RecursiveVisitor::visit( node );
    }

    switch( symbol->id() )
    {
        case Node::ID::BEHAVIOR_DEFINITION:  // [fallthrough]
        case Node::ID::IMPLEMENT_DEFINITION:
        {
            const auto& behaviorDefinition = static_cast< const BehaviorDefinition& >( *symbol );
            const auto domainDefinitionType =
                static_cast< const AST::Type* >( behaviorDefinition.domainType().get() );
            if( node.id() != domainDefinitionType->id() )
            {
                m_log.error(
                    { node.sourceLocation() },
                    node.description() + "  '" + typeName + "' is not a " +
                        domainDefinitionType->description(),
                    Code::TypeAnnotationInvalidTemplateTypeName );
                return;
            }

            symbol->accept( *this );
            const auto& type = symbol->type();
            if( type )
            {
                node.setType( type );
                return;
            }

            break;
        }
        case Node::ID::DOMAIN_DEFINITION:
        {
            const auto& domainDefinition = static_cast< const DomainDefinition& >( *symbol );
            const auto domainDefinitionType =
                static_cast< const AST::Type* >( domainDefinition.domainType().get() );
            if( node.id() != domainDefinitionType->id() )
            {
                m_log.error(
                    { node.sourceLocation() },
                    node.description() + "  '" + typeName + "' is not a " +
                        domainDefinitionType->description(),
                    Code::TypeAnnotationInvalidTemplateTypeName );
                return;
            }

            const auto& type = symbol->type();
            if( type )
            {
                node.setType( type );
                return;
            }

            const auto typeKind = node.name()->path();

            assert( node.subTypes()->size() >= 1 and " inconsistent state @ SymbolResolverPass " );
            if( node.subTypes()->size() == 1 )
            {
                const auto& subNode = node.subTypes()->front();
                subNode->accept( *this );
                const auto& subType = subNode->type();
                assert( subType and " inconsistent state " );

                if( not subType->isObject() )
                {
                    if( typeKind == TypeInfo::TYPE_NAME_RANGE )
                    {
                        const auto& type =
                            libstdhl::Memory::make< libcasm_ir::RangeType >( subType );
                        node.setType( type );
                        return;
                    }
                    // else if( typeKind == TypeInfo::TYPE_NAME_SET )
                    // {
                    //     const auto& type =
                    //         libstdhl::Memory::make< libcasm_ir::SetType >( subType );
                    //     node.setType( type );
                    //     return;
                    // }
                    else if( typeKind == TypeInfo::TYPE_NAME_FILE )
                    {
                        m_log.debug(
                            { node.sourceLocation() },
                            node.description() + " '" + typeName + "' is experimental" );
                        const auto& type =
                            libstdhl::Memory::make< libcasm_ir::FileType >( subType );
                        node.setType( type );
                        return;
                    }
                    else if( typeKind == TypeInfo::TYPE_NAME_PORT )
                    {
                        m_log.debug(
                            { node.sourceLocation() },
                            node.description() + " '" + typeName + "' is experimental" );
                        const auto& type =
                            libstdhl::Memory::make< libcasm_ir::PortType >( subType );
                        node.setType( type );
                        return;
                    }
                }
            }
            break;
        }
        default:
        {
            m_log.error(
                { node.sourceLocation() },
                "cannot use " + symbol->description() + " '" + typeName + "' as " +
                    node.description(),
                Code::TypeAnnotationInvalidTemplateTypeName );
            return;
        }
    }

    const auto& type = libstdhl::Memory::make< libcasm_ir::ObjectType >( node.signature() );
    node.setType( type );
}

void TypeCheckVisitor::visit( RelationType& node )
{
    if( node.type() )
    {
        return;
    }

    RecursiveVisitor::visit( node );

    if( node.mapping() )
    {
        return;
    }

    const auto& typeName = node.signature();

    resolveRelationType( node, *node.argumentTypes(), *node.returnType() );
    if( not node.type() )
    {
        return;
    }

    auto nodeType = node.type();
    node.setType( nullptr );
    const auto& relationType = std::static_pointer_cast< libcasm_ir::RelationType >( nodeType );

    const auto& symbol = node.typeDefinition();
    assert( symbol and " inconsistent state @ SymbolResolverPass " );
    switch( symbol->id() )
    {
        case Node::ID::DOMAIN_DEFINITION:
        {
            if( not symbol->type() )
            {
                libcasm_ir::Type::Ptr type = nullptr;
                const auto typeKind = node.name()->path();

                if( typeKind == TypeInfo::TYPE_NAME_RULEREF )
                {
                    type = libstdhl::Memory::make< libcasm_ir::RuleReferenceType >( relationType );
                }
                else if( typeKind == TypeInfo::TYPE_NAME_FUNCREF )
                {
                    type =
                        libstdhl::Memory::make< libcasm_ir::FunctionReferenceType >( relationType );
                }

                symbol->setType( type );
            }

            const auto& type = symbol->type();
            if( type )
            {
                node.setType( type );
                return;
            }

            break;
        }
        case Node::ID::BUILTIN_DEFINITION:
        {
            // symbol->accept( *this );
            const auto& type = symbol->type();
            if( symbol->type() )
            {
                node.setType( type );
                return;
            }
            break;
        }
        default:
        {
            m_log.error(
                { node.sourceLocation() },
                "cannot use " + symbol->description() + " '" + typeName + "' as " +
                    node.description(),
                Code::TypeAnnotationInvalidRelationTypeName );
            return;
        }
    }

    m_log.error(
        { node.sourceLocation() },
        "unknown " + node.description() + " '" + typeName + "' found",
        Code ::TypeAnnotationInvalidRelationTypeName );
}

void TypeCheckVisitor::pushSymbol( const VariableDefinition::Ptr& symbol )
{
    const auto& name = symbol->identifier()->name();

    const auto result = m_symbols.emplace( name, symbol );
    if( not result.second )
    {
        m_log.error(
            { symbol->sourceLocation() },
            "redefinition of symbol '" + name + "'",
            Code::SymbolAlreadyDefined );

        const auto& existingTemplateSymbol = result.first->second;
        m_log.info(
            { existingTemplateSymbol->sourceLocation() },
            "previous definition of '" + name + "' is here" );
    }
}

void TypeCheckVisitor::pushSymbols( const VariableDefinitions::Ptr& symbols )
{
    for( const auto& symbol : *symbols )
    {
        pushSymbol( symbol );
    }
}

void TypeCheckVisitor::popSymbol( const VariableDefinition::Ptr& symbol )
{
    const auto& name = symbol->identifier()->name();
    m_symbols.erase( name );
}

void TypeCheckVisitor::popSymbols( const VariableDefinitions::Ptr& symbols )
{
    for( const auto& symbol : *symbols )
    {
        popSymbol( symbol );
    }
}

void TypeCheckVisitor::pushVariableBindings( const VariableBindings::Ptr& variableBindings )
{
    for( const auto& variableBinding : *variableBindings )
    {
        pushSymbol( variableBinding->variable() );
    }
}

void TypeCheckVisitor::popVariableBindings( const VariableBindings::Ptr& variableBindings )
{
    for( const auto& variableBinding : *variableBindings )
    {
        popSymbol( variableBinding->variable() );
    }
}

//
//
// TypeCheckPass
//

void TypeCheckPass::usage( libpass::PassUsage& pu )
{
    pu.require< SpecificationMergerPass >();
}

u1 TypeCheckPass::run( libpass::PassResult& pr )
{
    libcasm_fe::Logger log( &id, stream() );

    const auto data = pr.output< SpecificationMergerPass >();
    const auto specification = data->specification();

    TypeCheckVisitor visitor( log, *specification->symboltable() );
    specification->ast()->accept( visitor );

    const auto errors = log.errors();
    if( errors > 0 )
    {
        log.debug( "symbol table =\n" + specification->symboltable()->dump() );
        log.debug( "found %lu error(s) during type checking", errors );
        return false;
    }

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
