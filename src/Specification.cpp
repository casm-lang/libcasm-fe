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

#include "Specification.h"

using namespace libcasm_fe;

Specification::Specification( void )
: m_name()
, m_header()
, m_definitions()
, m_symboltable( std::make_shared< Namespace >() )
{
}

void Specification::setName( const std::string& name )
{
    m_name = name;
}

const std::string& Specification::name( void ) const
{
    return m_name;
}

void Specification::setHeader( const Ast::HeaderDefinition::Ptr& header )
{
    m_header = header;
}

Ast::HeaderDefinition::Ptr Specification::header( void ) const
{
    return m_header;
}

void Specification::setDefinitions( const Ast::Definitions::Ptr& definitions )
{
    m_definitions = definitions;
}

const Ast::Definitions::Ptr& Specification::definitions( void ) const
{
    return m_definitions;
}

const Namespace::Ptr& Specification::symboltable( void ) const
{
    return m_symboltable;
}
