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

#include "Exceptions.h"

using namespace libcasm_fe;

Exception::Exception( const std::string& msg, Code errorCode )
: Exception( SourceLocation(), msg, errorCode )
{
}

Exception::Exception(
    const SourceLocation& location, const std::string& msg, Code errorCode )
: Exception( location, msg, {}, errorCode )
{
}

Exception::Exception( const SourceLocation& location, const std::string& msg,
    const std::vector< std::string >& backtrace, Code errorCode )
: m_msg( msg )
, m_locations( { location } )
, m_backtrace( backtrace )
, m_errorCode( errorCode )
{
}

Exception::Exception( const std::vector< SourceLocation >& locations,
    const std::string& msg, Code errorCode )
: Exception( locations, msg, {}, errorCode )
{
}

Exception::Exception( const std::vector< SourceLocation >& locations,
    const std::string& msg, const std::vector< std::string >& backtrace,
    Code errorCode )
: m_msg( msg )
, m_locations( locations )
, m_backtrace( backtrace )
, m_errorCode( errorCode )
{
}

const char* Exception::what() const noexcept
{
    return m_msg.c_str();
}

const std::vector< SourceLocation >& Exception::locations( void ) const noexcept
{
    return m_locations;
}

const std::vector< std::string >& Exception::backtrace( void ) const noexcept
{
    return m_backtrace;
}

Code Exception::errorCode( void ) const noexcept
{
    return m_errorCode;
}
