//
//  Copyright (C) 2014-2024 CASM Organization <https://casm-lang.org>
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

#include "Literal.h"

#include "../various/GrammarToken.h"

#include <libcasm-fe/cst/Token>

#include "Definition.h"

#include <libstdhl/File>
#include <libstdhl/String>

using namespace libcasm_fe;
using namespace CST;

//
//
// Literal
//

Literal::Literal( Node::ID id )
: Expression( id )
, m_leftBracket( Token::unresolved() )
, m_rightBracket( Token::unresolved() )
, m_spans( std::make_shared< Spans >() )
{
}

void Literal::setSpans( const Spans::Ptr& spans )
{
    m_spans = spans;
}

const Spans::Ptr& Literal::spans( void ) const
{
    return m_spans;
}

void Literal::setLeftBracket( const Token::Ptr& leftBracket )
{
    assert( m_leftBracket->token() == Grammar::Token::UNRESOLVED );
    m_leftBracket = leftBracket;
}

const Token::Ptr& Literal::leftBracket( void ) const
{
    return m_leftBracket;
}

void Literal::setRightBracket( const Token::Ptr& rightBracket )
{
    assert( m_rightBracket->token() == Grammar::Token::UNRESOLVED );
    m_rightBracket = rightBracket;
}

const Token::Ptr& Literal::rightBracket( void ) const
{
    return m_rightBracket;
}

void Literal::clone( Literal& duplicate ) const
{
    Expression::clone( duplicate );
    duplicate.setLeftBracket( leftBracket() );
    duplicate.setRightBracket( rightBracket() );
    duplicate.setSpans( spans() );
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

Node::Ptr UndefLiteral::clone( void ) const
{
    auto duplicate = std::make_shared< UndefLiteral >();

    Literal::clone( *duplicate );
    return duplicate;
}

//
//
// ValueLiteral
//

ValueLiteral::ValueLiteral( const libcasm_ir::Constant::Ptr& value )
: Literal( Node::ID::VALUE_LITERAL )
, m_value( value )
, m_radix( libstdhl::Type::Radix::DECIMAL )
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

void ValueLiteral::setRadix( const libstdhl::Type::Radix radix )
{
    m_radix = radix;
}

libstdhl::Type::Radix ValueLiteral::radix( void ) const
{
    return m_radix;
}

std::string ValueLiteral::toString( void ) const
{
    return sourceLocation().read();
}

void ValueLiteral::accept( Visitor& visitor )
{
    visitor.visit( *this );
}

Node::Ptr ValueLiteral::clone( void ) const
{
    auto duplicate = std::make_shared< ValueLiteral >( value() );

    Literal::clone( *duplicate );
    duplicate->setRadix( radix() );
    return duplicate;
}

//
//
// ReferenceLiteral
//

ReferenceLiteral::ReferenceLiteral( const Token::Ptr& at, const IdentifierPath::Ptr& identifier )
: Literal( Node::ID::REFERENCE_LITERAL )
, m_identifier( identifier )
, m_at( at )
, m_referenceType( ReferenceType::UNKNOWN )
, m_reference()
{
    setProperty( libcasm_ir::Property::SIDE_EFFECT_FREE );
    setProperty( libcasm_ir::Property::PURE );
}

const IdentifierPath::Ptr& ReferenceLiteral::identifier( void ) const
{
    return m_identifier;
}

const Token::Ptr& ReferenceLiteral::at( void ) const
{
    return m_at;
}

void ReferenceLiteral::setReferenceType( ReferenceType referenceType )
{
    m_referenceType = referenceType;
}

ReferenceLiteral::ReferenceType ReferenceLiteral::referenceType( void ) const
{
    return m_referenceType;
}

void ReferenceLiteral::setReference( const Definition::Ptr& reference )
{
    m_reference = reference;
}

const Definition::Ptr& ReferenceLiteral::reference( void ) const
{
    assert( m_reference != nullptr );
    return m_reference;
}

void ReferenceLiteral::accept( Visitor& visitor )
{
    visitor.visit( *this );
}

Node::Ptr ReferenceLiteral::clone( void ) const
{
    auto duplicate =
        std::make_shared< ReferenceLiteral >( at(), identifier()->duplicate< IdentifierPath >() );

    Literal::clone( *duplicate );
    duplicate->setReferenceType( referenceType() );
    duplicate->setReference( m_reference );
    return duplicate;
}

//
//
// SetLiteral
//

SetLiteral::SetLiteral( const Expressions::Ptr& expressions )
: Literal( Node::ID::SET_LITERAL )
, m_expressions( expressions )
{
}

const Expressions::Ptr& SetLiteral::expressions( void ) const
{
    return m_expressions;
}

void SetLiteral::accept( Visitor& visitor )
{
    visitor.visit( *this );
}

Node::Ptr SetLiteral::clone( void ) const
{
    auto duplicate = std::make_shared< SetLiteral >( expressions()->duplicate< Expressions >() );

    Literal::clone( *duplicate );
    return duplicate;
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

Node::Ptr ListLiteral::clone( void ) const
{
    auto duplicate = std::make_shared< ListLiteral >( expressions()->duplicate< Expressions >() );

    Literal::clone( *duplicate );
    return duplicate;
}

//
//
// RangeLiteral
//

RangeLiteral::RangeLiteral(
    const Expression::Ptr& left, const Token::Ptr& dotdot, const Expression::Ptr& right )
: Literal( Node::ID::RANGE_LITERAL )
, m_left( left )
, m_right( right )
, m_dotdot( dotdot )
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

const Token::Ptr& RangeLiteral::dotdot( void ) const
{
    return m_dotdot;
}

void RangeLiteral::accept( Visitor& visitor )
{
    visitor.visit( *this );
}

Node::Ptr RangeLiteral::clone( void ) const
{
    auto duplicate = std::make_shared< RangeLiteral >(
        left()->duplicate< Expression >(), dotdot(), right()->duplicate< Expression >() );

    Literal::clone( *duplicate );
    return duplicate;
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

Node::Ptr TupleLiteral::clone( void ) const
{
    auto duplicate = std::make_shared< TupleLiteral >( expressions()->duplicate< Expressions >() );

    Literal::clone( *duplicate );
    return duplicate;
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

Node::Ptr RecordLiteral::clone( void ) const
{
    auto duplicate =
        std::make_shared< RecordLiteral >( namedExpressions()->duplicate< NamedExpressions >() );

    Literal::clone( *duplicate );
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
