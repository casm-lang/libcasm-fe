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

#ifndef _LIB_CASMFE_STACK_H_
#define _LIB_CASMFE_STACK_H_

#include <vector>

namespace libcasm_fe
{
    template < typename T >
    class Stack
    {
      public:
        explicit Stack( void )
        : m_values()
        {
        }

        void push( const T& value )
        {
            m_values.push_back( value );
        }

        T pop( void )
        {
            assert( not m_values.empty() );

            const auto value = m_values.back();
            m_values.pop_back();
            return value;
        }

        void drop( std::size_t amount = 1 )
        {
            assert( amount <= m_values.size() );
            for ( std::size_t i = 0; i < amount; ++i )
            {
                m_values.pop_back();
            }
        }

        T* top_ptr( std::size_t amount = 1 )
        {
            return &top() - amount + 1;
        }

        T& top( void )
        {
            assert( not m_values.empty() );

            return m_values.back();
        }

        void clear( void )
        {
            m_values.clear();
        }

      private:
        std::vector< T > m_values;
    };
}

#endif // _LIB_CASMFE_STACK_H_

//
//  Local variables:
//  mode: c++
//  indent-tabs-mode: nil
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//
