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

#include "Definition.h"

using namespace libcasm_fe;
using namespace Ast;

Definition::Definition( Node::Type type, const IdentifierNode::Ptr& identifier )
: Node( type )
, m_identifier( identifier )
, m_relationType( nullptr )
{
}

IdentifierNode::Ptr Definition::identifier() const
{
    return m_identifier;
}

void Definition::setRelationType(
    const libcasm_ir::RelationType::Ptr& relationType )
{
    m_relationType = relationType;
}

libcasm_ir::RelationType::Ptr Definition::relationType() const
{
    return m_relationType;
}

VariableDefinition::VariableDefinition(
    const IdentifierNode::Ptr& identifier, const IdentifierNode::Ptr& typeName )
: Definition( Node::Type::VARIABLE_DEFINITION, identifier )
, m_typeName( typeName )
{
}

IdentifierNode::Ptr VariableDefinition::typeName() const
{
    return m_typeName;
}

FunctionDefinition::FunctionDefinition( const IdentifierNode::Ptr& identifier,
    const NodeList< IdentifierNode >::Ptr& argumentTypeNames,
    const IdentifierNode::Ptr& returnTypeName )
: Definition( Node::Type::FUNCTION_DEFINITION, identifier )
, m_classification( Classification::Controlled )
, m_argumentTypeNames( argumentTypeNames )
, m_returnTypeName( returnTypeName )
, m_symbolic( false )
, m_initializers( std::make_shared< NodeList< UpdateRule > >() )
, m_defaultValue( std::make_shared< UndefAtom >() )
{
}

NodeList< IdentifierNode >::Ptr FunctionDefinition::argumentTypeNames() const
{
    return m_argumentTypeNames;
}

IdentifierNode::Ptr FunctionDefinition::returnTypeName() const
{
    return m_returnTypeName;
}

void FunctionDefinition::setClassification(
    FunctionDefinition::Classification classification )
{
    m_classification = classification;
}

FunctionDefinition::Classification FunctionDefinition::classification() const
{
    return m_classification;
}

void FunctionDefinition::setSymbolic( bool symbolic )
{
    m_symbolic = symbolic;
}

bool FunctionDefinition::symbolic() const
{
    return m_symbolic;
}

void FunctionDefinition::setInitializers(
    const NodeList< UpdateRule >::Ptr& initializers )
{
    m_initializers = initializers;
}

NodeList< UpdateRule >::Ptr FunctionDefinition::initializers() const
{
    return m_initializers;
}

void FunctionDefinition::setDefaultValue( const Expression::Ptr& defaultValue )
{
    m_defaultValue = defaultValue;
}

Expression::Ptr FunctionDefinition::defaultValue() const
{
    return m_defaultValue;
}

DerivedDefinition::DerivedDefinition( const IdentifierNode::Ptr& identifier,
    const NodeList< VariableDefinition >::Ptr& arguments,
    const IdentifierNode::Ptr& returnTypeName,
    const Expression::Ptr& expression )
: Definition( Node::Type::DERIVED_DEFINITION, identifier )
, m_arguments( arguments )
, m_returnTypeName( returnTypeName )
, m_expression( expression )
{
}

NodeList< VariableDefinition >::Ptr DerivedDefinition::arguments() const
{
    return m_arguments;
}

IdentifierNode::Ptr DerivedDefinition::returnTypeName() const
{
    return m_returnTypeName;
}

Expression::Ptr DerivedDefinition::expression() const
{
    return m_expression;
}

RuleDefinition::RuleDefinition( const IdentifierNode::Ptr& identifier,
    const NodeList< VariableDefinition >::Ptr& arguments,
    const IdentifierNode::Ptr& returnTypeName,
    const Rule::Ptr& rule )
: Definition( Node::Type::RULE_DEFINITION, identifier )
, m_arguments( arguments )
, m_returnTypeName( returnTypeName )
, m_rule( rule )
{
}

NodeList< VariableDefinition >::Ptr RuleDefinition::arguments() const
{
    return m_arguments;
}

IdentifierNode::Ptr RuleDefinition::returnTypeName() const
{
    return m_returnTypeName;
}

Rule::Ptr RuleDefinition::rule() const
{
    return m_rule;
}

EnumerationDefinition::EnumerationDefinition(
    const IdentifierNode::Ptr& identifier,
    const NodeList< IdentifierNode >::Ptr& enumerators )
: Definition( Node::Type::ENUMERATION_DEFINITION, identifier )
, m_enumerators( enumerators )
{
}

NodeList< IdentifierNode >::Ptr EnumerationDefinition::enumerators() const
{
    return m_enumerators;
}
