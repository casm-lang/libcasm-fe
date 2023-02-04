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

#include "SourceToCstPass.h"

#include <libcasm-fe/Logger>
#include <libcasm-fe/Namespace>
#include <libcasm-fe/Specification>
#include <libcasm-fe/TypeInfo>
#include <libcasm-fe/analyze/ProjectResolverPass>

#include <libpass/PassRegistry>

#include <libstdhl/std/rfc3986>

#include "../Lexer.h"
#include "../various/GrammarParser.tab.h"
#include "../various/GrammarToken.h"

using namespace libcasm_fe;

char SourceToCstPass::id = 0;

static libpass::PassRegistration< SourceToCstPass > PASS(
    "Source Parsing Pass", "parse the source code and generates an CST", "src2cst", 0 );

//
//
// SourceToCstPass
//

void SourceToCstPass::usage( libpass::PassUsage& pu )
{
    pu.require< ProjectResolverPass >();
}

u1 SourceToCstPass::run( libpass::PassResult& pr )
{
    libcasm_fe::Logger log( &id, stream() );

    const auto data = pr.output< ProjectResolverPass >();
    const auto project = data->project();
    const auto specificationFile = project->specification();
    const auto specificationFileName = specificationFile->filename();
    auto& specificationFileStream = specificationFile->stream();

    Lexer lexer( log, specificationFileStream, std::cout );
    lexer.setFileName( specificationFileName );

    const auto specification = std::make_shared< Specification >();
    specification->setLocation( std::make_shared< libstdhl::Standard::RFC3986::URI >(
        "file", "/", specificationFileName, "", "" ) );

    Parser parser( log, lexer, *specification );
    parser.set_debug_level( m_debug );

    if( ( parser.parse() != 0 ) or not specification or ( log.errors() > 0 ) )
    {
        log.error( "could not parse '" + specification->location()->toString() + "'" );
        return false;
    }

    if( specification->name() == "CASM" )
    {
        log.debug( "module 'CASM' found" );
    }
    else
    {
        const auto& sourceLocation = specification->cst()->header()->sourceLocation();
        const auto casmImport = CST::make< ImportDefinition >(
            sourceLocation,
            Token::unresolved(),
            IdentifierPath::fromIdentifier( CST::make< Identifier >( sourceLocation, "CASM" ) ) );
        specification->cst()->definitions()->add( casmImport );

        const auto casmUsing = CST::make< UsingPathDefinition >(
            sourceLocation,
            Token::unresolved(),
            IdentifierPath::fromIdentifier( CST::make< Identifier >( sourceLocation, "CASM" ) ),
            std::make_shared< Token >( Grammar::Token::DOUBLECOLON ),
            std::make_shared< Token >( Grammar::Token::ASTERIX ) );
        specification->cst()->definitions()->add( casmUsing );
    }

    pr.setOutput< SourceToCstPass >( specification );
    return true;
}

void SourceToCstPass::setDebug( u1 enable )
{
    m_debug = enable;
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
