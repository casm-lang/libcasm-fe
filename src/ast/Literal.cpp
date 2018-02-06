//
//  Copyright (C) 2014-2018 CASM Organization <https://casm-lang.org>
//  All rights reserved.
//
//  Developed by: Philipp Paulweber
//                Emmanuel Pescosta
//                Florian Hahn
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

#include "Literal.h"

#include "Definition.h"
#include "Type.h"

using namespace libcasm_fe;
using namespace Ast;

Literal::Literal( Node::ID id )
: Expression( id )
{
}

//
//
// UndefLiteral
//

UndefLiteral::UndefLiteral( void )
: Literal( Node::ID::UNDEF_LITERAL )
{
    setProperty( libcasm_ir::Property::SIDE_EFFECT_FREE );
    setProperty( libcasm_ir::Property::PURE );
}

void UndefLiteral::accept( Visitor& visitor )
{
    visitor.visit( *this );
}

//
//
// ValueLiteral
//

ValueLiteral::ValueLiteral( const libcasm_ir::Constant::Ptr& value )
: Literal( Node::ID::VALUE_LITERAL )
, m_value( value )
{
    Expression::setType( value->type().ptr_type() );

    setProperty( libcasm_ir::Property::SIDE_EFFECT_FREE );
    setProperty( libcasm_ir::Property::PURE );
}

const libcasm_ir::Constant::Ptr& ValueLiteral::value( void ) const
{
    return m_value;
}

void ValueLiteral::setValue( const libcasm_ir::Constant::Ptr& value )
{
    m_value = value;
    Expression::setType( m_value->type().ptr_type() );
}

void ValueLiteral::accept( Visitor& visitor )
{
    visitor.visit( *this );
}

//
//
// ReferenceLiteral
//

ReferenceLiteral::ReferenceLiteral( const IdentifierPath::Ptr& identifier )
: Literal( Node::ID::REFERENCE_LITERAL )
, m_identifier( identifier )
, m_referenceType( ReferenceType::UNKNOWN )
, m_reference( nullptr )
, m_builtinId( libcasm_ir::Value::ID::_SIZE_ )
{
    setProperty( libcasm_ir::Property::SIDE_EFFECT_FREE );
    setProperty( libcasm_ir::Property::PURE );
}

const IdentifierPath::Ptr& ReferenceLiteral::identifier() const
{
    return m_identifier;
}

void ReferenceLiteral::setReferenceType( ReferenceType referenceType )
{
    m_referenceType = referenceType;
}

ReferenceLiteral::ReferenceType ReferenceLiteral::referenceType( void ) const
{
    return m_referenceType;
}

void ReferenceLiteral::setReference( const TypedNode::Ptr& reference )
{
    m_reference = reference;
}

const TypedNode::Ptr& ReferenceLiteral::reference( void ) const
{
    assert(
        ( m_referenceType != ReferenceType::BUILTIN ) and
        ( m_referenceType != ReferenceType::UNKNOWN ) );

    return m_reference;
}

void ReferenceLiteral::setBuiltinId( libcasm_ir::Value::ID builtinId )
{
    m_builtinId = builtinId;
}

libcasm_ir::Value::ID ReferenceLiteral::builtinId( void ) const
{
    assert( m_referenceType == ReferenceType::BUILTIN );

    return m_builtinId;
}

void ReferenceLiteral::accept( Visitor& visitor )
{
    visitor.visit( *this );
}

//
//
// ListLiteral
//

ListLiteral::ListLiteral( const Expressions::Ptr& expressions )
: Literal( Node::ID::LIST_LITERAL )
, m_expressions( expressions )
{
}

const Expressions::Ptr& ListLiteral::expressions( void ) const
{
    return m_expressions;
}

void ListLiteral::accept( Visitor& visitor )
{
    visitor.visit( *this );
}

//
//
// RangeLiteral
//

RangeLiteral::RangeLiteral( const Expression::Ptr& left, const Expression::Ptr& right )
: Literal( Node::ID::RANGE_LITERAL )
, m_left( left )
, m_right( right )
{
}

const Expression::Ptr& RangeLiteral::left( void ) const
{
    return m_left;
}

const Expression::Ptr& RangeLiteral::right( void ) const
{
    return m_right;
}

void RangeLiteral::accept( Visitor& visitor )
{
    visitor.visit( *this );
}

//
//
// TupleLiteral
//

TupleLiteral::TupleLiteral( const Expressions::Ptr& expressions )
: Literal( Node::ID::TUPLE_LITERAL )
, m_expressions( expressions )
{
}

const Expressions::Ptr& TupleLiteral::expressions( void ) const
{
    return m_expressions;
}

void TupleLiteral::accept( Visitor& visitor )
{
    visitor.visit( *this );
}

//
//
// RecordLiteral
//

RecordLiteral::RecordLiteral( const NamedExpressions::Ptr& namedExpressions )
: Literal( Node::ID::RECORD_LITERAL )
, m_namedExpressions( namedExpressions )
{
}

const NamedExpressions::Ptr& RecordLiteral::namedExpressions( void ) const
{
    return m_namedExpressions;
}

void RecordLiteral::accept( Visitor& visitor )
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
