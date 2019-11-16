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

#include "Node.h"

#include <libcasm-fe/ast/Declaration>

#include <cassert>

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

void Node::setSourceLocation( const libstdhl::SourceLocation& sourceLocation )
{
    m_sourceLocation = sourceLocation;
}

const libstdhl::SourceLocation& Node::sourceLocation( void ) const
{
    return m_sourceLocation;
}

std::string Node::description( void ) const
{
    switch( m_id )
    {
        case ID::HEADER_DEFINITION:
        {
            return "header";
        }
        case ID::INIT_DEFINITION:
        {
            return "init";
        }
        case ID::INITIALLY:
        {
            return "initially";
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
        case ID::ENUMERATOR_DEFINITION:
        {
            return "enumerator";
        }
        case ID::ENUMERATION_DEFINITION:
        {
            return "enumeration";
        }
        case ID::USING_DEFINITION:
        {
            return "using";
        }
        case ID::USING_PATH_DEFINITION:
        {
            return "using path";
        }
        case ID::INVARIANT_DEFINITION:
        {
            return "invariant";
        }
        case ID::IMPORT_DEFINITION:
        {
            return "import";
        }
        case ID::DOMAIN_DEFINITION:
        {
            return "domain";
        }
        case ID::STRUCTURE_DEFINITION:
        {
            return "structure";
        }
        case ID::FEATURE_DEFINITION:
        {
            return "feature";
        }
        case ID::IMPLEMENT_DEFINITION:
        {
            return "implement";
        }
        case ID::BUILTIN_DEFINITION:
        {
            return "builtin";
        }
        case ID::DECLARATION:
        {
            const auto& declaration = static_cast< const Declaration& >( *this );
            return declaration.kindName() + " declaration";
        }
        // literals
        case ID::UNDEF_LITERAL:
        {
            return "undef";
        }
        case ID::VALUE_LITERAL:
        {
            return "value";
        }
        case ID::REFERENCE_LITERAL:
        {
            return "reference";
        }
        case ID::RANGE_LITERAL:
        {
            return "range";
        }
        case ID::LIST_LITERAL:
        {
            return "list";
        }
        case ID::TUPLE_LITERAL:
        {
            return "tuple";
        }
        case ID::RECORD_LITERAL:
        {
            return "record";
        }
        case ID::EMBRACED_EXPRESSION:
        {
            return "embraced expression";
        }
        case ID::NAMED_EXPRESSION:
        {
            return "named expression";
        }
        case ID::DIRECT_CALL_EXPRESSION:
        {
            return "direct call";
        }
        case ID::METHOD_CALL_EXPRESSION:
        {
            return "method call";
        }
        case ID::LITERAL_CALL_EXPRESSION:
        {
            return "literal call";
        }
        case ID::INDIRECT_CALL_EXPRESSION:
        {
            return "indirect call";
        }
        case ID::TYPE_CASTING_EXPRESSION:
        {
            return "type casting expression";
        }
        case ID::UNARY_EXPRESSION:
        {
            return "expression";
        }
        case ID::BINARY_EXPRESSION:
        {
            return "expression";
        }
        case ID::LET_EXPRESSION:
        {
            return "let expression";
        }
        case ID::CONDITIONAL_EXPRESSION:
        {
            return "conditional expression";
        }
        case ID::CHOOSE_EXPRESSION:
        {
            return "choose expression";
        }
        case ID::UNIVERSAL_QUANTIFIER_EXPRESSION:
        {
            return "universal quantifier";
        }
        case ID::EXISTENTIAL_QUANTIFIER_EXPRESSION:
        {
            return "existential quantifier";
        }
        case ID::CARDINALITY_EXPRESSION:
        {
            return "cardinality expression";
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
        case ID::LOCAL_RULE:
        {
            return "local";
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
        case ID::WHILE_RULE:
        {
            return "while";
        }
        case ID::UNRESOLVED_TYPE:
        {
            return "unresolved type";
        }
        case ID::BASIC_TYPE:
        {
            return "basic type";
        }
        case ID::TUPLE_TYPE:
        {
            return "tuple type";
        }
        case ID::RECORD_TYPE:
        {
            return "record type";
        }
        case ID::TEMPLATE_TYPE:
        {
            return "template type";
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
        // helper
        case ID::DEFINED:
        {
            return "defined";
        }
        case ID::INITIALIZER:
        {
            return "initializer";
        }
        // other
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
        case ID::VARIABLE_BINDING:
        {
            return "variable binding";
        }
        case ID::TOKEN:
        {
            return "token";
        }
        case ID::SPAN:
        {
            return "span";
        }
    }

    assert( !" internal error! " );
    return std::string();
}

//
//
// TypedNode
//

TypedNode::TypedNode( Node::ID id )
: Node( id )
, m_type( nullptr )
{
}

void TypedNode::setType( const libcasm_ir::Type::Ptr& type )
{
    m_type = type;
}

const libcasm_ir::Type::Ptr& TypedNode::type( void ) const
{
    return m_type;
}

//
//
// TypedPropertyNode
//

TypedPropertyNode::TypedPropertyNode( Node::ID id )
: TypedNode( id )
, m_properties( {} )
{
}

void TypedPropertyNode::setProperty( const libcasm_ir::Property property )
{
    m_properties.set( property );
}

void TypedPropertyNode::setProperties( const libcasm_ir::Properties& properties )
{
    m_properties = properties;
}

const libcasm_ir::Properties& TypedPropertyNode::properties( void ) const
{
    return m_properties;
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
