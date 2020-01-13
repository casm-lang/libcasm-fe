//
//  Copyright (C) 2014-2021 CASM Organization <https://casm-lang.org>
//  All rights reserved.
//
//  Developed by: Philipp Paulweber
//                Emmanuel Pescosta
//                Jakob Moosbrugger
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

#include "LibraryLoaderPass.h"

#include <libcasm-fe/Logger>
#include <libcasm-fe/analyze/ProjectResolverPass>
#include <libcasm-fe/analyze/SymbolRegistrationPass>
#include <libcasm-fe/ast/Visitor>
#include <libcasm-fe/import/FileLoadingStrategy>
#include <libcasm-fe/import/ImportError>
#include <libcasm-fe/import/SpecificationLoader>
#include <libcasm-fe/transform/CstToAstPass>

#include <libpass/PassRegistry>
#include <libpass/PassResult>
#include <libpass/PassUsage>

using namespace libcasm_fe;
using namespace AST;

char LibraryLoaderPass::id = 0;

static libpass::PassRegistration< LibraryLoaderPass > PASS(
    "Library Loader Pass", "imports the defined CASM library (module)", "ast-lib-loader", 0 );

namespace libcasm_fe
{
    namespace AST
    {
        class LibraryLoaderVisitor final : public RecursiveVisitor
        {
          public:
            LibraryLoaderVisitor(
                libcasm_fe::Logger& log, Namespace& symboltable, SpecificationLoader& loader );

            void visit( ImportDefinition& node ) override;

          private:
            libcasm_fe::Logger& m_log;
            Namespace& m_symboltable;
            SpecificationLoader& m_loader;
        };
    }
}

LibraryLoaderVisitor::LibraryLoaderVisitor(
    libcasm_fe::Logger& log, Namespace& symboltable, SpecificationLoader& loader )
: m_log( log )
, m_symboltable( symboltable )
, m_loader( loader )
{
}

void LibraryLoaderVisitor::visit( ImportDefinition& node )
{
    RecursiveVisitor::visit( node );

    libcasm_fe::Specification::Ptr specification = nullptr;
    const auto& path = node.path();
    try
    {
        specification = m_loader.loadSpecification( path );
    }
    catch( const ImportError& e )
    {
        m_log.error( { path->sourceLocation() }, e.what(), Code::ImportError );
        return;
    }
    assert( specification );

    for( const auto& definition : *specification->ast()->definitions() )
    {
        if( definition->id() == Node::ID::INIT_DEFINITION )
        {
            const auto& initDefinition = definition->ptr< InitDefinition >();
            initDefinition->setExternal();
        }
    }

    const auto& identifierName = node.identifier()->name();
    try
    {
        m_symboltable.registerNamespace(
            identifierName, specification->symboltable(), Namespace::Visibility::External );
    }
    catch( const std::domain_error& e )
    {
        m_log.error( { node.sourceLocation() }, e.what() );
    }
}

void LibraryLoaderPass::usage( libpass::PassUsage& pu )
{
    pu.require< CstToAstPass >();
    pu.require< ProjectResolverPass >();
    pu.scheduleAfter< SymbolRegistrationPass >();
}

u1 LibraryLoaderPass::run( libpass::PassResult& pr )
{
    libcasm_fe::Logger log( &id, stream() );

    const auto data = pr.output< CstToAstPass >();
    const auto specification = data->specification();
    const auto symboltable = specification->symboltable();
    const auto specificationFileName = specification->location()->path();

    const auto projectResolverData = pr.output< ProjectResolverPass >();
    const auto project = projectResolverData->project();
    const auto configuration = project->configuration();

    auto specificationBasePath = specificationFileName;
    const auto lastSlashPos = specificationBasePath.find_last_of( '/' );
    if( lastSlashPos != std::string::npos )
    {
        specificationBasePath.erase( lastSlashPos );
    }
    else
    {
        specificationBasePath = ".";
    }

    SpecificationRepository::Ptr parentSpecificationRepository = nullptr;

    if( pr.hasInput< LibraryLoaderPass >() )
    {
        const auto data = pr.input< LibraryLoaderPass >();
        parentSpecificationRepository = data->specificationRepository();

        const auto parentSpecificationBasePath =
            parentSpecificationRepository->specificationBasePath();
        specificationBasePath = parentSpecificationBasePath;
    }

    const auto loadingStrategy = std::make_shared< FileLoadingStrategy >( specificationBasePath );

    SpecificationLoader loader( stream(), loadingStrategy );

    if( parentSpecificationRepository )
    {
        loader.setSpecificationRepository( parentSpecificationRepository );
    }
    else
    {
        loader.specificationRepository()->setSpecificationBasePath( specificationBasePath );
        loader.specificationRepository()->setProject( project );
    }

    assert( loader.specificationRepository() != nullptr );
    assert( loader.specificationRepository()->project() != nullptr );

    loader.specificationRepository()->store( specification->location()->toString(), specification );

    LibraryLoaderVisitor visitor( log, *symboltable, loader );
    specification->ast()->accept( visitor );

    const auto errors = log.errors();
    if( errors > 0 )
    {
        log.debug( "symbol table =\n" + specification->symboltable()->dump() );
        log.debug( "found %lu error(s) during library loading", errors );
        return false;
    }

    pr.setOutput< LibraryLoaderPass >( specification, loader.specificationRepository() );
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
