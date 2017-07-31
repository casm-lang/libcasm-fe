//
//  Copyright (C) 2014-2021 CASM Organization <https://casm-lang.org>
//  All rights reserved.
//
//  Developed by: Philipp Paulweber
//                Emmanuel Pescosta
//                Jakob Moosbrugger
//                Florian Hahn
//                Ioan Molnar
//                <https://github.com/casm-lang/libcasm-fe>
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

#include <libcasm-fe/ast/Expression>
#include <libcasm-fe/ast/Literal>

#include "../various/GrammarToken.h"

using namespace libcasm_fe;
using namespace Ast;

static const auto unresolvedToken = std::make_shared< Ast::Token >( Grammar::Token::UNRESOLVED );

static const auto initDefinitionIdentifier = std::make_shared< Identifier >( "$init$" );

//
//
// Definition
//

Definition::Definition( Node::ID type, const Identifier::Ptr& identifier )
: TypedPropertyNode( type )
, m_identifier( identifier )
, m_attributes( std::make_shared< Attributes >() )
, m_delimiterToken( unresolvedToken )
, m_maxNumberOfLocals( 0 )
, m_exported( false )
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

void Definition::setExported( const u1 exported )
{
    m_exported = exported;
}

u1 Definition::exported( void ) const
{
    return m_exported;
}

//
//
// HeaderDefinition
//

HeaderDefinition::HeaderDefinition( const Token::Ptr& headerToken )
: Definition( Node::ID::HEADER_DEFINITION, std::make_shared< Identifier >( "$header$" ) )
, m_headerToken( headerToken )
{
}

const Token::Ptr& HeaderDefinition::headerToken( void ) const
{
    return m_headerToken;
}

void HeaderDefinition::accept( Visitor& visitor )
{
    visitor.visit( *this );
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
{
    setProperty( libcasm_ir::Property::SIDE_EFFECT_FREE );
    setProperty( libcasm_ir::Property::PURE );
}

const Type::Ptr& VariableDefinition::variableType( void ) const
{
    return m_variableType;
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

void VariableDefinition::accept( Visitor& visitor )
{
    visitor.visit( *this );
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

void FunctionDefinition::accept( Visitor& visitor )
{
    visitor.visit( *this );
}

//
//
// DerivedDefinition
//

DerivedDefinition::DerivedDefinition(
    const Token::Ptr& derivedToken,
    const Identifier::Ptr& identifier,
    const NodeList< VariableDefinition >::Ptr& arguments,
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
, m_leftBracketToken( unresolvedToken )
, m_rightBracketToken( unresolvedToken )
{
    setProperty( libcasm_ir::Property::SIDE_EFFECT_FREE );
}

const NodeList< VariableDefinition >::Ptr& DerivedDefinition::arguments( void ) const
{
    return m_arguments;
}

const Type::Ptr& DerivedDefinition::returnType( void ) const
{
    return m_returnType;
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

void DerivedDefinition::accept( Visitor& visitor )
{
    visitor.visit( *this );
}

//
//
// RuleDefinition
//

RuleDefinition::RuleDefinition(
    const Token::Ptr& ruleToken,
    const Identifier::Ptr& identifier,
    const NodeList< VariableDefinition >::Ptr& arguments,
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
, m_leftBracketToken( unresolvedToken )
, m_rightBracketToken( unresolvedToken )
{
}

const NodeList< VariableDefinition >::Ptr& RuleDefinition::arguments( void ) const
{
    return m_arguments;
}

const Type::Ptr& RuleDefinition::returnType( void ) const
{
    return m_returnType;
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

void RuleDefinition::accept( Visitor& visitor )
{
    visitor.visit( *this );
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

void EnumeratorDefinition::accept( Visitor& visitor )
{
    visitor.visit( *this );
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
: Definition( Node::ID::ENUMERATION_DEFINITION, identifier )
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

void EnumerationDefinition::accept( Visitor& visitor )
{
    visitor.visit( *this );
}

//
//
// UsingDefinition
//

UsingDefinition::UsingDefinition(
    const Token::Ptr& usingToken,
    const Identifier::Ptr& identifier,
    const Token::Ptr& assignmentToken,
    const Type::Ptr& type )
: Definition( Node::ID::USING_DEFINITION, identifier )
, m_type( type )
, m_usingToken( usingToken )
, m_assignmentToken( assignmentToken )
{
}

const Type::Ptr& UsingDefinition::type( void ) const
{
    return m_type;
}

const Token::Ptr& UsingDefinition::usingToken( void ) const
{
    return m_usingToken;
}

const Token::Ptr& UsingDefinition::assignmentToken( void ) const
{
    return m_assignmentToken;
}

void UsingDefinition::accept( Visitor& visitor )
{
    visitor.visit( *this );
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
: Definition( Node::ID::USING_PATH_DEFINITION, std::make_shared< Identifier >() )
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

void UsingPathDefinition::accept( Visitor& visitor )
{
    visitor.visit( *this );
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

void InvariantDefinition::accept( Visitor& visitor )
{
    visitor.visit( *this );
}

//
//
// StructureDefinition
//

StructureDefinition::StructureDefinition(
    const Identifier::Ptr& identifier, const FunctionDefinitions::Ptr& functions )
: Definition( Node::ID::STRUCTURE_DEFINITION, identifier )
, m_functions( functions )
{
}

const FunctionDefinitions::Ptr& StructureDefinition::functions( void ) const
{
    return m_functions;
}

void StructureDefinition::accept( Visitor& visitor )
{
    visitor.visit( *this );
}

//
//
// FeatureDefinition
//

FeatureDefinition::FeatureDefinition(
    const Identifier::Ptr& identifier, const Definitions::Ptr& definitions )
: Definition( Node::ID::FEATURE_DEFINITION, identifier )
, m_definitions( definitions )
{
}

const Definitions::Ptr& FeatureDefinition::definitions( void ) const
{
    return m_definitions;
}

void FeatureDefinition::accept( Visitor& visitor )
{
    visitor.visit( *this );
}

//
//
// ImplementationDefinition
//

ImplementationDefinition::ImplementationDefinition(
    const IdentifierPath::Ptr& path, const Type::Ptr& type, const Definitions::Ptr& definitions )
: Definition( Node::ID::IMPLEMENTATION_DEFINITION, *path->identifiers()->end() )
, m_path( path )
, m_type( type )
, m_definitions( definitions )
{
}

const IdentifierPath::Ptr& ImplementationDefinition::path( void ) const
{
    return m_path;
}

const Type::Ptr& ImplementationDefinition::type( void ) const
{
    return m_type;
}

const Definitions::Ptr& ImplementationDefinition::definitions( void ) const
{
    return m_definitions;
}

void ImplementationDefinition::accept( Visitor& visitor )
{
    visitor.visit( *this );
}

//
//
// DeclarationDefinition
//

DeclarationDefinition::DeclarationDefinition(
    const Identifier::Ptr& identifier,
    const Types::Ptr& argumentTypes,
    const Type::Ptr& returnType )
: Definition( Node::ID::DECLARATION_DEFINITION, identifier )
, m_argumentTypes( argumentTypes )
, m_returnType( returnType )
{
}

const Types::Ptr& DeclarationDefinition::argumentTypes( void ) const
{
    return m_argumentTypes;
}

const Type::Ptr& DeclarationDefinition::returnType( void ) const
{
    return m_returnType;
}

void DeclarationDefinition::setKind( const Kind kind )
{
    m_kind = kind;
}

DeclarationDefinition::Kind DeclarationDefinition::kind( void ) const
{
    return m_kind;
}

std::string DeclarationDefinition::kindName( void ) const
{
    switch( kind() )
    {
        case DeclarationDefinition::Kind::DERIVED:
        {
            return "derived";
        }
        case DeclarationDefinition::Kind::RULE:
        {
            return "rule";
        }
    }

    assert( !" internal error! " );
    return std::string();
}

void DeclarationDefinition::accept( Visitor& visitor )
{
    visitor.visit( *this );
}

//
//
// InitDefinition
//

InitDefinition::InitDefinition( const Token::Ptr& initToken, const IdentifierPath::Ptr& initPath )
: Definition( Node::ID::INIT_DEFINITION, initDefinitionIdentifier )
, m_initPath( initPath )
, m_initializers( std::make_shared< Initializers >() )
, m_initToken( initToken )
, m_leftBraceToken( unresolvedToken )
, m_rightBraceToken( unresolvedToken )
, m_programFunction( nullptr )
{
}

InitDefinition::InitDefinition(
    const Token::Ptr& initToken,
    const Token::Ptr& leftBraceToken,
    const Initializers::Ptr& initializers,
    const Token::Ptr& rightBraceToken )
: Definition( Node::ID::INIT_DEFINITION, initDefinitionIdentifier )
, m_initPath( nullptr )
, m_initializers( initializers )
, m_initToken( initToken )
, m_leftBraceToken( leftBraceToken )
, m_rightBraceToken( rightBraceToken )
, m_programFunction( nullptr )
{
}

const IdentifierPath::Ptr& InitDefinition::initPath( void ) const
{
    return m_initPath;
}

const Initializers::Ptr& InitDefinition::initializers( void ) const
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

void InitDefinition::setProgramFunction( const FunctionDefinition::Ptr& programFunction )
{
    assert( m_programFunction == nullptr );
    m_programFunction = programFunction;
}

const FunctionDefinition::Ptr& InitDefinition::programFunction( void ) const
{
    return m_programFunction;
}

u1 InitDefinition::isSingleAgent( void ) const
{
    return m_initPath != nullptr;
}

void InitDefinition::accept( Visitor& visitor )
{
    visitor.visit( *this );
}

//
//
// ImportDefinition
//

ImportDefinition::ImportDefinition( const Token::Ptr& importToken, const IdentifierPath::Ptr& path )
: ImportDefinition( importToken, path, unresolvedToken, std::make_shared< Identifier >() )
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

void ImportDefinition::accept( Visitor& visitor )
{
    visitor.visit( *this );
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
