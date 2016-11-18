//
//  Copyright (c) 2014-2016 CASM Organization
//  All rights reserved.
//
//  Developed by: Florian Hahn
//                Philipp Paulweber
//                Emmanuel Pescosta
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

#include "Exceptions.h"


Exception::Exception
( const std::string& msg
, const libcasm_fe::Codes error_code
)
: msg_( msg )
, error_code_( error_code )
{
    addLocation( yy::location( yy::position(0,0,0) ) );
    fprintf( stderr, "RUNTIME_EXCEPTION_WITH_UNKNOWN_LOCATION!!!\n" );
}


Exception::Exception
( const yy::location& location
, const std::string& msg
, const libcasm_fe::Codes error_code
)
: msg_( msg )
, error_code_( error_code )
{
    addLocation( location );
}


Exception::Exception
( const std::vector< const yy::location* >& location
, const std::string& msg
, const libcasm_fe::Codes error_code
)
: msg_( msg )
, error_code_( error_code )
{
    for( auto loc : location )
    {
	addLocation( *loc );
    }
}



const char* Exception::what() const throw()
{
    return msg_.c_str();
}

void Exception::addLocation( const yy::location& location )
{
    location_.push_back( &location );
}

const std::vector< const yy::location* >& Exception::getLocations( void ) const
{
    return location_;
}

const libcasm_fe::Codes Exception::getErrorCode( void ) const
{
    return error_code_;
}

