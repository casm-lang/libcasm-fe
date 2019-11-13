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

#include "main.h"

#include <libcasm-fe/libcasm-fe>

#include <libpass/PassManager>
#include <libpass/PassResult>
#include <libpass/analyze/LoadFilePass>

using namespace libcasm_fe;
using namespace Ast;

static const auto source = R"***(
CASM

init test_skip

rule test_skip = skip

rule test_update_program_self_undef = program( self ) := undef

)***";

#define SOURCE( PASS, CONTENT, STATUS, CONFIG )                                                   \
    {                                                                                             \
        libpass::PassManager pm;                                                                  \
        pm.setDefaultPass< PASS >();                                                              \
        pm.set< libcasm_fe::PASS >( [&]( libcasm_fe::PASS& pass ) { CONFIG } );                   \
                                                                                                  \
        libstdhl::Logger log( pm.stream() );                                                      \
        log.setSource( libstdhl::Memory::make< libstdhl::Log::Source >( TEST_NAME, TEST_NAME ) ); \
                                                                                                  \
        auto flush = [&pm]() {                                                                    \
            libstdhl::Log::ApplicationFormatter f( TEST_NAME );                                   \
            libstdhl::Log::OutputStreamSink c( std::cerr, f );                                    \
            pm.stream().flush( c );                                                               \
        };                                                                                        \
                                                                                                  \
        const std::string filename = TEST_NAME + ".casm";                                         \
        auto file = libstdhl::File::open( filename, std::fstream::out );                          \
        file << CONTENT;                                                                          \
        file.close();                                                                             \
                                                                                                  \
        libpass::PassResult pr;                                                                   \
        pr.setInput< libpass::LoadFilePass >( filename );                                         \
        pm.setDefaultResult( pr );                                                                \
                                                                                                  \
        EXPECT_EQ( pm.run( flush ), STATUS );                                                     \
                                                                                                  \
        pm.result().output< libpass::LoadFilePass >()->close();                                   \
        libstdhl::File::remove( filename );                                                       \
        EXPECT_EQ( libstdhl::File::exists( filename ), false );                                   \
    }

#define SOURCE_TEST( SCOPE, PASS, CONTENT, STATUS, DESCRIPTION, CONFIG ) \
    TEST( libcasm_fe_passes, SCOPE##_##PASS##DESCRIPTION )               \
    {                                                                    \
        SOURCE( PASS, CONTENT, STATUS, CONFIG );                         \
    }

#define SOURCE_TEST_WITH_LIBRARY( SCOPE, PASS, CONTENT, LIBRARY, STATUS, DESCRIPTION, CONFIG ) \
    TEST( libcasm_fe_passes, SCOPE##_##PASS##DESCRIPTION )                                     \
    {                                                                                          \
        const std::string filename = "lib.casm";                                               \
        auto file = libstdhl::File::open( filename, std::fstream::out );                       \
        file << LIBRARY;                                                                       \
        file.close();                                                                          \
                                                                                               \
        SOURCE( PASS, CONTENT, STATUS, CONFIG );                                               \
                                                                                               \
        libstdhl::File::remove( filename );                                                    \
        EXPECT_EQ( libstdhl::File::exists( filename ), false );                                \
    }

SOURCE_TEST( analyze, ConsistencyCheckPass, source, true, , );

SOURCE_TEST( transform, SourceToAstPass, source, true, , { pass.setDebug( false ); } );

SOURCE_TEST( transform, AstDumpSourcePass, source, true, , );
SOURCE_TEST( transform, AstDumpDotPass, source, true, , );

// SOURCE_TEST( execute, NumericExecutionPass, source, true, , ); // TODO: FIXME:
// https://github.com/casm-lang/casm/issues/93
//
// static const auto source_with_no_init = R"***(
// CASM
//
// rule test = skip
//
// )***";
//
// SOURCE_TEST( execute, NumericExecutionPass, source_with_no_init, true, _noInitDefinition, );

static const auto src = R"***(
CASM init test

import lib

import lib as bar

using lib::*

rule test =
{
    lib::foo
    bar::foo
    assert( lib::Color::Red = Color::Red )
}

)***";

static const auto lib = R"***(
CASM

[ export ] rule foo = skip

function qux : -> Integer

[ export ] enumeration Color = { Red, Blue, Green }

)***";

SOURCE_TEST_WITH_LIBRARY( analyze, ConsistencyCheckPass, src, lib, true, _import, );
// SOURCE_TEST_WITH_LIBRARY( execute, NumericExecutionPass, src, lib, true, _import, );

//
//  Local variables:
//  mode: c++
//  indent-tabs-mode: nil
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//
