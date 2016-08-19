//  
//  Copyright (c) 2014-2016 CASM Organization
//  All rights reserved.
//  
//  Developed by: Florian Hahn
//                Philipp Paulweber
//                Emmanuel Pescosta
//                https://github.com/ppaulweber/libcasm-fe
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


RuntimeException::RuntimeException
( const yy::location& location
, const std::string& msg
, const libcasm_fe::Codes error_code
)
: location_( location )
, msg_( msg )
, error_code_( error_code )
{
}

RuntimeException::RuntimeException
( const std::string& msg
, const libcasm_fe::Codes error_code
)
: RuntimeException
  ( yy::location( yy::position(0,0,0) ) // unknown
    // ( (std::string*)"asdf"
    // , 0
    // , 0
    // )
  , msg
  , error_code
  )
{
    fprintf( stderr, "RUNTIME_EXCEPTION_WITH_UNKNOWN_LOCATION!!!\n" );
}

const char* RuntimeException::what() const throw()
{
    return msg_.c_str();
}

const yy::location& RuntimeException::getLocation( void ) const
{
    return location_;
}

const libcasm_fe::Codes RuntimeException::getErrorCode( void ) const
{
    return error_code_;
}




const char* ImpossibleException::what() const throw()
{
    return "ImpossibleException";
}
