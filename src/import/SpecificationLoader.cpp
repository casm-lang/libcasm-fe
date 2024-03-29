//
//  Copyright (C) 2014-2024 CASM Organization <https://casm-lang.org>
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

#include "SpecificationLoader.h"

#include <libcasm-fe/analyze/TemplatingPass>
#include <libcasm-fe/import/FileLoadingStrategy>
#include <libcasm-fe/import/ImportError>
#include <libcasm-fe/import/LibraryLoaderPass>
#include <libcasm-fe/import/PathLoadingStrategy>
#include <libcasm-fe/transform/CstToAstPass>

#include <libpass/PassLogger>
#include <libpass/PassManager>
#include <libpass/analyze/LoadFilePass>

#include <libstdhl/File>
#include <libstdhl/String>

#include <iostream>

#include "CASM.casm.h"

using namespace libcasm_fe;

SpecificationLoader::SpecificationLoader(
    libstdhl::Log::Stream& logStream, const LoadingStrategy::Ptr& loadingStrategy )
: m_logStream( logStream )
, m_loadingStrategy( loadingStrategy )
, m_specificationRepository( std::make_shared< SpecificationRepository >() )
{
}

const SpecificationRepository::Ptr& SpecificationLoader::specificationRepository( void ) const
{
    return m_specificationRepository;
}

void SpecificationLoader::setSpecificationRepository(
    const SpecificationRepository::Ptr& specificationRepository )
{
    m_specificationRepository = specificationRepository;
}

Specification::Ptr SpecificationLoader::loadSpecification(
    const AST::IdentifierPath::Ptr& identifierPath )
{
    libpass::PassLogger log( &LibraryLoaderPass::id, m_logStream );

    const auto& identifierPathName = identifierPath->path();
    log.debug( "loadSpecification: loading '" + identifierPathName + "'" );

    LoadingStrategy::Ptr loadingStrategy = m_loadingStrategy;

    const auto& moduleName = identifierPath->identifiers()->front()->name();
    if( specificationRepository()->project()->configuration() )
    {
        const auto& configuration = specificationRepository()->project()->configuration();
        log.debug( ">>> WE HAVE A PROJECT CONFIG =D @ '" + configuration->fileName() + "' <<<" );

        const auto& dependencyLocation = configuration->import( moduleName );
        if( dependencyLocation )
        {
            log.debug(
                ">>> found module '" + moduleName + "' @ '" + dependencyLocation->path() +
                "' <<<" );
            assert( dependencyLocation->scheme() == "file" );
            loadingStrategy = std::make_shared< PathLoadingStrategy >(
                specificationRepository()->specificationBasePath() + dependencyLocation->path() );
        }
    }

    if( moduleName == "CASM" )
    {
        const auto& casmSpecificationPath =
            libstdhl::String::replaceAll( identifierPathName, Namespace::delimiter(), "/" ) +
            Specification::fileExtension();

        static const std::unordered_map< std::string, const std::string& >
            filenameToSpecifiction = {
                { "CASM", CASM_casm },
            };

        const auto& casmSpecification = filenameToSpecifiction.find( identifierPathName );
        if( casmSpecification == filenameToSpecifiction.end() )
        {
            throw SpecificationLoadingError( "Unable to import '" + identifierPathName + "'" );
        }

        const auto temporaryPath = libstdhl::File::Path::temporary();
        const auto temporaryName = temporaryPath + "/" + casmSpecificationPath;
        auto temporaryFile = libstdhl::File::open( temporaryName, std::fstream::out );
        temporaryFile << casmSpecification->second;
        temporaryFile.close();
        loadingStrategy = std::make_shared< FileLoadingStrategy >( temporaryPath );
    }

    const auto& uri = loadingStrategy->toURI( identifierPath );
    const auto& uriString = uri.toString();
    log.debug( "loadSpecification: module '" + moduleName + "' with spec @ '" + uriString + "'" );

    const auto& cachedSpecification = specificationRepository()->get( uriString );
    if( cachedSpecification )
    {
        log.debug( "using '" + identifierPathName + "' from repository" );
        return *cachedSpecification;
    }

    libpass::LoadFilePass::Input::Ptr source = nullptr;
    try
    {
        source = loadingStrategy->loadSource( uri );
    }
    catch( const NoSuchSpecificationError& e )
    {
        throw NoSuchSpecificationError(
            "Unable to import '" + identifierPathName + "', " + e.what() );
    }
    assert( source != nullptr );

    libpass::PassResult defaultPassResult;
    defaultPassResult.setInput< libpass::LoadFilePass >( *source );
    defaultPassResult.setInput< libcasm_fe::LibraryLoaderPass >( specificationRepository() );

    libpass::PassManager passManager;
    passManager.setStream( m_logStream );
    passManager.setDefaultResult( defaultPassResult );
    passManager.setDefaultPass< TemplatingPass >();

    if( not passManager.run() )
    {
#ifndef NDEBUG
        auto flush = [&passManager, &uriString]() {
            libstdhl::Log::ApplicationFormatter formatter( uriString );
            libstdhl::Log::OutputStreamSink sink( std::cerr, formatter );
            passManager.stream().flush( sink );
        };
        flush();
#endif
        throw SpecificationLoadingError( "Unable to import '" + identifierPathName + "'" );
    }

    const auto& passResult = passManager.result();
    assert( passResult.hasOutput< CstToAstPass >() );
    const auto passData = passResult.output< CstToAstPass >();
    const auto specification = passData->specification();

    assert( specificationRepository()->get( uriString ) == specification );
    return specification;
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
