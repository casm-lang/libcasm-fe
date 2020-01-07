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

#include "Span.h"

#include <libstdhl/SourceLocation>

using namespace libcasm_fe;
using namespace AST;

//
//
// Span
//

Span::Span( const Grammar::Span kind, const std::size_t length )
: Node( Node::ID::SPAN )
, m_kind( kind )
, m_length( length )
{
}

const Grammar::Span Span::kind( void ) const
{
    return m_kind;
}

std::string Span::kindName( void ) const
{
    switch( kind() )
    {
        case Grammar::Span::SPACE:
        {
            return "space";
        }
        case Grammar::Span::NEWLINE:
        {
            return "newline";
        }
        case Grammar::Span::TABULATOR:
        {
            return "tabulator";
        }
        case Grammar::Span::INLINE_COMMENT:
        {
            return "inline comment";
        }
        case Grammar::Span::BLOCK_COMMENT:
        {
            return "block comment";
        }
    }
}

const std::size_t Span::length( void ) const
{
    return m_length;
}

std::string Span::toString( void ) const
{
    switch( kind() )
    {
        case Grammar::Span::SPACE:
        {
            return std::string( length(), ' ' );
        }
        case Grammar::Span::NEWLINE:
        {
            return std::string( length(), '\n' );
        }
        case Grammar::Span::TABULATOR:
        {
            return std::string( length(), '\t' );
        }
        case Grammar::Span::INLINE_COMMENT:
        {
            return sourceLocation().read();
        }
        case Grammar::Span::BLOCK_COMMENT:
        {
            return sourceLocation().read();
        }
    }

    assert( " error! " );
    return std::string();
}

void Span::accept( Visitor& visitor )
{
    visitor.visit( *this );
}

Node::Ptr Span::clone( void ) const
{
    auto duplicate = std::make_shared< Span >( kind(), length() );

    Node::clone( *duplicate );
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
