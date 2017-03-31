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

#ifndef _LIB_CASMFE_LOCATION_H_
#define _LIB_CASMFE_LOCATION_H_

#include <string>
#include <memory>

#include "../stdhl/cpp/Type.h"

namespace libcasm_fe
{
    class Position
    {
      public:
        using value_type = u32;
        using difference_type = i32;

      public:
        explicit Position()
        : Position( nullptr, 1u, 1u )
        {
        }

        Position( const std::shared_ptr< std::string >& fileName,
                  value_type line, value_type column )
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
        Position& operator+=( difference_type width )
        {
            columns( width );
            return *this;
        }

        /**
         * Add \a width columns.
         */
        friend Position operator+( Position lhs, difference_type width )
        {
            return lhs += width;
        }

        /**
         * Subtract \a width columns, in place.
         */
        Position& operator-=( difference_type width )
        {
            return operator+=( -width );
        }

        /**
         * Subtract \a width columns.
         */
        friend Position operator-( Position lhs, difference_type width )
        {
            return lhs += -width;
        }

        friend bool operator==( const Position& lhs, const Position& rhs )
        {
            return (lhs.line == rhs.line) and (lhs.column == rhs.column)
                and ((lhs.fileName == rhs.fileName)
                    or (lhs.fileName and rhs.fileName
                        and *lhs.fileName == *rhs.fileName));
        }

        friend bool operator!= ( const Position& lhs, const Position& rhs )
        {
            return not(lhs == rhs);
        }

        friend std::ostream& operator<<( std::ostream& stream, const Position& position )
        {
            return stream << std::to_string( position.line ) << ":"
                          << std::to_string( position.column );
        }

      private:
        /**
         * Compute max(min, lhs+rhs) (provided min <= lhs).
         */
        static value_type add_(value_type lhs, difference_type rhs, difference_type min)
        {
            return (0 < rhs || -static_cast<value_type>(rhs) < lhs
                    ? rhs + lhs
                    : min);
        }

      public:
        std::shared_ptr< std::string > fileName; /**< File name to which this position refers. */
        value_type line; /**< Current line number. */
        value_type column; /**< Current column number. */
    };

    class Location
    {
      public:
        explicit Location( const Position& position = Position() )
        : Location( position, position )
        {
        }

        Location( const Position& begin, const Position& end )
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
        void columns( Position::difference_type count )
        {
            end += count;
        }

        /**
         * Extend the current location to the COUNT next lines.
         */
        void lines( Position::difference_type count )
        {
            end.lines(count);
        }

        const std::shared_ptr<std::string>& fileName() const
        {
            return begin.fileName;
        }

        /**
         * Join two locations, in place.
         */
        Location& operator+=( const Location &rhs )
        {
            end = rhs.end;
            return *this;
        }

        /**
         * Join two locations.
         */
        friend Location operator+( Location lhs, const Location &rhs )
        {
            return lhs += rhs;
        }

        /**
         * Add \a width columns to the end position, in place.
         */
        Location& operator+=( Position::difference_type width )
        {
            columns( width );
            return *this;
        }

        /**
         * Add \a width columns to the end position.
         */
        friend Location operator+( Location lhs, Position::difference_type width )
        {
            return lhs += width;
        }

        /**
         * Subtract \a width columns from the end position, in place.
         */
        Location& operator-=( Position::difference_type width )
        {
            return operator+=( -width );
        }

        /**
         * Subtract \a width columns from the end position.
         */
        friend Location operator-( Location lhs, Position::difference_type width )
        {
            return lhs += -width;
        }

        friend bool operator==( const Location& lhs, const Location& rhs )
        {
            return lhs.begin == rhs.begin and lhs.end == rhs.end;
        }

        friend bool operator!= ( const Location& lhs, const Location& rhs )
        {
            return not(lhs == rhs);
        }

        friend std::ostream& operator<<( std::ostream& stream, const Location& location )
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
        Position begin; /**< Beginning of the located region. */
        Position end; /**< End of the located region. */
    };
}

#endif // _LIB_CASMFE_LOCATION_H_

//
//  Local variables:
//  mode: c++
//  indent-tabs-mode: nil
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//
