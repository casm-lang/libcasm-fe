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

#include "Node.h"

using namespace libcasm_fe;
using namespace Ast;

Node::Node( Node::ID id )
: m_id( id )
, m_sourceLocation()
{
}

Node::ID Node::id( void ) const
{
    return m_id;
}

void Node::setSourceLocation( const Location& sourceLocation )
{
    m_sourceLocation = sourceLocation;
}

const Location& Node::sourceLocation( void ) const
{
    return m_sourceLocation;
}

std::string Node::description( void ) const
{
    switch( m_id )
    {
        case ID::SPECIFICATION:
        {
            return "specification";
        }
        case ID::VARIABLE_DEFINITION:
        {
            return "variable";
        }
        case ID::FUNCTION_DEFINITION:
        {
            return "function";
        }
        case ID::DERIVED_DEFINITION:
        {
            return "derived";
        }
        case ID::RULE_DEFINITION:
        {
            return "rule";
        }
        case ID::ENUMERATION_DEFINITION:
        {
            return "enumeration";
        }
        case ID::VALUE_ATOM:
        {
            return "value";
        }
        case ID::RULE_REFERENCE_ATOM:
        {
            return "rule reference";
        }
        case ID::UNDEF_ATOM:
        {
            return "undef";
        }
        case ID::DIRECT_CALL_EXPRESSION:
        {
            return "direct call";
        }
        case ID::INDIRECT_CALL_EXPRESSION:
        {
            return "indirect call";
        }
        case ID::UNARY_EXPRESSION:
        {
            return "expression";
        }
        case ID::BINARY_EXPRESSION:
        {
            return "expression";
        }
        case ID::RANGE_EXPRESSION:
        {
            return "range";
        }
        case ID::LIST_EXPRESSION:
        {
            return "list";
        }
        case ID::CONDITIONAL_EXPRESSION:
        {
            return "conditional expression";
        }
        case ID::UNIVERSAL_QUANTIFIER_EXPRESSION:
        {
            return "universal quantifier";
        }
        case ID::EXISTENTIAL_QUANTIFIER_EXPRESSION:
        {
            return "existential quantifier";
        }
        case ID::SKIP_RULE:
        {
            return "skip";
        }
        case ID::CONDITIONAL_RULE:
        {
            return "conditional";
        }
        case ID::CASE_RULE:
        {
            return "case";
        }
        case ID::LET_RULE:
        {
            return "let";
        }
        case ID::FORALL_RULE:
        {
            return "forall";
        }
        case ID::CHOOSE_RULE:
        {
            return "choose";
        }
        case ID::ITERATE_RULE:
        {
            return "iterate";
        }
        case ID::BLOCK_RULE:
        {
            return "block";
        }
        case ID::SEQUENCE_RULE:
        {
            return "sequence";
        }
        case ID::UPDATE_RULE:
        {
            return "update";
        }
        case ID::CALL_RULE:
        {
            return "call";
        }
        case ID::UNRESOLVED_TYPE:
        {
            return "unresolved type";
        }
        case ID::BASIC_TYPE:
        {
            return "basic type";
        }
        case ID::COMPOSED_TYPE:
        {
            return "composed type";
        }
        case ID::FIXED_SIZED_TYPE:
        {
            return "fixed sized type";
        }
        case ID::RELATION_TYPE:
        {
            return "relation type";
        }
        case ID::BASIC_ATTRIBUTE:
        {
            return "basic attribute";
        }
        case ID::EXPRESSION_ATTRIBUTE:
        {
            return "expression attribute";
        }
        case ID::NODE_LIST:
        {
            return "node list";
        }
        case ID::IDENTIFIER:
        {
            return "identifier";
        }
        case ID::IDENTIFIER_PATH:
        {
            return "identifier path";
        }
        case ID::EXPRESSION_CASE:
        {
            return "expression case";
        }
        case ID::DEFAULT_CASE:
        {
            return "default case";
        }
    }
}

TypedNode::TypedNode( Node::ID id )
: Node( id )
, m_type( nullptr )
{
}

void TypedNode::setType( const libcasm_ir::Type::Ptr& type )
{
    m_type = type;
}

libcasm_ir::Type::Ptr TypedNode::type( void ) const
{
    return m_type;
}

Identifier::Identifier( const std::string& name )
: Node( Node::ID::IDENTIFIER )
, m_name( name )
{
}

const std::string& Identifier::name( void ) const
{
    return m_name;
}

void Identifier::accept( Visitor& visitor )
{
    visitor.visit( *this );
}

IdentifierPath::IdentifierPath( const Identifier::Ptr& identifier, Type type )
: Node( Node::ID::IDENTIFIER_PATH )
, m_identifiers( Ast::make< Identifiers >( identifier->sourceLocation() ) )
, m_type( type )
{
    m_identifiers->add( identifier );
}

IdentifierPath::IdentifierPath( const Identifiers::Ptr& identifiers, Type type )
: Node( Node::ID::IDENTIFIER_PATH )
, m_identifiers( identifiers )
, m_type( type )
{
    assert( not identifiers->empty() && "identifiers must not be empty" );
}

Identifiers::Ptr IdentifierPath::identifiers( void ) const
{
    return m_identifiers;
}

IdentifierPath::Type IdentifierPath::type( void ) const
{
    return m_type;
}

std::string IdentifierPath::baseName( void ) const
{
    assert( not m_identifiers->empty() ); // see ctor precondition
    return m_identifiers->back()->name();
}

std::string IdentifierPath::baseDir( void ) const
{
    const auto& p = path();
    return p.substr( 0, p.find_last_of( '.' ) );
}

std::string IdentifierPath::path( void ) const
{
    std::string path;

    if( m_type == Type::RELATIVE )
    {
        path += ".";
    }

    bool isFirstElement = true;
    for( const auto& identifier : *m_identifiers )
    {
        if( not isFirstElement )
        {
            path += ".";
        }
        path += identifier->name();
        isFirstElement = false;
    }

    return path;
}

void IdentifierPath::accept( Visitor& visitor )
{
    visitor.visit( *this );
}
