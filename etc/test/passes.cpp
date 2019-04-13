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

#define SOURCE_TEST( SCOPE, PASS, CONTENT, STATUS, DESCRIPTION, CONFIG )                       \
    TEST( libcasm_fe, SCOPE##_##PASS##DESCRIPTION )                                            \
    {                                                                                          \
        const std::string filename = TEST_NAME + ".casm";                                      \
        auto file = libstdhl::File::open( filename, std::fstream::out );                       \
        file << CONTENT;                                                                       \
        file.close();                                                                          \
        EXPECT_EQ( libstdhl::File::exists( filename ), true );                                 \
                                                                                               \
        libpass::PassManager pm;                                                               \
        pm.setDefaultPass< PASS >();                                                           \
        pm.set< libcasm_fe::PASS >( [&]( libcasm_fe::PASS& pass ) { CONFIG } );                \
                                                                                               \
        libpass::PassResult pr;                                                                \
        const auto input = libstdhl::Memory::make< libpass::LoadFilePass::Input >( filename ); \
        pr.setInputData< libpass::LoadFilePass >( input );                                     \
        pm.setDefaultResult( pr );                                                             \
                                                                                               \
        EXPECT_EQ( pm.run(), STATUS );                                                         \
                                                                                               \
        pm.result().output< libpass::LoadFilePass >()->close();                                \
        libstdhl::File::remove( filename );                                                    \
        EXPECT_EQ( libstdhl::File::exists( filename ), false );                                \
    }

SOURCE_TEST( transform, SourceToAstPass, "_test_", false, _unable_to_parse, );
SOURCE_TEST( transform, SourceToAstPass, source, true, , { pass.setDebug( false ); } );

SOURCE_TEST( analyze, ConsistencyCheckPass, source, true, , );

SOURCE_TEST( transform, AstDumpSourcePass, source, true, , );
SOURCE_TEST( transform, AstDumpDotPass, source, true, , );

// SOURCE_TEST( execute, NumericExecutionPass, source, true, , ); // TODO: FIXME: https://github.com/casm-lang/casm/issues/93
//
// static const auto source_with_no_init = R"***(
// CASM
//
// rule test = skip
//
// )***";
//
// SOURCE_TEST( execute, NumericExecutionPass, source_with_no_init, true, _noInitDefinition, );

//
//  Local variables:
//  mode: c++
//  indent-tabs-mode: nil
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//
