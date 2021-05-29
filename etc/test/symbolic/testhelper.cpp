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

#include "testhelper.h"

#include <cctype>

using namespace libcasm_fe;

class CheckIterator
{
    using iter = std::string::const_iterator;
	public:
    CheckIterator( const std::string& str )
    : m_it( str.begin() )
    , m_inSQuotes( false )
    , m_inDQuotes( false )
    {
    }

    bool inSQuotes(void)
    {
        return m_inSQuotes;
    }

	void toggleSQuotes(void) {
		m_inSQuotes = !m_inSQuotes;
	}

    bool inDQuotes(void)
    {
        return m_inDQuotes;
    }

	void toggleDQuotes(void) {
		m_inDQuotes = !m_inDQuotes;
	}

	CheckIterator operator++(void) {
		++m_it;
		return *this;
	}

	bool operator!=(const iter it) {
		return !(m_it == it);
	}

	bool operator==(const iter it) {
		return m_it == it;
	}
	char operator*(void) {
		return *m_it;
	}

  private:
    iter m_it;
    bool m_inSQuotes;
    bool m_inDQuotes;
};

CheckIterator&
nextChar( const std::string& str, CheckIterator& offset )
{
    bool inComment = false;
    for( ; offset != str.end(); ++offset )
    {
        char c = *offset;
        if( c == '\'' && !offset.inDQuotes() && !inComment )
        {
			offset.toggleSQuotes();
        }
        if( c == '"' && !offset.inSQuotes() && !inComment )
        {
			offset.toggleDQuotes();
        }
        if( c == '%' && !offset.inSQuotes() && !offset.inDQuotes() )
        {
            inComment = true;
        }
        if( c == '\n' )
        {
            inComment = false;
        }
        if( inComment || ( std::isspace( c ) && !offset.inSQuotes() && !offset.inDQuotes() ) )
        {
            continue;
        }
        return offset;
    }
    return offset;
}

bool TestHelper::compareTPTPFiles( const std::string& expected, const std::string& actual )
{
	auto expected_offset = CheckIterator(expected);
    //size_t expected_offset = nextChar( expected, 0 );
    auto actual_offset = CheckIterator( actual );

    while( nextChar(expected, expected_offset) != expected.end() && nextChar(actual, actual_offset) != actual.end() )
    {
        if( *expected_offset != *actual_offset )
        {
            return false;
        }
		++expected_offset;
		++actual_offset;
    }
	//consume whitespace and comments at the end
	expected_offset = nextChar( expected, expected_offset );
	actual_offset = nextChar( actual, actual_offset );
    return expected_offset == expected.end() && actual_offset == actual.end();
}
