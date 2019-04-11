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

#include "LibraryLoader.h"

#include <libcasm-fe/analyze/ConsistencyCheckPass>
#include <libcasm-fe/import/ImportError>
#include <libcasm-fe/transform/SourceToAstPass>

#include <libpass/PassManager>
#include <libpass/analyze/LoadFilePass>

#include <libstdhl/String>

using namespace libcasm_fe;

LibraryLoader::LibraryLoader(
    libstdhl::Log::Stream& logStream, const std::shared_ptr< LoadingStrategy >& loadingStrategy )
: SpecificationLoader()
, m_logStream( logStream )
, m_repository()
, m_loadingStrategy( loadingStrategy )
{
}

Specification::Ptr LibraryLoader::loadSpecification( const std::string& identifierPath )
{
    libstdhl::Logger log( m_logStream );
    log.setCategory( std::make_shared< libstdhl::Log::Category >( identifierPath, "import" ) );

    log.debug( ">>> LibraryLoader::loadSpecification with '" + identifierPath + "'" );

    const auto cachedSpecification = m_repository.get( identifierPath );
    if( cachedSpecification )
    {
        log.debug( "Using '" + identifierPath + "' from repository" );
        return *cachedSpecification;
    }

    const auto source = m_loadingStrategy->loadSource( identifierPath );
    const auto fileName = source->filename();

    libpass::PassResult defaultPassResult;
    defaultPassResult.setInput< libpass::LoadFilePass >( *source );

    libpass::PassManager passManager;
    passManager.setStream( m_logStream );
    passManager.setDefaultResult( defaultPassResult );
    passManager.setDefaultPass< ConsistencyCheckPass >();

    auto flush = [&passManager, &fileName]() {
        libstdhl::Log::ApplicationFormatter formatter( fileName );
        libstdhl::Log::OutputStreamSink sink( std::cerr, formatter );
        passManager.stream().flush( sink );
    };

    if( not passManager.run( flush ) )
    {
        throw SpecificationLoadingError( "Couldn't load '" + identifierPath + "'" );
    }

    const auto& passResult = passManager.result();
    assert( passResult.hasOutput< SourceToAstPass >() );
    const auto passData = passResult.output< SourceToAstPass >();
    const auto specification = passData->specification();
    m_repository.store( identifierPath, specification );
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
