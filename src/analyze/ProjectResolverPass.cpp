//
//  Copyright (C) 2014-2023 CASM Organization <https://casm-lang.org>
//  All rights reserved.
//
//  Developed by: Philipp Paulweber et al.
//  <https://github.com/casm-lang/libcasm-fe/graphs/contributors>
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

#include <libpass/PassRegistry>

#include <libstdhl/String>
#include <libstdhl/std/rfc3986>

using namespace libcasm_fe;

char ProjectResolverPass::id = 0;

static libpass::PassRegistration< ProjectResolverPass > PASS(
    "ProjectResolverPass", "TODO", "project-resolve", 0 );

//
//
// ProjectResolverPass
//

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
        const auto configurationFileName = specificationFileName;
        log.debug( "CASM project configuration input YAML file '" + configurationFileName + "'" );

        try
        {
            const auto configuration = std::make_shared< Configuration >(
                Configuration::fromString( configurationFileName ) );

            const auto specification = std::make_shared< libpass::LoadFilePass::Output >(
                configuration->filePath() + configuration->execute() );

            project = std::make_shared< Project >( specification, configuration );
        }
        catch( const ConfigurationException& e )
        {
            log.error( e.what() );
        }
        catch( const std::invalid_argument& e )
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
