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

#include <libcasm-fe/lst/Expression>
#include <libcasm-fe/lst/Literal>

using namespace libcasm_fe;
using namespace LST;

//
//
// Definition
//

Definition::Definition(
    Node::ID id,
    const libcasm_ir::Type::Ptr& type,
    const libcasm_ir::Properties& properties,
    const Identifier::Ptr& identifier,
    const std::size_t maxNumberOfLocals )
: Node( id, type, properties )
, m_identifier( identifier )
, m_maxNumberOfLocals( maxNumberOfLocals )
{
}

const Identifier::Ptr& Definition::identifier( void ) const
{
    return m_identifier;
}

std::size_t Definition::maximumNumberOfLocals( void ) const
{
    return m_maxNumberOfLocals;
}

//
//
// VariableDefinition
//

VariableDefinition::VariableDefinition(
    const libcasm_ir::Type::Ptr& type,
    const libcasm_ir::Properties& properties,
    const Identifier::Ptr& identifier,
    const std::size_t maxNumberOfLocals,
    const std::size_t localIndex )
: Definition( Node::ID::VARIABLE_DEFINITION, type, properties, identifier, maxNumberOfLocals )
, m_localIndex( localIndex )
{
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
    const libcasm_ir::Type::Ptr& type,
    const libcasm_ir::Properties& properties,
    const Identifier::Ptr& identifier,
    const std::size_t maxNumberOfLocals,
    const Expression::Ptr& defined,
    const SequenceRule::Ptr& initially,
    const u1 symbolic,
    const u1 program,
    const u1 local )
: Definition( Node::ID::FUNCTION_DEFINITION, type, properties, identifier, maxNumberOfLocals )
, m_defined( defined )
, m_initially( initially )
, m_symbolic( symbolic )
, m_program( program )
, m_local( local )
{
}

const Expression::Ptr& FunctionDefinition::defined( void ) const
{
    return m_defined;
}

const SequenceRule::Ptr& FunctionDefinition::initially( void ) const
{
    return m_initially;
}

u1 FunctionDefinition::symbolic( void ) const
{
    return m_symbolic;
}

u1 FunctionDefinition::program( void ) const
{
    return m_program;
}

u1 FunctionDefinition::local( void ) const
{
    return m_local;
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
    const libcasm_ir::Type::Ptr& type,
    const libcasm_ir::Properties& properties,
    const Identifier::Ptr& identifier,
    const std::size_t maxNumberOfLocals,
    const VariableDefinitions::Ptr& arguments,
    const Expression::Ptr& expression )
: Definition( Node::ID::DERIVED_DEFINITION, type, properties, identifier, maxNumberOfLocals )
, m_arguments( arguments )
, m_expression( expression )
{
}

const VariableDefinitions::Ptr& DerivedDefinition::arguments( void ) const
{
    return m_arguments;
}

const Expression::Ptr& DerivedDefinition::expression( void ) const
{
    return m_expression;
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
    const libcasm_ir::Type::Ptr& type,
    const libcasm_ir::Properties& properties,
    const Identifier::Ptr& identifier,
    const std::size_t maxNumberOfLocals,
    const VariableDefinitions::Ptr& arguments,
    const Rule::Ptr& rule )
: Definition( Node::ID::RULE_DEFINITION, type, properties, identifier, maxNumberOfLocals )
, m_arguments( arguments )
, m_rule( rule )
{
}

const VariableDefinitions::Ptr& RuleDefinition::arguments( void ) const
{
    return m_arguments;
}

const Rule::Ptr& RuleDefinition::rule( void ) const
{
    return m_rule;
}

void RuleDefinition::accept( Visitor& visitor )
{
    visitor.visit( *this );
}

//
//
// EnumeratorDefinition
//

EnumeratorDefinition::EnumeratorDefinition(
    const libcasm_ir::Type::Ptr& type,
    const libcasm_ir::Properties& properties,
    const Identifier::Ptr& identifier,
    const std::size_t maxNumberOfLocals )
: Definition( Node::ID::ENUMERATOR_DEFINITION, type, properties, identifier, maxNumberOfLocals )
{
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
    const libcasm_ir::Type::Ptr& type,
    const libcasm_ir::Properties& properties,
    const Identifier::Ptr& identifier,
    const std::size_t maxNumberOfLocals,
    const Enumerators::Ptr& enumerators )
: Definition( Node::ID::ENUMERATION_DEFINITION, type, properties, identifier, maxNumberOfLocals )
, m_enumerators( enumerators )
{
}

const Enumerators::Ptr& EnumerationDefinition::enumerators( void ) const
{
    return m_enumerators;
}

void EnumerationDefinition::accept( Visitor& visitor )
{
    visitor.visit( *this );
}

//
//
// InvariantDefinition
//

InvariantDefinition::InvariantDefinition(
    const libcasm_ir::Type::Ptr& type,
    const libcasm_ir::Properties& properties,
    const Identifier::Ptr& identifier,
    const std::size_t maxNumberOfLocals,
    const Expression::Ptr& expression )
: Definition( Node::ID::INVARIANT_DEFINITION, type, properties, identifier, maxNumberOfLocals )
, m_expression( expression )
{
}

const Expression::Ptr& InvariantDefinition::expression( void ) const
{
    return m_expression;
}

void InvariantDefinition::accept( Visitor& visitor )
{
    visitor.visit( *this );
}

//
//
// DomainDefinition
//

DomainDefinition::DomainDefinition(
    const libcasm_ir::Type::Ptr& type,
    const libcasm_ir::Properties& properties,
    const Identifier::Ptr& identifier,
    const std::size_t maxNumberOfLocals )
: Definition( Node::ID::DOMAIN_DEFINITION, type, properties, identifier, maxNumberOfLocals )
{
}

void DomainDefinition::accept( Visitor& visitor )
{
    visitor.visit( *this );
}

//
//
// BuiltinDefinition
//

BuiltinDefinition::BuiltinDefinition(
    const libcasm_ir::Type::Ptr& type,
    const libcasm_ir::Properties& properties,
    const Identifier::Ptr& identifier,
    const std::size_t maxNumberOfLocals,
    const libcasm_ir::Value::ID targetId )
: Definition( Node::ID::BUILTIN_DEFINITION, type, properties, identifier, maxNumberOfLocals )
, m_targetId( targetId )
{
    assert( libcasm_ir::Value::_SIZE_ );
}

libcasm_ir::Value::ID BuiltinDefinition::targetId( void ) const
{
    return m_targetId;
}

void BuiltinDefinition::accept( Visitor& visitor )
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
