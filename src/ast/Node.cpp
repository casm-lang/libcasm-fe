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

libcasm_fe::Ast::Node::Node( libcasm_fe::Ast::Node::Type type )
: m_type( type )
, m_location()
{
}

libcasm_fe::Ast::Node::Type libcasm_fe::Ast::Node::type() const
{
    return m_type;
}

void libcasm_fe::Ast::Node::setLocation( const yy::location& location )
{
    m_location = location;
}

yy::location libcasm_fe::Ast::Node::location() const
{
    return m_location;
}

IdentifierNode::IdentifierNode( const std::string& identifier )
: Node( Node::Type::IDENTIFIER )
, m_identifier( identifier )
{
}

std::string IdentifierNode::identifier() const
{
    return m_identifier;
}
