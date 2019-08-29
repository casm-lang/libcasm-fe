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

#include "SpecificationMergerPass.h"

#include <libcasm-fe/Logger>
#include <libcasm-fe/analyze/TypeCheckPass>
#include <libcasm-fe/import/LibraryLoaderPass>
#include <libcasm-fe/transform/SourceToAstPass>

#include <libpass/PassRegistry>
#include <libpass/PassResult>
#include <libpass/PassUsage>

using namespace libcasm_fe;
using namespace Ast;

char SpecificationMergerPass::id = 0;

static libpass::PassRegistration< SpecificationMergerPass > PASS(
    "ASTSpecificationMergerPass", "merges the imported CASM specifications", "ast-spec-merge", 0 );

void SpecificationMergerPass::usage( libpass::PassUsage& pu )
{
    pu.require< LibraryLoaderPass >();
    pu.scheduleAfter< TypeCheckPass >();
}

u1 SpecificationMergerPass::run( libpass::PassResult& pr )
{
    libcasm_fe::Logger log( &id, stream() );

    const auto data = pr.output< LibraryLoaderPass >();
    const auto specificationRepository = data->specificationRepository();

    const auto definitions = std::make_shared< Definitions >();
    for( const auto& specification : specificationRepository->specifications() )
    {
        for( const auto& definition : *specification->definitions() )
        {
            definitions->add( definition );
        }
    }

    const auto errors = log.errors();
    if( errors > 0 )
    {
        log.debug( "found %lu error(s) during library loading", errors );
        return false;
    }

    const auto parsedSpecification = pr.output< SourceToAstPass >()->specification();
    const auto mergedSpecification = std::make_shared< Specification >();

    mergedSpecification->setAsmType( parsedSpecification->asmType() );
    mergedSpecification->setLocation( parsedSpecification->location() );
    mergedSpecification->setHeader( parsedSpecification->header() );
    mergedSpecification->setSpans( parsedSpecification->spans() );
    mergedSpecification->setSymboltable( parsedSpecification->symboltable() );

    mergedSpecification->setDefinitions( definitions );

    pr.setOutput< SpecificationMergerPass >( mergedSpecification );
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
