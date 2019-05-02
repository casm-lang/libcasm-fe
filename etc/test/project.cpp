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

#define TEST_PASS( PASS, FILENAME, STATUS, CONFIG )                                               \
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
        libpass::PassResult pr;                                                                   \
        pr.setInput< libpass::LoadFilePass >( FILENAME );                                         \
        pm.setDefaultResult( pr );                                                                \
                                                                                                  \
        EXPECT_EQ( pm.run( flush ), STATUS );                                                     \
                                                                                                  \
        pm.result().output< libpass::LoadFilePass >()->close();                                   \
    }

static const auto specificationFoo = R"***(
CASM

init test

rule test = program( self ) := undef

import src::Bar

)***";

static const auto specificationSrcBar = R"***(
CASM

import src::Qux

//import external::Baz

)***";

static const auto specificationSrcQux = R"***(
CASM

import Foo

import external::Baz

)***";

static const auto specificationLibBaz = R"***(
CASM

rule asdf = skip

)***";

static const auto projectConfiguration = R"***(
CASM:
  execute: libcasm_fe_project.import_from_configuration/Foo.casm
  imports:
    - external: file:///./libcasm_fe_project.import_from_configuration/lib

)***";

TEST( libcasm_fe_project, import_from_configuration )
{
    // GIVEN
    const auto projectConfig = TEST_NAME + ".yml";
    const auto projectPath = TEST_NAME + "/";
    const auto projectPathLib = projectPath + "lib/";
    const auto projectPathSrc = projectPath + "src/";
    const auto projectFileFoo = projectPath + "Foo.casm";
    const auto projectFileBar = projectPathSrc + "Bar.casm";
    const auto projectFileQux = projectPathSrc + "Qux.casm";
    const auto projectFileBaz = projectPathLib + "Baz.casm";
    TEST_PATH_CREATE( projectPath );
    TEST_PATH_CREATE( projectPathSrc );
    TEST_PATH_CREATE( projectPathLib );
    TEST_FILE_CREATE( projectFileFoo, specificationFoo );
    TEST_FILE_CREATE( projectFileBar, specificationSrcBar );
    TEST_FILE_CREATE( projectFileQux, specificationSrcQux );
    TEST_FILE_CREATE( projectFileBaz, specificationLibBaz );
    TEST_FILE_CREATE( projectConfig, projectConfiguration );

    // WHEN & THEN
    TEST_PASS( ConsistencyCheckPass, projectConfig, true, );

    // CLEANUP
    TEST_FILE_REMOVE( projectConfig );
    TEST_FILE_REMOVE( projectFileBaz );
    TEST_FILE_REMOVE( projectFileQux );
    TEST_FILE_REMOVE( projectFileBar );
    TEST_FILE_REMOVE( projectFileFoo );
    TEST_PATH_REMOVE( projectPathLib );
    TEST_PATH_REMOVE( projectPathSrc );
    TEST_PATH_REMOVE( projectPath );
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
