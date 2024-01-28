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

#include "main.h"
#include "pass.h"

using namespace libcasm_fe;
using namespace AST;

TEST( libcasm_fe_utf8, identifier_with_emoticons )
{
    // GIVEN
    static const auto file = TEST_NAME + ".casm";
    static const auto spec = R"***(
CASM

// rule test = 😆 

// rule 😆 = 😆😆

// rule 😆😆 = skip

/* asdf 😆😆 */ rule 😆 = skip

enumeration 😆😆😆 = { 😢, 😢😢, 😢😢😢, 😢suffix, prefix😢, 😢infix😢 }

function really😆function : 😆😆😆 -> Integer

rule test =
    println( "test string with UTF-8 😆 emoticon" ) // contains 😆 in the string

)***";

    // WHEN
    TEST_FILE_CREATE( file, spec );

    // THEN
    TEST_PASS( CstEmitPass, file, true, );

    // CLEANUP
    TEST_FILE_REMOVE( file );
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
