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

#include "Driver.h"

using namespace libcasm_fe;

#define BOLD_BLACK "\x1b[1m"
#define BOLD_RED "\x1b[1;31m"
#define BOLD_GREEN "\x1b[1;32m"
#define BOLD_YELLOW "\x1b[1;33m"
#define BOLD_MAGENTA "\x1b[1;35m"
#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define YELLOW "\x1b[33m"
#define MAGENTA "\x1b[35m"
#define RESET "\x1b[0m"

extern int yylex_destroy( void );

// driver must be global, because it is needed for YY_INPUT
Driver* global_driver;

Driver::Driver()
: error_( 0 )
, warning_( 0 )
, trace_parsing( false )
, trace_scanning( false )
{
    file_ = nullptr;

    lines_.push_back( "" );
}

Driver::~Driver()
{
    if( file_ != nullptr )
    {
        fclose( file_ );
    }
    yylex_destroy();
}

size_t Driver::get_next_chars( char buf[], size_t max_size )
{
    if( fgets( buf, max_size, file_ ) == NULL )
    {
        if( ferror( file_ ) )
        {
            return -1;
        }
        else
        {
            return 0;
        }
    }
    else
    {
        // lines_ must not be empty (initialized with empty string in
        // constructor)
        lines_.back().append( buf );
        if( buf[ strlen( buf ) - 1 ] == '\n' )
        {
            lines_.push_back( "" );
        }
        return strlen( buf );
    }
}

void Driver::error(
    const yy::location& l, const std::string& m, libcasm_fe::Codes code )
{
    error( { l }, m, code );
}

void Driver::error( const std::vector< yy::location >& locations,
    const std::string& m, libcasm_fe::Codes code )
{
    assert( locations.size() > 0 );

    const yy::location& l = locations.at( 0 );

    // Set state to error!
    error_++;

    std::cerr << BOLD_BLACK << filename_ << ":" << l.begin.line << "."
              << l.begin.column << "-" << l.end.line << "." << l.end.column
              << ": " << BOLD_RED << "error: " << RESET << BOLD_BLACK << m
              << RESET;

    if( code != libcasm_fe::Codes::Unspecified )
    {
        for( const auto& loc : locations )
        {
            fprintf(
                stderr, " " YELLOW "@%i{%04x}" RESET, loc.begin.line, code );
        }
    }

    std::cerr << std::endl;

    for( auto loc : locations )
    {
        underline( loc );
    }

    if( code == libcasm_fe::Codes::Unspecified )
    {
        warning( l, "unspecified error code!" );
    }
}

void Driver::error( const Exception& exception )
{
    error(
        exception.getLocations(), exception.what(), exception.getErrorCode() );
}

void Driver::warning( const yy::location& l, const std::string& m )
{
    // increment warning counter
    warning_++;

    std::cerr << BOLD_BLACK << filename_ << ":" << l.begin.line << "."
              << l.begin.column << "-" << l.end.line << "." << l.end.column
              << ": " << BOLD_MAGENTA << "warning: " << RESET << BOLD_BLACK << m
              << RESET << std::endl;

    underline( l );
}

void Driver::info( const yy::location& l, const std::string& m )
{
    std::cerr << BOLD_BLACK << filename_ << ":" << l.begin.line << "."
              << l.begin.column << "-" << l.end.line << "." << l.end.column
              << ": " << BOLD_GREEN << "info: " << RESET << BOLD_BLACK << m
              << RESET << std::endl;

    underline( l );
}

void Driver::underline( const yy::location& l )
{
    if( l.begin.line == l.end.line && l.begin.line <= lines_.size() )
    {
        const std::string location_info
            = filename_ + ":" + std::to_string( l.begin.line ) + ": ";
        const std::string& error_line = lines_[ l.begin.line - 1 ];

        std::cerr << location_info << error_line
                  << std::string(
                         location_info.size() + l.begin.column - 1, ' ' )
                  << GREEN << "^"
                  << std::string( l.end.column - l.begin.column + 1, '-' )
                  << RESET << std::endl;
    }
    else
    {
        for( size_t i = l.begin.line; ( i <= l.end.line && i <= lines_.size() );
             i++ )
        {
            std::cerr << filename_ << ":" << i << " " << lines_[ i - 1 ];
        }
    }
}

bool Driver::ok() const
{
    return error_ == 0;
}

uint64_t Driver::get_error_count() const
{
    return error_;
}

uint64_t Driver::get_warning_count() const
{
    return warning_;
}

const std::string& Driver::get_filename()
{
    return filename_;
}
