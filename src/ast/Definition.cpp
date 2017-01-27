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

#include "Definition.h"

using namespace libcasm_fe;
using namespace Ast;

Signature::Signature( const std::vector< libcasm_ir::Type* >& argumentTypes,
    libcasm_ir::Type* returnType )
: m_argumentTypes( argumentTypes )
, m_returnType( returnType )
{
}

Signature::Signature( const std::vector< libcasm_ir::Type* >& argumentTypes )
: Signature( argumentTypes, nullptr /* TODO should be void */ )
{
}

std::vector< libcasm_ir::Type* > Signature::argumentTypes() const
{
    return m_argumentTypes;
}

libcasm_ir::Type* Signature::returnType() const
{
    return m_returnType;
}

std::size_t Signature::arity() const
{
    return m_argumentTypes.size();
}

FunctionDefinition::FunctionDefinition( FunctionDefinition::Category category,
    const std::string& identifier,
    const Signature::Ptr& signature )
: Definition( Node::Type::FUNCTION_DEFINITION )
, m_category( category )
, m_identifier( identifier )
, m_signature( signature )
{
}

FunctionDefinition::Category FunctionDefinition::category() const
{
    return m_category;
}

std::string FunctionDefinition::identifier() const
{
    return m_identifier;
}

Signature::Ptr FunctionDefinition::signature() const
{
    return m_signature;
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

void FunctionDefinition::setDefaultValue( const Atom::Ptr& defaultValue )
{
    m_defaultValue = defaultValue;
}

Atom::Ptr FunctionDefinition::defaultValue() const
{
    return m_defaultValue;
}

DerivedDefinition::DerivedDefinition( const std::string& identifier,
    const Signature::Ptr& signature,
    const Expression::Ptr& expression )
: Definition( Node::Type::DERIVED_DEFINITION )
, m_identifier( identifier )
, m_signature( signature )
, m_expression( expression )
{
}

std::string DerivedDefinition::identifier() const
{
    return m_identifier;
}

Signature::Ptr DerivedDefinition::signature() const
{
    return m_signature;
}

Expression::Ptr DerivedDefinition::expression() const
{
    return m_expression;
}

RuleDefinition::RuleDefinition( const std::string& identifier,
    const Signature::Ptr& signature,
    const Rule::Ptr& rule )
: Definition( Node::Type::RULE_DEFINITION )
, m_identifier( identifier )
, m_signature( signature )
, m_rule( rule )
{
}

std::string RuleDefinition::identifier() const
{
    return m_identifier;
}

Signature::Ptr RuleDefinition::signature() const
{
    return m_signature;
}

Rule::Ptr RuleDefinition::innerRule() const
{
    return m_rule;
}

EnumerationDefinition::EnumerationDefinition( const std::string& identifier,
    const std::vector< std::string >& enumerators )
: Definition( Node::Type::ENUMERATION_DEFINITION )
, m_identifier( identifier )
, m_enumerators( enumerators )
{
}

std::string EnumerationDefinition::identifier() const
{
    return m_identifier;
}

std::vector< std::string > EnumerationDefinition::enumerators() const
{
    return m_enumerators;
}
