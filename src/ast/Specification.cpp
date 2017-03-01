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

#include "Specification.h"

using namespace libcasm_fe;
using namespace Ast;

Specification::Specification(
    const IdentifierNode::Ptr& name, const Definitions::Ptr& definitions )
: Node( Node::ID::SPECIFICATION )
, m_name( name )
, m_definitions( definitions )
{
}

IdentifierNode::Ptr Specification::name( void ) const
{
    return m_name;
}

Definitions::Ptr Specification::definitions( void ) const
{
    return m_definitions;
}
