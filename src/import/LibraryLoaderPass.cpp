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

#include "LibraryLoaderPass.h"

#include <libcasm-fe/Logger>
#include <libcasm-fe/analyze/SymbolRegistrationPass>
#include <libcasm-fe/ast/RecursiveVisitor>
#include <libcasm-fe/import/FileLoadingStrategy>
#include <libcasm-fe/import/ImportError>
#include <libcasm-fe/import/LibraryLoader>
#include <libcasm-fe/import/SpecificationLoader>
#include <libcasm-fe/transform/SourceToAstPass>

#include <libpass/PassRegistry>
#include <libpass/PassResult>
#include <libpass/PassUsage>

using namespace libcasm_fe;
using namespace Ast;

char LibraryLoaderPass::id = 0;

static libpass::PassRegistration< LibraryLoaderPass > PASS(
    "ASTLibraryLoaderPass", "imports the specified CASM libraries", "ast-lib-loader", 0 );

class LibraryLoaderVisitor final : public RecursiveVisitor
{
  public:
    LibraryLoaderVisitor(
        libcasm_fe::Logger& log,
        Namespace& symboltable,
        SpecificationLoader& loader,
        const std::string& specificationBasePath );

    void visit( ImportDefinition& node ) override;

  private:
    libcasm_fe::Logger& m_log;
    Namespace& m_symboltable;
    SpecificationLoader& m_loader;
    std::string m_specificationBasePath;
};

LibraryLoaderVisitor::LibraryLoaderVisitor(
    libcasm_fe::Logger& log,
    Namespace& symboltable,
    SpecificationLoader& loader,
    const std::string& specificationBasePath )
: m_log( log )
, m_symboltable( symboltable )
, m_loader( loader )
, m_specificationBasePath( specificationBasePath )
{
}

void LibraryLoaderVisitor::visit( ImportDefinition& node )
{
    RecursiveVisitor::visit( node );

    // file-based loading
    std::string libraryPath;
    switch( node.path()->type() )
    {
        case IdentifierPath::Type::ABSOLUTE:
        {
            libraryPath = node.path()->path();
            break;
        }
        case IdentifierPath::Type::RELATIVE:
        {
            // import library relative to the current specification
            libraryPath = m_specificationBasePath + node.path()->path();
            break;
        }
        default:
        {
            assert( !"path type cannot be handled" );
        }
    }

    Specification::Ptr specification;
    try
    {
        specification = m_loader.loadSpecification( libraryPath );
    }
    catch( const ImportError& e )
    {
        m_log.error(
            { node.path()->sourceLocation() },
            "Couldn't import library '" + libraryPath + "'",
            Code::ImportError );
        m_log.warning( { node.path()->sourceLocation() }, e.what() );
        return;
    }
    assert( specification );

    const auto identifier =
        node.identifier()->empty() ? node.path()->identifiers()->back() : node.identifier();
    try
    {
        m_symboltable.registerNamespace( identifier->name(), specification->symboltable() );
    }
    catch( const std::domain_error& e )
    {
        m_log.error( { identifier->sourceLocation() }, e.what() );
    }
}

void LibraryLoaderPass::usage( libpass::PassUsage& pu )
{
    pu.require< SourceToAstPass >();
    pu.scheduleAfter< SymbolRegistrationPass >();
}

u1 LibraryLoaderPass::run( libpass::PassResult& pr )
{
    libcasm_fe::Logger log( &id, stream() );

    const auto data = pr.output< SourceToAstPass >();
    const auto specification = data->specification();
    const auto symboltable = specification->symboltable();

    // determine the base path of the current specification, which will be used
    // to resolve relative import paths
    auto specificationBasePath = specification->name();
    const auto lastSlashPos = specificationBasePath.find_last_of( '/' );
    if( lastSlashPos != std::string::npos )
    {
        specificationBasePath.erase( lastSlashPos );
    }
    else
    {
        specificationBasePath = ".";
    }

    auto loaderStrategy = std::make_shared< FileLoadingStrategy >( specificationBasePath );
    const auto loader = std::make_shared< LibraryLoader >( stream(), loaderStrategy );

    if( pr.hasInput< LibraryLoaderPass >() )
    {
        const auto data = pr.input< LibraryLoaderPass >();
        const auto specificationRepository = data->specificationRepository();
        loader->setSpecificationRepository( specificationRepository );
    }

    std::string uri = "file://";
    uri += specification->name();
    loader->specificationRepository()->store( uri, specification );

    specification->setLoader( loader );

    assert( specification->loader() && "loader must be set" );

    LibraryLoaderVisitor visitor(
        log, *symboltable, *specification->loader(), specificationBasePath );
    specification->definitions()->accept( visitor );

    const auto errors = log.errors();
    if( errors > 0 )
    {
        log.debug( "found %lu error(s) during library loading", errors );
        return false;
    }

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
