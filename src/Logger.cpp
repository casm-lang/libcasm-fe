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

#include "Logger.h"

#include "Exceptions.h"
#include "SourceLocation.h"

#include "../stdhl/cpp/String.h"

using namespace libcasm_fe;

namespace Log = libstdhl::Log;

static Log::Items to_location_items(
    const std::vector< SourceLocation >& locations )
{
    Log::Items items;
    for( const auto& location : locations )
    {
        items.add( libstdhl::make< Log::LocationItem >(
            *location.begin.fileName, location.begin.line,
            location.begin.column, location.end.line, location.end.column ) );
    }
    return items;
}

void Logger::error( const std::vector< SourceLocation >& locations,
    const std::string& message, libcasm_fe::Code errorCode )
{
    auto items = to_location_items( locations );
    items.add( libstdhl::make< Log::TextItem >( message ) );

    if( errorCode != Code::Unspecified )
    {
        std::unordered_set< std::string > usedErrorCodeStrings;

        for( const auto& location : locations )
        {
            const auto errorCodeString = libstdhl::String::format(
                "@%i{%04x}", location.begin.line, errorCode );

            const auto result = usedErrorCodeStrings.emplace( errorCodeString );
            if( not result.second )
            {
                continue;
            }

            items.add( libstdhl::make< Log::TextItem >( errorCodeString ) );
        }
    }

    log< Log::Level::ID::ERROR >( items );

    if( errorCode == Code::Unspecified )
    {
        warning( locations, "unspecified error code" );
    }
}

void Logger::error( const Exception& exception )
{
    error( exception.locations(), exception.what(), exception.errorCode() );
    info( "Backtrace:\n"
          + libstdhl::String::join( exception.backtrace(), "\n" ) );
}

void Logger::warning(
    const std::vector< SourceLocation >& locations, const std::string& message )
{
    auto items = to_location_items( locations );
    items.add( libstdhl::make< Log::TextItem >( message ) );
    log< Log::Level::ID::WARNING >( items );
}

void Logger::info(
    const std::vector< SourceLocation >& locations, const std::string& message )
{
    auto items = to_location_items( locations );
    items.add( libstdhl::make< Log::TextItem >( message ) );
    log< Log::Level::ID::INFORMATIONAL >( items );
}

void Logger::debug(
    const std::vector< SourceLocation >& locations, const std::string& message )
{
    auto items = to_location_items( locations );
    items.add( libstdhl::make< Log::TextItem >( message ) );
    log< Log::Level::ID::DEBUG >( items );
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
