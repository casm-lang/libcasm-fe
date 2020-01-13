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

#include <libcasm-fe/Namespace>
#include <libcasm-fe/ast/Expression>
#include <libcasm-fe/ast/Literal>

using namespace libcasm_fe;
using namespace AST;

//
//
// Definition
//

Definition::Definition( Node::ID type, const Identifier::Ptr& identifier )
: TypedPropertyNode( type )
, m_identifier( identifier )
, m_symboltable( std::make_shared< Namespace >() )
, m_templateSymbols( std::make_shared< VariableDefinitions >() )
, m_abstract( false )
, m_exported( false )
, m_maxNumberOfLocals( 0 )
{
}

const Identifier::Ptr& Definition::identifier( void ) const
{
    return m_identifier;
}

void Definition::setTemplateSymbols( const VariableDefinitions::Ptr& templateSymbols )
{
    m_templateSymbols = templateSymbols;
}

const VariableDefinitions::Ptr& Definition::templateSymbols( void ) const
{
    return m_templateSymbols;
}

u1 Definition::isTemplate( void ) const
{
    return templateSymbols()->size() != 0;
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

void Definition::setMaximumNumberOfLocals( std::size_t maxNumberOfLocals )
{
    m_maxNumberOfLocals = maxNumberOfLocals;
}

std::size_t Definition::maximumNumberOfLocals( void ) const
{
    return m_maxNumberOfLocals;
}

const Namespace::Ptr& Definition::symboltable( void ) const
{
    return m_symboltable;
}

void Definition::clone( Definition& duplicate ) const
{
    TypedPropertyNode::clone( duplicate );
    duplicate.setTemplateSymbols( templateSymbols() );
    duplicate.setAbstract( abstract() );
    duplicate.setExported( exported() );
    duplicate.setMaximumNumberOfLocals( maximumNumberOfLocals() );
}

//
//
// VariableDefinition
//

VariableDefinition::VariableDefinition(
    const Identifier::Ptr& identifier, const Type::Ptr& variableType )
: Definition( Node::ID::VARIABLE_DEFINITION, identifier )
, m_variableType( variableType )
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
        identifier()->duplicate< Identifier >(), variableType()->duplicate< Type >() );

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
      AST::make< Identifier >( domainType->name()->sourceLocation(), domainType->name()->path() ) )
, m_domainType( domainType )
, m_basicBehavior()
, m_extendedBehaviors()
{
}

const Type::Ptr& TypeDefinition::domainType( void ) const
{
    return m_domainType;
}

void TypeDefinition::setBasicBehavior( const ImplementDefinition::Ptr& basicBehavior )
{
    const auto& behaviorName = "*";
    auto behaviorNamespace = symboltable()->findNamespace( behaviorName );
    if( not behaviorNamespace )
    {
        behaviorNamespace = std::make_shared< Namespace >();
        symboltable()->registerNamespace( behaviorName, behaviorNamespace );
    }

    const auto& implementDefinition = basicBehavior;
    const auto& typeDefinition = implementDefinition->domainType()->typeDefinition();
    const auto& typeName = implementDefinition->domainType()->signature();
    behaviorNamespace->registerSymbol( typeName, implementDefinition->ptr< Definition >() );

    assert( not m_basicBehavior and " inconsistent state @ Namespace " );
    m_basicBehavior = implementDefinition;
}

const ImplementDefinition::Ptr& TypeDefinition::basicBehavior( void ) const
{
    return m_basicBehavior;
}

void TypeDefinition::addExtendedBehavior( const ImplementDefinition::Ptr& extendedBehavior )
{
    const auto& behaviorName = "+";
    auto behaviorNamespace = symboltable()->findNamespace( behaviorName );
    if( not behaviorNamespace )
    {
        behaviorNamespace = std::make_shared< Namespace >();
        symboltable()->registerNamespace( behaviorName, behaviorNamespace );
    }

    const auto& implementDefinition = extendedBehavior;
    const auto& typeDefinition = implementDefinition->behaviorType()->typeDefinition();
    const auto& typeName = implementDefinition->behaviorType()->signature();
    behaviorNamespace->registerSymbol( typeName, implementDefinition->ptr< Definition >() );

    assert( typeDefinition->id() == Node::ID::BEHAVIOR_DEFINITION );
    const auto& behaviorDefinition = typeDefinition->ptr< BehaviorDefinition >();
    const auto result = m_extendedBehaviors.emplace( typeName, implementDefinition );
    // assert( result.second and " inconsistent state @ Namespace " );
    if( not result.second )
    {
        throw std::domain_error( " inconsistent state " );
    }
}

const std::unordered_map< std::string, std::shared_ptr< ImplementDefinition > >&
TypeDefinition::extendedBehaviors( void ) const
{
    return m_extendedBehaviors;
}

void TypeDefinition::clone( TypeDefinition& duplicate ) const
{
    Definition::clone( duplicate );
    duplicate.setBasicBehavior( basicBehavior() );
    for( const auto& element : duplicate.extendedBehaviors() )
    {
        const auto& extendedBehavior = element.second;
        duplicate.addExtendedBehavior( extendedBehavior );
    }
}

//
//
// FunctionDefinition
//

FunctionDefinition::FunctionDefinition(
    const Identifier::Ptr& identifier,
    const Types::Ptr& argumentTypes,
    const Type::Ptr& returnType,
    const Expression::Ptr& defined,
    const MappedExpressions::Ptr& initially,
    const Classification classification,
    const u1 symbolic )
: Definition( Node::ID::FUNCTION_DEFINITION, identifier )
, m_argumentTypes( argumentTypes )
, m_returnType( returnType )
, m_defined( defined )
, m_initially( initially )
, m_classification( classification )
, m_symbolic( symbolic )
, m_program( identifier->name() == "program" )
, m_initiallyRule( AST::make< SkipRule >( initially->sourceLocation() ) )
{
    setProperty( libcasm_ir::Property::SIDE_EFFECT_FREE );
}

const Types::Ptr& FunctionDefinition::argumentTypes( void ) const
{
    return m_argumentTypes;
}

const Type::Ptr& FunctionDefinition::returnType( void ) const
{
    return m_returnType;
}

const Expression::Ptr& FunctionDefinition::defined( void ) const
{
    return m_defined;
}

const MappedExpressions::Ptr& FunctionDefinition::initially( void ) const
{
    return m_initially;
}

FunctionDefinition::Classification FunctionDefinition::classification( void ) const
{
    return m_classification;
}

std::string FunctionDefinition::classificationName( void ) const
{
    return CST::FunctionDefinition::toString( classification() );
}

u1 FunctionDefinition::symbolic( void ) const
{
    return m_symbolic;
}

bool FunctionDefinition::program( void ) const
{
    return m_program;
}

bool FunctionDefinition::local( void ) const
{
    return m_classification == Classification::LOCAL;
}

void FunctionDefinition::setInitiallyRule( const Rule::Ptr& initiallyRule )
{
    m_initiallyRule = initiallyRule;
}

const Rule::Ptr& FunctionDefinition::initiallyRule( void ) const
{
    return m_initiallyRule;
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
        identifier()->duplicate< Identifier >(),
        argumentTypes()->duplicate< Types >(),
        returnType()->duplicate< Type >(),
        defined()->duplicate< Expression >(),
        initially()->duplicate< MappedExpressions >(),
        classification(),
        symbolic() );

    Definition::clone( *duplicate );
    return duplicate;
}

//
//
// DerivedDefinition
//

DerivedDefinition::DerivedDefinition(
    const Identifier::Ptr& identifier,
    const VariableDefinitions::Ptr& arguments,
    const Type::Ptr& returnType,
    const Expression::Ptr& expression )
: Definition( Node::ID::DERIVED_DEFINITION, identifier )
, m_arguments( arguments )
, m_returnType( returnType )
, m_expression( expression )
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
        identifier()->duplicate< Identifier >(),
        arguments()->duplicate< VariableDefinitions >(),
        returnType()->duplicate< Type >(),
        expression()->duplicate< Expression >() );

    Definition::clone( *duplicate );
    return duplicate;
}

//
//
// RuleDefinition
//

RuleDefinition::RuleDefinition(
    const Identifier::Ptr& identifier,
    const VariableDefinitions::Ptr& arguments,
    const Type::Ptr& returnType,
    const Rule::Ptr& rule )
: Definition( Node::ID::RULE_DEFINITION, identifier )
, m_arguments( arguments )
, m_returnType( returnType )
, m_rule( rule )
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
        identifier()->duplicate< Identifier >(),
        arguments()->duplicate< VariableDefinitions >(),
        returnType()->duplicate< Type >(),
        rule()->duplicate< Rule >() );

    Definition::clone( *duplicate );
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
    const Identifier::Ptr& identifier, const Enumerators::Ptr& enumerators )
: TypeDefinition(
      Node::ID::ENUMERATION_DEFINITION,
      AST::make< BasicType >(
          identifier->sourceLocation(), IdentifierPath::fromIdentifier( identifier ) ) )
, m_enumerators( enumerators )
{
    setProperty( libcasm_ir::Property::SIDE_EFFECT_FREE );
    setProperty( libcasm_ir::Property::PURE );
}

const Enumerators::Ptr& EnumerationDefinition::enumerators( void ) const
{
    return m_enumerators;
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
        identifier()->duplicate< Identifier >(), enumerators()->duplicate< Enumerators >() );

    TypeDefinition::clone( *duplicate );
    return duplicate;
}

//
//
// UsingDefinition
//

UsingDefinition::UsingDefinition( const Identifier::Ptr& identifier, const Type::Ptr& aliasType )
: Definition( Node::ID::USING_DEFINITION, identifier )
, m_aliasType( aliasType )
{
}

const Type::Ptr& UsingDefinition::aliasType( void ) const
{
    return m_aliasType;
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
        identifier()->duplicate< Identifier >(), aliasType()->duplicate< Type >() );

    Definition::clone( *duplicate );
    return duplicate;
}

//
//
// UsingPathDefinition
//

UsingPathDefinition::UsingPathDefinition( const IdentifierPath::Ptr& path, const u1 explicitSymbol )
: Definition(
      Node::ID::USING_PATH_DEFINITION,
      AST::make< Identifier >( path->sourceLocation(), path->path() ) )
, m_path( path )
, m_explicitSymbol( explicitSymbol )
{
}

const IdentifierPath::Ptr& UsingPathDefinition::path( void ) const
{
    return m_path;
}

u1 UsingPathDefinition::explicitSymbol( void ) const
{
    return m_explicitSymbol;
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
        path()->duplicate< IdentifierPath >(), explicitSymbol() );

    Definition::clone( *duplicate );
    return duplicate;
}

//
//
// InvariantDefinition
//

InvariantDefinition::InvariantDefinition(
    const Identifier::Ptr& identifier, const Expression::Ptr& expression )
: Definition( Node::ID::INVARIANT_DEFINITION, identifier )
, m_expression( expression )
{
}

const Expression::Ptr& InvariantDefinition::expression( void ) const
{
    return m_expression;
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
        identifier()->duplicate< Identifier >(), expression()->duplicate< Expression >() );

    Definition::clone( *duplicate );
    return duplicate;
}

//
//
// DomainDefinition
//

DomainDefinition::DomainDefinition( const Type::Ptr& domainType )
: TypeDefinition( Node::ID::DOMAIN_DEFINITION, domainType )
{
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
    auto duplicate = std::make_shared< DomainDefinition >( domainType()->duplicate< Type >() );

    TypeDefinition::clone( *duplicate );
    return duplicate;
}

//
//
// StructureDefinition
//

StructureDefinition::StructureDefinition(
    const Type::Ptr& domainType, const FunctionDefinitions::Ptr& functions )
: TypeDefinition( Node::ID::STRUCTURE_DEFINITION, domainType )
, m_functions( functions )
{
}

const FunctionDefinitions::Ptr& StructureDefinition::functions( void ) const
{
    return m_functions;
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
        domainType()->duplicate< Type >(), functions()->duplicate< FunctionDefinitions >() );

    TypeDefinition::clone( *duplicate );
    return duplicate;
}

//
//
// BehaviorDefinition
//

BehaviorDefinition::BehaviorDefinition(
    const Type::Ptr& domainType, const Definitions::Ptr& definitions )
: TypeDefinition( Node::ID::BEHAVIOR_DEFINITION, domainType )
, m_definitions( definitions )
{
}

const Definitions::Ptr& BehaviorDefinition::definitions( void ) const
{
    return m_definitions;
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
        domainType()->duplicate< Type >(), definitions()->duplicate< Definitions >() );

    TypeDefinition::clone( *duplicate );
    return duplicate;
}

//
//
// ImplementDefinition
//

ImplementDefinition::ImplementDefinition(
    const Type::Ptr& behaviorType,
    const Type::Ptr& domainType,
    const Definitions::Ptr& definitions )
: TypeDefinition( Node::ID::IMPLEMENT_DEFINITION, domainType )
, m_behaviorType( behaviorType )
, m_definitions( definitions )
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

u1 ImplementDefinition::forBehaviorType( void ) const
{
    return domainType() != behaviorType();
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
        behaviorType()->duplicate< Type >(),
        domainType()->duplicate< Type >(),
        definitions()->duplicate< Definitions >() );

    TypeDefinition::clone( *duplicate );
    return duplicate;
}

//
//
// BuiltinDefinition
//

BuiltinDefinition::BuiltinDefinition(
    const Identifier::Ptr& identifier,
    const Types::Ptr& argumentTypes,
    const Type::Ptr& returnType )
: Definition( Node::ID::BUILTIN_DEFINITION, identifier )
, m_argumentTypes( argumentTypes )
, m_returnType( returnType )
, m_targetId( libcasm_ir::Value::_SIZE_ )
{
    setProperty( libcasm_ir::Property::SIDE_EFFECT_FREE );
    setProperty( libcasm_ir::Property::PURE );
}

const Types::Ptr& BuiltinDefinition::argumentTypes( void ) const
{
    return m_argumentTypes;
}

const Type::Ptr& BuiltinDefinition::returnType( void ) const
{
    return m_returnType;
}

void BuiltinDefinition::setTargetId( const libcasm_ir::Value::ID targetId )
{
    m_targetId = targetId;
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

std::string BuiltinDefinition::typeDescription( void ) const
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

void BuiltinDefinition::accept( Visitor& visitor )
{
    visitor.visit( *this );
}

Node::Ptr BuiltinDefinition::clone( void ) const
{
    auto duplicate = std::make_shared< BuiltinDefinition >(
        identifier()->duplicate< Identifier >(),
        argumentTypes()->duplicate< Types >(),
        returnType()->duplicate< Type >() );

    Definition::clone( *duplicate );
    return duplicate;
}

//
//
// InitDefinition
//

InitDefinition::InitDefinition( const MappedExpressions::Ptr& initializers, const u1 singleAgent )
: Definition(
      Node::ID::INIT_DEFINITION, AST::make< Identifier >( initializers->sourceLocation(), "init" ) )
, m_initializers( initializers )
, m_singleAgent( singleAgent )
, m_external( false )
{
}

const MappedExpressions::Ptr& InitDefinition::initializers( void ) const
{
    return m_initializers;
}

u1 InitDefinition::singleAgent( void ) const
{
    return m_singleAgent;
}

void InitDefinition::setExternal( void )
{
    m_external = true;
}

u1 InitDefinition::external( void ) const
{
    return m_external;
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
    auto duplicate = std::make_shared< InitDefinition >(
        initializers()->duplicate< MappedExpressions >(), singleAgent() );

    Definition::clone( *duplicate );
    if( external() )
    {
        duplicate->setExternal();
    }
    return duplicate;
}

//
//
// ImportDefinition
//

ImportDefinition::ImportDefinition(
    const IdentifierPath::Ptr& path, const Identifier::Ptr& identifier )
: Definition( Node::ID::IMPORT_DEFINITION, identifier )
, m_path( path )
{
}

const IdentifierPath::Ptr& ImportDefinition::path( void ) const
{
    return m_path;
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
        path()->duplicate< IdentifierPath >(), identifier()->duplicate< Identifier >() );

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
