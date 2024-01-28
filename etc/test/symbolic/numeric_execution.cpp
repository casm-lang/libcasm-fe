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

#include "../main.h"

#include <libcasm-fe/libcasm-fe>

#include <libpass/PassManager>
#include <libpass/PassResult>
#include <libpass/analyze/LoadFilePass>

using namespace libcasm_fe;
using namespace LST;

#define SOURCE( PASS, CONTENT, STATUS, CONFIG )                                                   \
    {                                                                                             \
        libpass::PassManager pm;                                                                  \
        pm.setDefaultPass< PASS >();                                                              \
        pm.set< libcasm_fe::PASS >( [ & ]( libcasm_fe::PASS& pass ) { CONFIG } );                 \
                                                                                                  \
        libstdhl::Logger log( pm.stream() );                                                      \
        log.setSource( libstdhl::Memory::make< libstdhl::Log::Source >( TEST_NAME, TEST_NAME ) ); \
                                                                                                  \
        auto flush = [ &pm ]() {                                                                  \
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

static const auto source = R"***(
CASM

[symbolic] function a : -> Integer = { 3 }
function b : -> Integer = { 2 }

init test

rule test = {
    assert( a = 3 )
    assert( b = 2 )
}
)***";

SOURCE_TEST( symbolic_execution, NumericExecutionPass, source, true, , );

SOURCE_TEST( symbolic_execution, SymbolicExecutionPass, source, true, , );

static const auto source_assert = R"***(
CASM

init test

function a : -> Integer
[symbolic] function b : -> Integer = { 1 }

rule test = {
    assert( a = undef )
    a := b + 10
    program( self ) := @print_t
}

rule print_t = {
    assert( a != undef )
    program( self ) := undef
}
)***";

SOURCE_TEST( assert_numeric, NumericExecutionPass, source_assert, true, , );

SOURCE_TEST( assert_symbolic, SymbolicExecutionPass, source_assert, true, , );

//
//  Local variables:
//  mode: c++
//  indent-tabs-mode: nil
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//
