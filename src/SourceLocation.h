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

#ifndef _LIBCASM_FE_SOURCE_LOCATION_H_
#define _LIBCASM_FE_SOURCE_LOCATION_H_

#include <libcasm-fe/CasmFE>

#include <sstream>

namespace libcasm_fe
{
    class SourcePosition
    {
      public:
        using value_type = u32;
        using difference_type = i32;

      public:
        explicit SourcePosition()
        : SourcePosition( nullptr, 1u, 1u )
        {
        }

        SourcePosition(
            const std::shared_ptr< std::string >& fileName, value_type line, value_type column )
        : fileName( fileName )
        , line( line )
        , column( column )
        {
        }

        /**
         * Advance to the COUNT next lines.
         */
        void lines( difference_type count )
        {
            if( count != 0 )
            {
                column = 1u;
                line = add_( line, count, 1 );
            }
        }

        /**
         * Advance to the COUNT next columns.
         */
        void columns( difference_type count )
        {
            column = add_( column, count, 1 );
        }

        /**
         * Add \a width columns, in place.
         */
        SourcePosition& operator+=( difference_type width )
        {
            columns( width );
            return *this;
        }

        /**
         * Add \a width columns.
         */
        friend SourcePosition operator+( SourcePosition lhs, difference_type width )
        {
            return lhs += width;
        }

        /**
         * Subtract \a width columns, in place.
         */
        SourcePosition& operator-=( difference_type width )
        {
            return operator+=( -width );
        }

        /**
         * Subtract \a width columns.
         */
        friend SourcePosition operator-( SourcePosition lhs, difference_type width )
        {
            return lhs += -width;
        }

        friend bool operator==( const SourcePosition& lhs, const SourcePosition& rhs )
        {
            return ( lhs.line == rhs.line ) and ( lhs.column == rhs.column ) and
                   ( ( lhs.fileName == rhs.fileName ) or
                     ( lhs.fileName and rhs.fileName and *lhs.fileName == *rhs.fileName ) );
        }

        friend bool operator!=( const SourcePosition& lhs, const SourcePosition& rhs )
        {
            return not( lhs == rhs );
        }

        friend std::ostream& operator<<( std::ostream& stream, const SourcePosition& position )
        {
            return stream << std::to_string( position.line ) << ":"
                          << std::to_string( position.column );
        }

      private:
        /**
         * Compute max(min, lhs+rhs) (provided min <= lhs).
         */
        static value_type add_( value_type lhs, difference_type rhs, difference_type min )
        {
            return ( 0 < rhs || -static_cast< value_type >( rhs ) < lhs ? rhs + lhs : min );
        }

      public:
        std::shared_ptr< std::string > fileName; /**< File name to which this position refers. */
        value_type line;                         /**< Current line number. */
        value_type column;                       /**< Current column number. */
    };

    class SourceLocation
    {
      public:
        explicit SourceLocation( const SourcePosition& position = SourcePosition() )
        : SourceLocation( position, position )
        {
        }

        SourceLocation( const SourcePosition& begin, const SourcePosition& end )
        : begin( begin )
        , end( end )
        {
        }

        /**
         * Reset initial location to final location.
         */
        void step()
        {
            begin = end;
        }

        /**
         * Extend the current location to the COUNT next columns.
         */
        void columns( SourcePosition::difference_type count )
        {
            end += count;
        }

        /**
         * Extend the current location to the COUNT next lines.
         */
        void lines( SourcePosition::difference_type count )
        {
            end.lines( count );
        }

        const std::shared_ptr< std::string >& fileName() const
        {
            return begin.fileName;
        }

        /**
         * Join two locations, in place.
         */
        SourceLocation& operator+=( const SourceLocation& rhs )
        {
            end = rhs.end;
            return *this;
        }

        /**
         * Join two locations.
         */
        friend SourceLocation operator+( SourceLocation lhs, const SourceLocation& rhs )
        {
            return lhs += rhs;
        }

        /**
         * Add \a width columns to the end position, in place.
         */
        SourceLocation& operator+=( SourcePosition::difference_type width )
        {
            columns( width );
            return *this;
        }

        /**
         * Add \a width columns to the end position.
         */
        friend SourceLocation operator+( SourceLocation lhs, SourcePosition::difference_type width )
        {
            return lhs += width;
        }

        /**
         * Subtract \a width columns from the end position, in place.
         */
        SourceLocation& operator-=( SourcePosition::difference_type width )
        {
            return operator+=( -width );
        }

        /**
         * Subtract \a width columns from the end position.
         */
        friend SourceLocation operator-( SourceLocation lhs, SourcePosition::difference_type width )
        {
            return lhs += -width;
        }

        friend bool operator==( const SourceLocation& lhs, const SourceLocation& rhs )
        {
            return lhs.begin == rhs.begin and lhs.end == rhs.end;
        }

        friend bool operator!=( const SourceLocation& lhs, const SourceLocation& rhs )
        {
            return not( lhs == rhs );
        }

        friend std::ostream& operator<<( std::ostream& stream, const SourceLocation& location )
        {
            if( location.begin != location.end )
            {
                return stream << location.begin << ".." << location.end;
            }
            else
            {
                return stream << location.begin;
            }
        }

      public:
        SourcePosition begin; /**< Beginning of the located region. */
        SourcePosition end;   /**< End of the located region. */
    };
}

#endif  // _LIBCASM_FE_SOURCE_LOCATION_H_

//
//  Local variables:
//  mode: c++
//  indent-tabs-mode: nil
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//
