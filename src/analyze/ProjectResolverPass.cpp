//
//  Copyright (C) 2014-2019 CASM Organization <https://casm-lang.org>
//  All rights reserved.
//
//  Developed by: Philipp Paulweber
//                Emmanuel Pescosta
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

#include "ProjectResolverPass.h"

#include <libcasm-fe/Configuration>
#include <libcasm-fe/Exception>
#include <libcasm-fe/Logger>
#include <libcasm-fe/analyze/TypeCheckPass>
#include <libcasm-fe/import/LibraryLoaderPass>
#include <libcasm-fe/transform/SourceToAstPass>

#include <libpass/PassRegistry>
#include <libpass/PassResult>
#include <libpass/PassUsage>

#include <libstdhl/String>
#include <libstdhl/Yaml>
#include <libstdhl/std/rfc3986>

using namespace libcasm_fe;
using namespace Ast;

char ProjectResolverPass::id = 0;

static libpass::PassRegistration< ProjectResolverPass > PASS(
    "ProjectResolverPass", "TODO", "project-resolve", 0 );

void ProjectResolverPass::usage( libpass::PassUsage& pu )
{
    pu.require< libpass::LoadFilePass >();
}

u1 ProjectResolverPass::run( libpass::PassResult& pr )
{
    libcasm_fe::Logger log( &id, stream() );

    const auto specification = pr.output< libpass::LoadFilePass >();
    auto specificationFileName = specification->filename();

    if( libstdhl::File::Path::exists( specificationFileName ) )
    {
        log.debug( "input filename '" + specificationFileName + "' is a directory" );
        if( specificationFileName == "." )
        {
            specificationFileName = "";
        }
        else if( not libstdhl::String::endsWith( specificationFileName, "/" ) )
        {
            specificationFileName += "/";
        }
        specificationFileName += ".casm.yml";
    }

    Project::Ptr project = nullptr;

    if( libstdhl::String::endsWith( specificationFileName, ".yml" ) or
        libstdhl::String::endsWith( specificationFileName, ".yaml" ) )
    {
        const auto configuration = std::make_shared< Configuration >( specificationFileName );
        const auto configurationFileName = configuration->fileName();
        const auto configurationFilePath = configuration->filePath();
        log.debug(
            "CASM project configuration provided as input YAML file '" + configurationFileName +
            "'" );

        try
        {
            auto file = libstdhl::File::open( configurationFileName );

            const auto yaml = libstdhl::Yaml::Content::fromStream( file );

            log.debug( "project configuration:\n" + yaml.dump() );

            if( yaml.type() != libstdhl::Yaml::Type::MAP )
            {
                throw libstdhl::Yaml::Exception(
                    configurationFileName + ": project configuration is not a map" );
            }

            if( not yaml.has( "CASM" ) )
            {
                throw libstdhl::Yaml::Exception(
                    configurationFileName + ": project configuration has no 'CASM' key" );
            }
            else if( yaml[ "CASM" ].type() != libstdhl::Yaml::Type::MAP )
            {
                throw libstdhl::Yaml::Exception(
                    configurationFileName +
                    ": project configuration value of 'CASM' key is not a map" );
            }

            if( not yaml[ "CASM" ].has( "execute" ) )
            {
                throw libstdhl::Yaml::Exception(
                    configurationFileName + ": project configuration has no 'execute' key" );
            }
            else if( yaml[ "CASM" ][ "execute" ].type() != libstdhl::Yaml::Type::STRING )
            {
                throw libstdhl::Yaml::Exception(
                    configurationFileName +
                    ": project configuration value of 'execute' key is not a string" );
            }
            else
            {
                const auto executeFileName = yaml[ "CASM" ][ "execute" ].as< std::string >();

                specificationFileName = configurationFilePath + executeFileName;
                const auto specification =
                    std::make_shared< libpass::LoadFilePass::Output >( specificationFileName );
                project = std::make_shared< Project >( specification, configuration );
            }

            // search for optional 'imports'
            if( yaml[ "CASM" ].has( "imports" ) )
            {
                if( yaml[ "CASM" ][ "imports" ].type() != libstdhl::Yaml::Type::SEQUENCE )
                {
                    throw libstdhl::Yaml::Exception(
                        configurationFileName +
                        ": project configuration value of 'imports' key is not a sequence" );
                }
                else
                {
                    const auto& imports = yaml[ "CASM" ][ "imports" ];
                    for( auto dependencyIndex = 0; dependencyIndex < imports.size();
                         dependencyIndex++ )
                    {
                        const auto dependency = imports[ dependencyIndex ];

                        if( dependency.type() != libstdhl::Yaml::Type::MAP )
                        {
                            throw libstdhl::Yaml::Exception(
                                configurationFileName + ": project configuration dependency '" +
                                std::to_string( dependencyIndex + 1 ) +
                                "' of 'imports' is not a map" );
                        }

                        dependency.foreach( [&]( const std::string& dependencyName,
                                                 const libstdhl::Yaml::Content& dependencyLocation,
                                                 u1& ) {
                            if( dependencyLocation.type() != libstdhl::Yaml::Type::STRING )
                            {
                                throw libstdhl::Yaml::Exception(
                                    configurationFileName +
                                    ": project configuration 'imports' dependency '" +
                                    dependencyName + "' is not a string" );
                            }

                            const auto dependencyLocationString =
                                dependencyLocation.as< std::string >();
                            const auto dependencyLocationURI =
                                libstdhl::Standard::RFC3986::URI::fromString(
                                    dependencyLocationString );

                            log.info( dependencyName + " : " + dependencyLocationURI.toString() );
                            configuration->setImport( dependencyName, dependencyLocationURI );
                        } );
                    }
                }
            }
        }
        catch( const libstdhl::Yaml::Exception& e )
        {
            log.error( e.what() );
        }
        catch( const std::invalid_argument& e )
        {
            log.error( e.what() );
        }
        catch( const ConfigurationImportException& e )
        {
            log.error( e.what() );
        }

        const auto errors = log.errors();
        if( errors > 0 )
        {
            log.debug( "found %lu error(s) during project configuration resolving", errors );
            return false;
        }
    }
    else
    {
        if( not libstdhl::String::endsWith( specificationFileName, ".casm" ) )
        {
            log.warning(
                "input filename '" + specificationFileName +
                "' has an unknown file extension, assume a CASM specification" );
        }

        project = std::make_shared< Project >( specification );
    }

    assert( project != nullptr );
    log.debug( "input filename '" + project->specification()->filename() + "'" );

    const auto errors = log.errors();
    if( errors > 0 )
    {
        log.debug( "found %lu error(s) during file resolving", errors );
        return false;
    }

    pr.setOutput< ProjectResolverPass >( project );

    return true;
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
