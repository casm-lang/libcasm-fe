//
//  Copyright (C) 2014-2022 CASM Organization <https://casm-lang.org>
//  All rights reserved.
//
//  Developed by: Philipp Paulweber et al.
//                <https://github.com/casm-lang/libcasm-fe/graphs/contributors>
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

#include "Configuration.h"

#include <libcasm-fe/Exception>
#include <libcasm-fe/Specification>

#include <libstdhl/File>
#include <libstdhl/String>
#include <libstdhl/Yaml>

using namespace libcasm_fe;

//
//
// Configuration
//

Configuration Configuration::fromString( const std::string& fileName )
{
    auto filePath = fileName;
    const auto lastSlashPos = filePath.find_last_of( '/' );
    if( lastSlashPos != std::string::npos )
    {
        filePath.erase( lastSlashPos );
        filePath += "/";
    }
    else
    {
        filePath = "";
    }

    std::fstream file;
    try
    {
        file = libstdhl::File::open( fileName );
    }
    catch( const std::invalid_argument& e )
    {
        throw ConfigurationException( fileName + ": " + e.what() );
    }

    libstdhl::Yaml::Content yamlFile;
    try
    {
        yamlFile = libstdhl::Yaml::Content::fromStream( file );
    }
    catch( const libstdhl::Yaml::Exception& e )
    {
        throw ConfigurationException( fileName + ": " + e.what() );
    }

    const auto& yaml = yamlFile;
    // log.debug( "project configuration:\n" + yaml.dump() );

    if( yaml.type() != libstdhl::Yaml::Type::MAP )
    {
        throw ConfigurationException( fileName + ": project configuration is not a map" );
    }

    if( not yaml.has( "CASM" ) )
    {
        throw ConfigurationException( fileName + ": project configuration has no 'CASM' key" );
    }
    else if( yaml[ "CASM" ].type() != libstdhl::Yaml::Type::MAP )
    {
        throw ConfigurationException(
            fileName + ": project configuration value of 'CASM' key is not a map" );
    }

    if( not yaml[ "CASM" ].has( "execute" ) )
    {
        throw ConfigurationException( fileName + ": project configuration has no 'execute' key" );
    }
    else if( yaml[ "CASM" ][ "execute" ].type() != libstdhl::Yaml::Type::STRING )
    {
        throw ConfigurationException(
            fileName + ": project configuration value of 'execute' key is not a string" );
    }

    const auto execute = yaml[ "CASM" ][ "execute" ].as< std::string >();
    Configuration configuration( fileName, filePath, execute );

    // search for optional 'imports'
    if( yaml[ "CASM" ].has( "imports" ) )
    {
        if( yaml[ "CASM" ][ "imports" ].type() != libstdhl::Yaml::Type::SEQUENCE )
        {
            throw ConfigurationException(
                fileName + ": project configuration value of 'imports' key is not a sequence" );
        }
        else
        {
            const auto& imports = yaml[ "CASM" ][ "imports" ];
            for( auto dependencyIndex = 0; dependencyIndex < imports.size(); dependencyIndex++ )
            {
                const auto dependency = imports[ dependencyIndex ];

                if( dependency.type() != libstdhl::Yaml::Type::MAP )
                {
                    throw ConfigurationException(
                        fileName + ": project configuration dependency '" +
                        std::to_string( dependencyIndex + 1 ) + "' of 'imports' is not a map" );
                }

                dependency.foreach( [ & ](
                                        const std::string& dependencyName,
                                        const libstdhl::Yaml::Content& dependencyLocation,
                                        u1& ) {
                    if( dependencyLocation.type() != libstdhl::Yaml::Type::STRING )
                    {
                        throw ConfigurationException(
                            fileName + ": project configuration 'imports' dependency '" +
                            dependencyName + "' is not a string" );
                    }

                    const auto dependencyLocationString = dependencyLocation.as< std::string >();

                    try
                    {
                        const auto dependencyLocationURI =
                            libstdhl::Standard::RFC3986::URI::fromString(
                                dependencyLocationString );
                        configuration.setImport( dependencyName, dependencyLocationURI );
                    }
                    catch( const std::invalid_argument& e )
                    {
                        const auto dependencyLocationURI =
                            libstdhl::Standard::RFC3986::URI::fromString(
                                "file:///" + dependencyLocationString );
                        configuration.setImport( dependencyName, dependencyLocationURI );
                    }
                } );
            }
        }
    }

    return configuration;
}

const std::string& Configuration::fileExtension( void )
{
    static const std::string fileExtensionString = Specification::fileExtension() + ".yml";
    return fileExtensionString;
}

Configuration::Configuration(
    const std::string& fileName, const std::string& filePath, const std::string& execute )
: m_fileName( fileName )
, m_filePath( filePath )
, m_execute( execute )
, m_imports()
{
}

const std::string& Configuration::fileName( void ) const
{
    return m_fileName;
}

const std::string& Configuration::filePath( void ) const
{
    return m_filePath;
}

const std::string& Configuration::execute( void ) const
{
    return m_execute;
}

void Configuration::setImport(
    const std::string& dependencyName, const libstdhl::Standard::RFC3986::URI& dependencyLocation )
{
    const auto result = m_imports.emplace( dependencyName, dependencyLocation );
    const auto& uri = result.first->second;

    if( not result.second )
    {
        throw ConfigurationException(
            "import dependency '" + dependencyName + "' already defined with location " +
            uri.toString() + "'" );
    }

    const auto uriScheme = uri.scheme();
    if( uriScheme != "file" )
    {
        throw ConfigurationException(
            "import dependency '" + dependencyName + "' has unsupported URI scheme '" + uriScheme +
            "' in location " + uri.toString() + "'" );
    }
    const auto uriPath = uri.path();
    if( not libstdhl::String::startsWith( uriPath, "/" ) )
    {
        throw ConfigurationException(
            "import dependency '" + dependencyName +
            "' must be a local one starting with '/', you provided '" + uri.toString() + "'" );
    }
}

libstdhl::Optional< libstdhl::Standard::RFC3986::URI > Configuration::import(
    const std::string& dependencyName ) const
{
    const auto it = m_imports.find( dependencyName );
    if( it != m_imports.cend() )
    {
        return it->second;
    }

    return libstdhl::nullopt;
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
