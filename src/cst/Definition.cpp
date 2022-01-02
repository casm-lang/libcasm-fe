//
//  Copyright (C) 2014-2022 CASM Organization <https://casm-lang.org>
//  All rights reserved.
//
//  Developed by: Philipp Paulweber et al.
//                <https://github.com/casm-lang/libcasm-fe/graphs/contributors>
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

#include "Definition.h"

#include "../various/GrammarToken.h"

#include <libcasm-fe/cst/Expression>
#include <libcasm-fe/cst/Literal>

using namespace libcasm_fe;
using namespace CST;

//
//
// Definition
//

Definition::Definition( Node::ID type, const Identifier::Ptr& identifier )
: TypedPropertyNode( type )
, m_identifier( identifier )
, m_attributes( std::make_shared< Attributes >() )
, m_delimiterToken( Token::unresolved() )
, m_maxNumberOfLocals( 0 )
, m_abstract( false )
, m_exported( false )
, m_operation( Grammar::Token::UNRESOLVED )
, m_templateSymbols( std::make_shared< VariableDefinitions >() )
{
}

const Identifier::Ptr& Definition::identifier( void ) const
{
    return m_identifier;
}

void Definition::setAttributes( const Attributes::Ptr& attributes )
{
    m_attributes = attributes;
}

const Attributes::Ptr& Definition::attributes( void ) const
{
    return m_attributes;
}

void Definition::setDelimiterToken( const Token::Ptr& delimiterToken )
{
    assert( m_delimiterToken->token() == Grammar::Token::UNRESOLVED );
    m_delimiterToken = delimiterToken;
}

const Token::Ptr& Definition::delimiterToken( void ) const
{
    return m_delimiterToken;
}

void Definition::setMaximumNumberOfLocals( std::size_t maxNumberOfLocals )
{
    m_maxNumberOfLocals = maxNumberOfLocals;
}

std::size_t Definition::maximumNumberOfLocals( void ) const
{
    return m_maxNumberOfLocals;
}

void Definition::setAbstract( const u1 abstract )
{
    m_abstract = abstract;
}

u1 Definition::abstract( void ) const
{
    return m_abstract;
}

void Definition::setExported( const u1 exported )
{
    m_exported = exported;
}

u1 Definition::exported( void ) const
{
    return m_exported;
}

void Definition::setOperation( const Grammar::Token operation )
{
    m_operation = operation;
}

Grammar::Token Definition::operation( void ) const
{
    return m_operation;
}

const VariableDefinitions::Ptr& Definition::templateSymbols( void ) const
{
    return m_templateSymbols;
}

void Definition::clone( Definition& duplicate ) const
{
    TypedPropertyNode::clone( duplicate );
    duplicate.setAttributes( attributes()->duplicate< Attributes >() );
    duplicate.setDelimiterToken( delimiterToken() );
    duplicate.setMaximumNumberOfLocals( maximumNumberOfLocals() );
    duplicate.setAbstract( abstract() );
    duplicate.setExported( exported() );
    duplicate.setOperation( operation() );
}

//
//
// HeaderDefinition
//

HeaderDefinition::HeaderDefinition( const Token::Ptr& headerToken )
: Definition(
      Node::ID::HEADER_DEFINITION,
      CST::make< Identifier >( headerToken->sourceLocation(), headerToken->tokenString() ) )
, m_headerToken( headerToken )
{
}

const Token::Ptr& HeaderDefinition::headerToken( void ) const
{
    return m_headerToken;
}

std::string HeaderDefinition::typeDescription( void ) const
{
    return "...";
}

void HeaderDefinition::accept( Visitor& visitor )
{
    visitor.visit( *this );
}

Node::Ptr HeaderDefinition::clone( void ) const
{
    auto duplicate = std::make_shared< HeaderDefinition >( headerToken() );

    Definition::clone( *duplicate );
    return duplicate;
}

//
//
// VariableDefinition
//

VariableDefinition::VariableDefinition(
    const Identifier::Ptr& identifier, const Token::Ptr& colonToken, const Type::Ptr& variableType )
: Definition( Node::ID::VARIABLE_DEFINITION, identifier )
, m_variableType( variableType )
, m_colonToken( colonToken )
, m_localIndex( 0 )
, m_objectDefinition()
{
    setProperty( libcasm_ir::Property::SIDE_EFFECT_FREE );
    setProperty( libcasm_ir::Property::PURE );
}

const Type::Ptr& VariableDefinition::variableType( void ) const
{
    return m_variableType;
}

void VariableDefinition::setVariableType( const Type::Ptr& variableType )
{
    m_variableType = variableType;
}

const Token::Ptr& VariableDefinition::colonToken( void ) const
{
    return m_colonToken;
}

void VariableDefinition::setLocalIndex( std::size_t localIndex )
{
    m_localIndex = localIndex;
}

std::size_t VariableDefinition::localIndex( void ) const
{
    return m_localIndex;
}

void VariableDefinition::setObjectDefinition( const TypeDefinition::Ptr& objectDefinition )
{
    m_objectDefinition = objectDefinition;
}

const TypeDefinition::Ptr& VariableDefinition::objectDefinition( void ) const
{
    return m_objectDefinition;
}

std::string VariableDefinition::typeDescription( void ) const
{
    return identifier()->name() + " : " + variableType()->signature();
}

void VariableDefinition::accept( Visitor& visitor )
{
    visitor.visit( *this );
}

Node::Ptr VariableDefinition::clone( void ) const
{
    auto duplicate = std::make_shared< VariableDefinition >(
        identifier()->duplicate< Identifier >(),
        colonToken(),
        variableType()->duplicate< Type >() );

    Definition::clone( *duplicate );
    duplicate->setLocalIndex( localIndex() );
    duplicate->setObjectDefinition( objectDefinition() );
    return duplicate;
}

//
//
// TypeDefinition
//

TypeDefinition::TypeDefinition( const Node::ID id, const Type::Ptr& domainType )
: Definition(
      id,
      CST::make< Identifier >( domainType->name()->sourceLocation(), domainType->name()->path() ) )
, m_domainType( domainType )
{
}

const Type::Ptr& TypeDefinition::domainType( void ) const
{
    return m_domainType;
}

void TypeDefinition::clone( TypeDefinition& duplicate ) const
{
    Definition::clone( duplicate );
}

//
//
// FunctionDefinition
//

FunctionDefinition::FunctionDefinition(
    const Token::Ptr& functionToken,
    const Identifier::Ptr& identifier,
    const Token::Ptr& colonToken,
    const Types::Ptr& argumentTypes,
    const Token::Ptr& mapsToken,
    const Type::Ptr& returnType,
    const Defined::Ptr& defined,
    const Initially::Ptr& initially )
: Definition( Node::ID::FUNCTION_DEFINITION, identifier )
, m_argumentTypes( argumentTypes )
, m_returnType( returnType )
, m_defined( defined )
, m_functionToken( functionToken )
, m_mapsToken( mapsToken )
, m_colonToken( colonToken )
, m_classification( Classification::UNKNOWN )
, m_symbolic( false )
, m_initially( initially )
, m_isProgram( identifier->name() == "program" )
{
    setProperty( libcasm_ir::Property::SIDE_EFFECT_FREE );
}

bool FunctionDefinition::isProgram( void ) const
{
    return m_isProgram;
}

bool FunctionDefinition::isLocal( void ) const
{
    return m_classification == Classification::LOCAL;
}

const Types::Ptr& FunctionDefinition::argumentTypes( void ) const
{
    return m_argumentTypes;
}

const Type::Ptr& FunctionDefinition::returnType( void ) const
{
    return m_returnType;
}

const Token::Ptr& FunctionDefinition::functionToken( void ) const
{
    return m_functionToken;
}

const Token::Ptr& FunctionDefinition::colonToken( void ) const
{
    return m_colonToken;
}

const Token::Ptr& FunctionDefinition::mapsToken( void ) const
{
    return m_mapsToken;
}

const Defined::Ptr& FunctionDefinition::defined( void ) const
{
    return m_defined;
}

void FunctionDefinition::setClassification( FunctionDefinition::Classification classification )
{
    m_classification = classification;
}

FunctionDefinition::Classification FunctionDefinition::classification( void ) const
{
    return m_classification;
}

std::string FunctionDefinition::classificationName( void ) const
{
    return toString( classification() );
}

std::string FunctionDefinition::toString( const Classification classification )
{
    switch( classification )
    {
        case FunctionDefinition::Classification::UNKNOWN:
        {
            return "unknown";
        }
        case FunctionDefinition::Classification::IN:
        {
            return "in";
        }
        case FunctionDefinition::Classification::CONTROLLED:
        {
            return "controlled";
        }
        case FunctionDefinition::Classification::SHARED:
        {
            return "shared";
        }
        case FunctionDefinition::Classification::OUT:
        {
            return "out";
        }
        case FunctionDefinition::Classification::STATIC:
        {
            return "static";
        }
        case FunctionDefinition::Classification::LOCAL:
        {
            return "local";
        }
    }

    assert( !" internal error! " );
    return std::string();
}

void FunctionDefinition::setSymbolic( u1 symbolic )
{
    m_symbolic = symbolic;
}

u1 FunctionDefinition::symbolic( void ) const
{
    return m_symbolic;
}

const Initially::Ptr& FunctionDefinition::initially( void ) const
{
    return m_initially;
}

std::string FunctionDefinition::typeDescription( void ) const
{
    std::stringstream stream;
    stream << ":";

    const auto& innerTypes = argumentTypes();
    for( const auto& innerType : *innerTypes )
    {
        stream << " " << innerType->signature() << "* ";
    }

    if( innerTypes->size() > 0 )
    {
        stream.seekp( -2, stream.cur );
    }

    stream << " -> " << returnType()->signature() << " ";
    return stream.str();
}

void FunctionDefinition::accept( Visitor& visitor )
{
    visitor.visit( *this );
}

Node::Ptr FunctionDefinition::clone( void ) const
{
    auto duplicate = std::make_shared< FunctionDefinition >(
        functionToken(),
        identifier()->duplicate< Identifier >(),
        colonToken(),
        argumentTypes()->duplicate< Types >(),
        mapsToken(),
        returnType()->duplicate< Type >(),
        defined()->duplicate< Defined >(),
        initially()->duplicate< Initially >() );

    Definition::clone( *duplicate );
    duplicate->setClassification( classification() );
    duplicate->setSymbolic( symbolic() );
    return duplicate;
}

//
//
// DerivedDefinition
//

DerivedDefinition::DerivedDefinition(
    const Token::Ptr& derivedToken,
    const Identifier::Ptr& identifier,
    const VariableDefinitions::Ptr& arguments,
    const Token::Ptr& mapsToken,
    const Type::Ptr& returnType,
    const Token::Ptr& assignmentToken,
    const Expression::Ptr& expression )
: Definition( Node::ID::DERIVED_DEFINITION, identifier )
, m_arguments( arguments )
, m_returnType( returnType )
, m_expression( expression )
, m_derivedToken( derivedToken )
, m_mapsToken( mapsToken )
, m_assignmentToken( assignmentToken )
, m_leftBracketToken( Token::unresolved() )
, m_rightBracketToken( Token::unresolved() )
{
    setProperty( libcasm_ir::Property::SIDE_EFFECT_FREE );
}

const VariableDefinitions::Ptr& DerivedDefinition::arguments( void ) const
{
    return m_arguments;
}

const Type::Ptr& DerivedDefinition::returnType( void ) const
{
    return m_returnType;
}

void DerivedDefinition::setReturnType( const Type::Ptr& returnType )
{
    m_returnType = returnType;
}

const Expression::Ptr& DerivedDefinition::expression( void ) const
{
    return m_expression;
}

const Token::Ptr& DerivedDefinition::derivedToken( void ) const
{
    return m_derivedToken;
}

const Token::Ptr& DerivedDefinition::mapsToken( void ) const
{
    return m_mapsToken;
}

const Token::Ptr& DerivedDefinition::assignmentToken( void ) const
{
    return m_assignmentToken;
}

void DerivedDefinition::setLeftBracketToken( const Token::Ptr& leftBracketToken )
{
    assert( m_leftBracketToken->token() == Grammar::Token::UNRESOLVED );
    m_leftBracketToken = leftBracketToken;
}

const Token::Ptr& DerivedDefinition::leftBracketToken( void ) const
{
    return m_leftBracketToken;
}

void DerivedDefinition::setRightBracketToken( const Token::Ptr& rightBracketToken )
{
    assert( m_rightBracketToken->token() == Grammar::Token::UNRESOLVED );
    m_rightBracketToken = rightBracketToken;
}

const Token::Ptr& DerivedDefinition::rightBracketToken( void ) const
{
    return m_rightBracketToken;
}

std::string DerivedDefinition::typeDescription( void ) const
{
    std::stringstream stream;
    stream << "(";

    const auto& innerDefinitions = arguments();
    for( const auto& innerDefinition : *innerDefinitions )
    {
        stream << " " << innerDefinition->typeDescription() << ", ";
    }

    if( innerDefinitions->size() > 0 )
    {
        stream.seekp( -2, stream.cur );
        stream << " ";
    }

    stream << ") -> " << returnType()->signature() << " ";
    return stream.str();
}

void DerivedDefinition::accept( Visitor& visitor )
{
    visitor.visit( *this );
}

Node::Ptr DerivedDefinition::clone( void ) const
{
    auto duplicate = std::make_shared< DerivedDefinition >(
        derivedToken(),
        identifier()->duplicate< Identifier >(),
        arguments()->duplicate< VariableDefinitions >(),
        mapsToken(),
        returnType()->duplicate< Type >(),
        assignmentToken(),
        expression()->duplicate< Expression >() );

    Definition::clone( *duplicate );
    duplicate->setLeftBracketToken( leftBracketToken() );
    duplicate->setRightBracketToken( rightBracketToken() );
    return duplicate;
}

//
//
// RuleDefinition
//

RuleDefinition::RuleDefinition(
    const Token::Ptr& ruleToken,
    const Identifier::Ptr& identifier,
    const VariableDefinitions::Ptr& arguments,
    const Token::Ptr& mapsToken,
    const Type::Ptr& returnType,
    const Token::Ptr& assignmentToken,
    const Rule::Ptr& rule )
: Definition( Node::ID::RULE_DEFINITION, identifier )
, m_arguments( arguments )
, m_returnType( returnType )
, m_rule( rule )
, m_ruleToken( ruleToken )
, m_mapsToken( mapsToken )
, m_assignmentToken( assignmentToken )
, m_leftBracketToken( Token::unresolved() )
, m_rightBracketToken( Token::unresolved() )
{
}

const VariableDefinitions::Ptr& RuleDefinition::arguments( void ) const
{
    return m_arguments;
}

const Type::Ptr& RuleDefinition::returnType( void ) const
{
    return m_returnType;
}

void RuleDefinition::setReturnType( const Type::Ptr& returnType )
{
    m_returnType = returnType;
}

const Rule::Ptr& RuleDefinition::rule( void ) const
{
    return m_rule;
}

const Token::Ptr& RuleDefinition::ruleToken( void ) const
{
    return m_ruleToken;
}

const Token::Ptr& RuleDefinition::mapsToken( void ) const
{
    return m_mapsToken;
}

const Token::Ptr& RuleDefinition::assignmentToken( void ) const
{
    return m_assignmentToken;
}

void RuleDefinition::setLeftBracketToken( const Token::Ptr& leftBracketToken )
{
    assert( m_leftBracketToken->token() == Grammar::Token::UNRESOLVED );
    m_leftBracketToken = leftBracketToken;
}

const Token::Ptr& RuleDefinition::leftBracketToken( void ) const
{
    return m_leftBracketToken;
}

void RuleDefinition::setRightBracketToken( const Token::Ptr& rightBracketToken )
{
    assert( m_rightBracketToken->token() == Grammar::Token::UNRESOLVED );
    m_rightBracketToken = rightBracketToken;
}

const Token::Ptr& RuleDefinition::rightBracketToken( void ) const
{
    return m_rightBracketToken;
}

std::string RuleDefinition::typeDescription( void ) const
{
    std::stringstream stream;
    stream << "(";

    const auto& innerDefinitions = arguments();
    for( const auto& innerDefinition : *innerDefinitions )
    {
        stream << " " << innerDefinition->typeDescription() << ", ";
    }

    if( innerDefinitions->size() > 0 )
    {
        stream.seekp( -2, stream.cur );
        stream << " ";
    }

    stream << ") -> " << returnType()->signature() << " ";
    return stream.str();
}

void RuleDefinition::accept( Visitor& visitor )
{
    visitor.visit( *this );
}

Node::Ptr RuleDefinition::clone( void ) const
{
    auto duplicate = std::make_shared< RuleDefinition >(
        ruleToken(),
        identifier()->duplicate< Identifier >(),
        arguments()->duplicate< VariableDefinitions >(),
        mapsToken(),
        returnType()->duplicate< Type >(),
        assignmentToken(),
        rule()->duplicate< Rule >() );

    Definition::clone( *duplicate );
    duplicate->setLeftBracketToken( leftBracketToken() );
    duplicate->setRightBracketToken( rightBracketToken() );
    return duplicate;
}

//
//
// EnumeratorDefinition
//

EnumeratorDefinition::EnumeratorDefinition( const Identifier::Ptr& identifier )
: Definition( Node::ID::ENUMERATOR_DEFINITION, identifier )
{
    setProperty( libcasm_ir::Property::SIDE_EFFECT_FREE );
    setProperty( libcasm_ir::Property::PURE );
}

std::string EnumeratorDefinition::typeDescription( void ) const
{
    return identifier()->name();
}

void EnumeratorDefinition::accept( Visitor& visitor )
{
    visitor.visit( *this );
}

Node::Ptr EnumeratorDefinition::clone( void ) const
{
    auto duplicate =
        std::make_shared< EnumeratorDefinition >( identifier()->duplicate< Identifier >() );

    Definition::clone( *duplicate );
    return duplicate;
}

//
//
// EnumerationDefinition
//

EnumerationDefinition::EnumerationDefinition(
    const Token::Ptr& enumerationToken,
    const Identifier::Ptr& identifier,
    const Token::Ptr& assignmentToken,
    const Token::Ptr& leftBraceToken,
    const Enumerators::Ptr& enumerators,
    const Token::Ptr& rightBraceToken )
: TypeDefinition(
      Node::ID::ENUMERATION_DEFINITION,
      CST::make< BasicType >(
          identifier->sourceLocation(), IdentifierPath::fromIdentifier( identifier ) ) )
, m_enumerators( enumerators )
, m_enumerationToken( enumerationToken )
, m_assignmentToken( assignmentToken )
, m_leftBraceToken( leftBraceToken )
, m_rightBraceToken( rightBraceToken )
{
    setProperty( libcasm_ir::Property::SIDE_EFFECT_FREE );
    setProperty( libcasm_ir::Property::PURE );
}

const Enumerators::Ptr& EnumerationDefinition::enumerators( void ) const
{
    return m_enumerators;
}

const Token::Ptr& EnumerationDefinition::enumerationToken( void ) const
{
    return m_enumerationToken;
}

const Token::Ptr& EnumerationDefinition::assignmentToken( void ) const
{
    return m_assignmentToken;
}

const Token::Ptr& EnumerationDefinition::leftBraceToken( void ) const
{
    return m_leftBraceToken;
}

const Token::Ptr& EnumerationDefinition::rightBraceToken( void ) const
{
    return m_rightBraceToken;
}

std::string EnumerationDefinition::typeDescription( void ) const
{
    return domainType()->signature();
}

void EnumerationDefinition::accept( Visitor& visitor )
{
    visitor.visit( *this );
}

Node::Ptr EnumerationDefinition::clone( void ) const
{
    auto duplicate = std::make_shared< EnumerationDefinition >(
        enumerationToken(),
        identifier()->duplicate< Identifier >(),
        assignmentToken(),
        leftBraceToken(),
        enumerators()->duplicate< Enumerators >(),
        rightBraceToken() );

    TypeDefinition::clone( *duplicate );
    return duplicate;
}

//
//
// UsingDefinition
//

UsingDefinition::UsingDefinition(
    const Token::Ptr& usingToken,
    const Identifier::Ptr& identifier,
    const Token::Ptr& assignmentToken,
    const Type::Ptr& aliasType )
: Definition( Node::ID::USING_DEFINITION, identifier )
, m_aliasType( aliasType )
, m_usingToken( usingToken )
, m_assignmentToken( assignmentToken )
{
}

const Type::Ptr& UsingDefinition::aliasType( void ) const
{
    return m_aliasType;
}

const Token::Ptr& UsingDefinition::usingToken( void ) const
{
    return m_usingToken;
}

const Token::Ptr& UsingDefinition::assignmentToken( void ) const
{
    return m_assignmentToken;
}

std::string UsingDefinition::typeDescription( void ) const
{
    return aliasType()->signature();
}

void UsingDefinition::accept( Visitor& visitor )
{
    visitor.visit( *this );
}

Node::Ptr UsingDefinition::clone( void ) const
{
    auto duplicate = std::make_shared< UsingDefinition >(
        usingToken(),
        identifier()->duplicate< Identifier >(),
        assignmentToken(),
        aliasType()->duplicate< Type >() );

    Definition::clone( *duplicate );
    return duplicate;
}

//
//
// UsingPathDefinition
//

UsingPathDefinition::UsingPathDefinition(
    const Token::Ptr& usingToken,
    const IdentifierPath::Ptr& path,
    const Token::Ptr& doubleColonToken,
    const Token::Ptr& asterixToken )
: Definition(
      Node::ID::USING_PATH_DEFINITION,
      CST::make< Identifier >( path->sourceLocation(), path->path() ) )
, m_path( path )
, m_usingToken( usingToken )
, m_doubleColonToken( doubleColonToken )
, m_asterixToken( asterixToken )
{
}

UsingPathDefinition::UsingPathDefinition(
    const Token::Ptr& usingToken, const IdentifierPath::Ptr& path )
: UsingPathDefinition( usingToken, path, Token::unresolved(), Token::unresolved() )
{
}

const IdentifierPath::Ptr& UsingPathDefinition::path( void ) const
{
    return m_path;
}

u1 UsingPathDefinition::explicitSymbol( void ) const
{
    return m_doubleColonToken->token() == Grammar::Token::UNRESOLVED and
           m_asterixToken->token() == Grammar::Token::UNRESOLVED;
}

const Token::Ptr& UsingPathDefinition::usingToken( void ) const
{
    return m_usingToken;
}

const Token::Ptr& UsingPathDefinition::doubleColonToken( void ) const
{
    return m_doubleColonToken;
}

const Token::Ptr& UsingPathDefinition::asterixToken( void ) const
{
    return m_asterixToken;
}

std::string UsingPathDefinition::typeDescription( void ) const
{
    return path()->path();
}

void UsingPathDefinition::accept( Visitor& visitor )
{
    visitor.visit( *this );
}

Node::Ptr UsingPathDefinition::clone( void ) const
{
    auto duplicate = std::make_shared< UsingPathDefinition >(
        usingToken(), path()->duplicate< IdentifierPath >(), doubleColonToken(), asterixToken() );

    Definition::clone( *duplicate );
    return duplicate;
}

//
//
// InvariantDefinition
//

InvariantDefinition::InvariantDefinition(
    const Token::Ptr& invariantToken,
    const Identifier::Ptr& identifier,
    const Token::Ptr& assignmentToken,
    const Expression::Ptr& expression )
: Definition( Node::ID::INVARIANT_DEFINITION, identifier )
, m_expression( expression )
, m_invariantToken( invariantToken )
, m_assignmentToken( assignmentToken )
{
}

const Expression::Ptr& InvariantDefinition::expression( void ) const
{
    return m_expression;
}

const Token::Ptr& InvariantDefinition::invariantToken( void ) const
{
    return m_invariantToken;
}

const Token::Ptr& InvariantDefinition::assignmentToken( void ) const
{
    return m_assignmentToken;
}

std::string InvariantDefinition::typeDescription( void ) const
{
    return "...";
}

void InvariantDefinition::accept( Visitor& visitor )
{
    visitor.visit( *this );
}

Node::Ptr InvariantDefinition::clone( void ) const
{
    auto duplicate = std::make_shared< InvariantDefinition >(
        invariantToken(),
        identifier()->duplicate< Identifier >(),
        assignmentToken(),
        expression()->duplicate< Expression >() );

    Definition::clone( *duplicate );
    return duplicate;
}

//
//
// DomainDefinition
//

DomainDefinition::DomainDefinition( const Token::Ptr& domainToken, const Type::Ptr& domainType )
: TypeDefinition( Node::ID::DOMAIN_DEFINITION, domainType )
, m_domainToken( domainToken )
{
}

const Token::Ptr& DomainDefinition::domainToken( void ) const
{
    return m_domainToken;
}

std::string DomainDefinition::typeDescription( void ) const
{
    return domainType()->signature();
}

void DomainDefinition::accept( Visitor& visitor )
{
    visitor.visit( *this );
}

Node::Ptr DomainDefinition::clone( void ) const
{
    auto duplicate =
        std::make_shared< DomainDefinition >( domainToken(), domainType()->duplicate< Type >() );

    TypeDefinition::clone( *duplicate );
    return duplicate;
}

//
//
// StructureDefinition
//

StructureDefinition::StructureDefinition(
    const Token::Ptr& structureToken,
    const Identifier::Ptr& identifier,
    const Token::Ptr& assignmentToken,
    const Token::Ptr& leftBraceToken,
    const FunctionDefinitions::Ptr& functions,
    const Token::Ptr& rightBraceToken )
: TypeDefinition(
      Node::ID::STRUCTURE_DEFINITION,
      CST::make< BasicType >(
          identifier->sourceLocation(), IdentifierPath::fromIdentifier( identifier ) ) )
, m_functions( functions )
, m_structureToken( structureToken )
, m_assignmentToken( assignmentToken )
, m_leftBraceToken( leftBraceToken )
, m_rightBraceToken( rightBraceToken )
{
}

const FunctionDefinitions::Ptr& StructureDefinition::functions( void ) const
{
    return m_functions;
}

const Token::Ptr& StructureDefinition::structureToken( void ) const
{
    return m_structureToken;
}

const Token::Ptr& StructureDefinition::assignmentToken( void ) const
{
    return m_assignmentToken;
}

const Token::Ptr& StructureDefinition::leftBraceToken( void ) const
{
    return m_leftBraceToken;
}

const Token::Ptr& StructureDefinition::rightBraceToken( void ) const
{
    return m_rightBraceToken;
}

std::string StructureDefinition::typeDescription( void ) const
{
    return domainType()->signature();
}

void StructureDefinition::accept( Visitor& visitor )
{
    visitor.visit( *this );
}

Node::Ptr StructureDefinition::clone( void ) const
{
    auto duplicate = std::make_shared< StructureDefinition >(
        structureToken(),
        identifier()->duplicate< Identifier >(),
        assignmentToken(),
        leftBraceToken(),
        functions()->duplicate< FunctionDefinitions >(),
        rightBraceToken() );

    TypeDefinition::clone( *duplicate );
    return duplicate;
}

//
//
// BehaviorDefinition
//

BehaviorDefinition::BehaviorDefinition(
    const Token::Ptr& behaviorToken,
    const Type::Ptr& domainType,
    const Token::Ptr& assignmentToken,
    const Token::Ptr& leftBraceToken,
    const Definitions::Ptr& definitions,
    const Token::Ptr& rightBraceToken )
: TypeDefinition( Node::ID::BEHAVIOR_DEFINITION, domainType )
, m_definitions( definitions )
, m_behaviorToken( behaviorToken )
, m_assignmentToken( assignmentToken )
, m_leftBraceToken( leftBraceToken )
, m_rightBraceToken( rightBraceToken )
{
}

const Definitions::Ptr& BehaviorDefinition::definitions( void ) const
{
    return m_definitions;
}

const Token::Ptr& BehaviorDefinition::behaviorToken( void ) const
{
    return m_behaviorToken;
}

const Token::Ptr& BehaviorDefinition::assignmentToken( void ) const
{
    return m_assignmentToken;
}

const Token::Ptr& BehaviorDefinition::leftBraceToken( void ) const
{
    return m_leftBraceToken;
}

const Token::Ptr& BehaviorDefinition::rightBraceToken( void ) const
{
    return m_rightBraceToken;
}

std::string BehaviorDefinition::typeDescription( void ) const
{
    return domainType()->signature();
}

void BehaviorDefinition::accept( Visitor& visitor )
{
    visitor.visit( *this );
}

Node::Ptr BehaviorDefinition::clone( void ) const
{
    auto duplicate = std::make_shared< BehaviorDefinition >(
        behaviorToken(),
        domainType()->duplicate< Type >(),
        assignmentToken(),
        leftBraceToken(),
        definitions()->duplicate< Definitions >(),
        rightBraceToken() );

    TypeDefinition::clone( *duplicate );
    return duplicate;
}

//
//
// ImplementDefinition
//

ImplementDefinition::ImplementDefinition(
    const Token::Ptr& implementToken,
    const Type::Ptr& behaviorType,
    const Token::Ptr& forToken,
    const Type::Ptr& domainType,
    const Token::Ptr& assignmentToken,
    const Token::Ptr& leftBraceToken,
    const Definitions::Ptr& definitions,
    const Token::Ptr& rightBraceToken )
: TypeDefinition( Node::ID::IMPLEMENT_DEFINITION, domainType )
, m_behaviorType( behaviorType )
, m_definitions( definitions )
, m_implementToken( implementToken )
, m_forToken( forToken )
, m_assignmentToken( assignmentToken )
, m_leftBraceToken( leftBraceToken )
, m_rightBraceToken( rightBraceToken )
{
}

ImplementDefinition::ImplementDefinition(
    const Token::Ptr& implementToken,
    const Type::Ptr& domainType,
    const Token::Ptr& assignmentToken,
    const Token::Ptr& leftBraceToken,
    const Definitions::Ptr& definitions,
    const Token::Ptr& rightBraceToken )
: ImplementDefinition(
      implementToken,
      std::make_shared< UnresolvedType >(),
      Token::unresolved(),
      domainType,
      assignmentToken,
      leftBraceToken,
      definitions,
      rightBraceToken )
{
}

const Type::Ptr& ImplementDefinition::behaviorType( void ) const
{
    return m_behaviorType;
}

const Definitions::Ptr& ImplementDefinition::definitions( void ) const
{
    return m_definitions;
}

const Token::Ptr& ImplementDefinition::implementToken( void ) const
{
    return m_implementToken;
}

const Token::Ptr& ImplementDefinition::forToken( void ) const
{
    return m_forToken;
}

const Token::Ptr& ImplementDefinition::assignmentToken( void ) const
{
    return m_assignmentToken;
}

const Token::Ptr& ImplementDefinition::leftBraceToken( void ) const
{
    return m_leftBraceToken;
}

const Token::Ptr& ImplementDefinition::rightBraceToken( void ) const
{
    return m_rightBraceToken;
}

u1 ImplementDefinition::hasBehavior( void ) const
{
    return behaviorType()->id() != Node::ID::UNRESOLVED_TYPE;
}

std::string ImplementDefinition::typeDescription( void ) const
{
    return domainType()->signature();
}

void ImplementDefinition::accept( Visitor& visitor )
{
    visitor.visit( *this );
}

Node::Ptr ImplementDefinition::clone( void ) const
{
    auto duplicate = std::make_shared< ImplementDefinition >(
        implementToken(),
        behaviorType()->duplicate< Type >(),
        forToken(),
        domainType()->duplicate< Type >(),
        assignmentToken(),
        leftBraceToken(),
        definitions()->duplicate< Definitions >(),
        rightBraceToken() );

    TypeDefinition::clone( *duplicate );
    return duplicate;
}

//
//
// BuiltinDefinition
//

BuiltinDefinition::BuiltinDefinition(
    const Token::Ptr& builtinToken, const RelationType::Ptr& domainType )
: TypeDefinition( Node::ID::BUILTIN_DEFINITION, domainType )
, m_builtinToken( builtinToken )
, m_targetId( libcasm_ir::Value::_SIZE_ )
{
    setProperty( libcasm_ir::Property::SIDE_EFFECT_FREE );
    setProperty( libcasm_ir::Property::PURE );
}

const Token::Ptr& BuiltinDefinition::builtinToken( void ) const
{
    return m_builtinToken;
}

const RelationType& BuiltinDefinition::relationType( void ) const
{
    return static_cast< const RelationType& >( *domainType() );
}

libcasm_ir::Value::ID BuiltinDefinition::targetId( void ) const
{
    assert( hasTargetId() );
    return m_targetId;
}

u1 BuiltinDefinition::hasTargetId( void ) const
{
    return m_targetId != libcasm_ir::Value::_SIZE_;
}

void BuiltinDefinition::setTargetId( const libcasm_ir::Value::ID targetId )
{
    m_targetId = targetId;
}

std::string BuiltinDefinition::typeDescription( void ) const
{
    return domainType()->signature();
}

void BuiltinDefinition::accept( Visitor& visitor )
{
    visitor.visit( *this );
}

Node::Ptr BuiltinDefinition::clone( void ) const
{
    auto duplicate = std::make_shared< BuiltinDefinition >(
        builtinToken(), relationType().duplicate< RelationType >() );

    TypeDefinition::clone( *duplicate );
    return duplicate;
}

//
//
// InitDefinition
//

InitDefinition::InitDefinition( const Token::Ptr& initToken, const IdentifierPath::Ptr& initPath )
: Definition(
      Node::ID::INIT_DEFINITION,
      CST::make< Identifier >( initToken->sourceLocation(), initToken->tokenString() ) )
, m_initToken( initToken )
, m_initPath( initPath )
, m_leftBraceToken( Token::unresolved() )
, m_initializers( CST::make< MappedExpressions >( initToken->sourceLocation() ) )
, m_rightBraceToken( Token::unresolved() )
, m_external( false )
{
}

InitDefinition::InitDefinition(
    const Token::Ptr& initToken,
    const Token::Ptr& leftBraceToken,
    const MappedExpressions::Ptr& initializers,
    const Token::Ptr& rightBraceToken )
: Definition(
      Node::ID::INIT_DEFINITION,
      CST::make< Identifier >( initToken->sourceLocation(), initToken->tokenString() ) )
, m_initToken( initToken )
, m_initPath( nullptr )
, m_leftBraceToken( leftBraceToken )
, m_initializers( initializers )
, m_rightBraceToken( rightBraceToken )
, m_external( false )
{
}

const IdentifierPath::Ptr& InitDefinition::initPath( void ) const
{
    return m_initPath;
}

const MappedExpressions::Ptr& InitDefinition::initializers( void ) const
{
    return m_initializers;
}

const Token::Ptr& InitDefinition::initToken( void ) const
{
    return m_initToken;
}

const Token::Ptr& InitDefinition::leftBraceToken( void ) const
{
    return m_leftBraceToken;
}

const Token::Ptr& InitDefinition::rightBraceToken( void ) const
{
    return m_rightBraceToken;
}

u1 InitDefinition::isSingleAgent( void ) const
{
    return m_initPath != nullptr;
}

u1 InitDefinition::external( void ) const
{
    return m_external;
}

void InitDefinition::setExternal( void )
{
    m_external = true;
}

std::string InitDefinition::typeDescription( void ) const
{
    return ( external() ? "external" : "internal" );
}

void InitDefinition::accept( Visitor& visitor )
{
    visitor.visit( *this );
}

Node::Ptr InitDefinition::clone( void ) const
{
    InitDefinition::Ptr duplicate;
    if( not isSingleAgent() )
    {
        duplicate = std::make_shared< InitDefinition >(
            initToken(),
            leftBraceToken(),
            initializers()->duplicate< MappedExpressions >(),
            rightBraceToken() );
    }
    else
    {
        duplicate = std::make_shared< InitDefinition >(
            initToken(), initPath()->duplicate< IdentifierPath >() );
    }

    Definition::clone( *duplicate );
    return duplicate;
}

//
//
// ImportDefinition
//

ImportDefinition::ImportDefinition( const Token::Ptr& importToken, const IdentifierPath::Ptr& path )
: ImportDefinition( importToken, path, Token::unresolved(), nullptr )
{
}

ImportDefinition::ImportDefinition(
    const Token::Ptr& importToken,
    const IdentifierPath::Ptr& path,
    const Token::Ptr& asToken,
    const Identifier::Ptr& identifier )
: Definition( Node::ID::IMPORT_DEFINITION, identifier )
, m_path( path )
, m_importToken( importToken )
, m_asToken( asToken )
{
}

const IdentifierPath::Ptr& ImportDefinition::path( void ) const
{
    return m_path;
}

const Token::Ptr& ImportDefinition::importToken( void ) const
{
    return m_importToken;
}

const Token::Ptr& ImportDefinition::asToken( void ) const
{
    return m_asToken;
}

std::string ImportDefinition::typeDescription( void ) const
{
    return path()->path();
}

void ImportDefinition::accept( Visitor& visitor )
{
    visitor.visit( *this );
}

Node::Ptr ImportDefinition::clone( void ) const
{
    auto duplicate = std::make_shared< ImportDefinition >(
        importToken(),
        path()->duplicate< IdentifierPath >(),
        asToken(),
        identifier()->duplicate< Identifier >() );

    Definition::clone( *duplicate );
    return duplicate;
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
