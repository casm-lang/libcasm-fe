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

#include "../main.h"

#include <libcasm-fe/import/SpecificationMergerPass>
#include <libcasm-fe/libcasm-fe>

#include <libpass/PassManager>
#include <libpass/PassResult>
#include <libpass/analyze/LoadFilePass>

using namespace libcasm_fe;
using namespace LST;

bool isFunctionSymbolic( const Specification::Ptr& specification, std::string function )
{
    for( const auto& definition : *specification->lst()->definitions() )
    {
        if( definition->id() == Node::ID::FUNCTION_DEFINITION )
        {
            const auto& functionDefn = std::static_pointer_cast< FunctionDefinition >( definition );
            if( functionDefn->identifier()->name() == function )
            {
                return functionDefn->symbolic();
            }
        }
    }
    EXPECT_TRUE( false ) << "Function '" << function << "' not found.";
    return false;
}

#define SOURCE( PASS, CONTENT, STATUS, CONFIG, SYM_FUNCS... )                                     \
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
        auto data = pm.result().output< SpecificationMergerPass >();                              \
        auto specification = data->specification();                                               \
        std::vector< std::string > symFuncs = { SYM_FUNCS };                                      \
        for( const auto& func : symFuncs )                                                        \
        {                                                                                         \
            bool sym = true;                                                                      \
            std::string funcName = func;                                                          \
            if( func.length() > 0 && func[ 0 ] == '~' )                                           \
            {                                                                                     \
                sym = false;                                                                      \
                funcName = func.substr( 1, func.length() - 1 );                                   \
            }                                                                                     \
            EXPECT_EQ( isFunctionSymbolic( specification, funcName ), sym )                       \
                << "Expected function '" << funcName << "' to be "                                \
                << ( sym ? "symbolic" : "numeric" ) << ".";                                       \
        }                                                                                         \
                                                                                                  \
        pm.result().output< libpass::LoadFilePass >()->close();                                   \
        libstdhl::File::remove( filename );                                                       \
        EXPECT_EQ( libstdhl::File::exists( filename ), false );                                   \
    }

#define SOURCE_TEST( SCOPE, PASS, CONTENT, STATUS, DESCRIPTION, CONFIG, SYM_FUNCS... ) \
    TEST( libcasm_fe_passes, SCOPE##_##PASS##DESCRIPTION )                             \
    {                                                                                  \
        SOURCE( PASS, CONTENT, STATUS, CONFIG, SYM_FUNCS );                            \
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

static const auto source_update = R"***(
CASM

init test

[symbolic] function a : -> Integer
function b : -> Integer
function c : -> Integer
function d : -> Integer

rule test =
{
    b := a
    c := 7
    d := undef
    program( self ) := undef
}

)***";

SOURCE_TEST( symbolic_update, SymbolicConsistencyPass, source_update, true, , , "b", "~c", "~d" );

static const auto source_condition = R"***(
CASM

init test

[symbolic] function a : -> Integer
function b : -> Integer
function c : -> Integer
function d : -> Integer
function e : -> Integer
function f : -> Integer
function g : -> Integer
function h : -> Integer

rule test =
{
    if a = 0 then
        b := 1
    else
        b := 2

    case a of {
        1: e := 1
        2: e := 2
        _: e := 0
    }

    g := if a = 0 then 1 else 2

    if c = 0 then
        d := 4
    else
        d := 5

    case c of {
        1: f := 1
        2: f := 2
        _: f := 0
    }

    h := if c = 0 then 1 else 2
    program( self ) := undef
}

)***";

SOURCE_TEST(
    symbolic_from_condition,
    SymbolicConsistencyPass,
    source_condition,
    true,
    ,
    ,
    "b",
    "~c",
    "~d",
    "e",
    "~f",
    "g",
    "~h" );

static const auto source_propagate = R"***(
CASM

init test

[symbolic] function a : -> Integer
function b : -> Integer
function c : -> Integer
function d : -> Integer
function e : -> Integer

rule test =
{
    if a = 0 then
        b := 1
    else
        b := 2

    c := b
    d := 17
    e := d
    program( self ) := undef
}

)***";

SOURCE_TEST(
    propagate_symbolic, SymbolicConsistencyPass, source_propagate, true, , , "b", "c", "~d", "~e" );

static const auto source_local = R"***(
CASM

init test

[symbolic] function a : -> Integer
function b : -> Integer
function c : -> Integer
function d : -> Integer

rule test =
{
    local e : -> Integer in {|
        e := a
        b := e
    |}

    local e : -> Integer in {|
        e := c
        d := e
    |}
    program( self ) := undef
}

)***";

SOURCE_TEST( symbolic_local, SymbolicConsistencyPass, source_local, true, , , "b", "~c", "~d" );

static const auto source_called = R"***(
CASM

init test

[symbolic] function a : -> Integer
function b : Integer -> Integer
function c : Integer -> Integer
function d : Integer -> Integer

rule test =
{
    b(1) := b(a)
    c(a) := 3
    d(3) := 5

    program( self ) := undef
}

)***";

SOURCE_TEST( called_symbolic, SymbolicConsistencyPass, source_called, true, , , "b", "c", "~d" );

static const auto source_let = R"***(
CASM

init test

[symbolic] function a : -> Integer
function b : -> Integer
function c : -> Integer
function d : -> Integer

rule test =
{
    let x = a in
        b := x

    let x = c in
        d := x

    program( self ) := undef
}

)***";

SOURCE_TEST( symbolic_let, SymbolicConsistencyPass, source_let, true, , , "b", "~c", "~d" );

static const auto source_initializers = R"***(
CASM

init test

[symbolic] function a : -> Integer
function b : Integer -> Integer = { (a) -> 1 }
function c : Integer -> Integer = { (1) -> 4, (2) -> a }
function d : -> Integer = { a }
function e : -> Integer = { 0 }
function f : Integer -> Integer = { (2) -> 3, (e) -> 4, (4) -> e }

rule test =
{
    program( self ) := undef
}

)***";

SOURCE_TEST(
    symbolic_initializers,
    SymbolicConsistencyPass,
    source_initializers,
    true,
    ,
    ,
    "b",
    "c",
    "d",
    "~e",
    "~f" );

static const auto source_direct_call = R"***(
CASM

init test

[symbolic] function a : -> Integer
function b : Integer -> Integer
function c : -> Integer
function d : -> Integer
function e : -> Integer
function f : Integer -> Integer

derived identity (i: Integer) -> Integer = i

rule test =
{
	b(1) := b(a)
	c := add(a, b(1))
	d := identity(a)
	callable(a)
	f(1) := f(2)
    f(2) := add(f(1), 2)

    program( self ) := undef
}

rule callable(p1: Integer) = {
	e := p1
}

)***";

SOURCE_TEST(
    symbolic_direct_calls,
    SymbolicConsistencyPass,
    source_direct_call,
    true,
    ,
    ,
    "b",
    "c",
    "d",
    "e",
    "~f" );

// TODO: self recursion with return value
// TODO: alternating recursion with return value
static const auto source_infinite_recursion = R"***(
CASM

init test

[symbolic] function a : -> Integer
function b : -> Integer
function c : -> Integer
function d : -> Integer
function e : -> Integer

rule test =
{
    callable1(a)
    callable3(1)

    program( self ) := undef
}

rule callable1(p1: Integer) = {
	b := p1
    callable2(b)
}

rule callable2(p1: Integer) = {
	c := p1
    callable1(c)
}

rule callable3(p1: Integer) = {
	d := p1
    callable4(d)
}

rule callable4(p1: Integer) = {
	e := p1
    callable3(e)
}
)***";

SOURCE_TEST(
    symbolic_infinite_recursion,
    SymbolicConsistencyPass,
    source_infinite_recursion,
    true,
    ,
    ,
    "b",
    "c",
    "~d",
    "~e" );

static const auto source_iterate = R"***(
CASM

init test

[symbolic] function a : -> Integer
function b : -> Integer
function c : -> Integer
function d : -> Integer
function e : -> Integer
function f : -> Integer


rule test =
{
	iterate {
        if a < 10 then {
            b := b + 2
            a := a + 1
        }
    }

    while a < 10 do {
        e := e + 1
    }

	iterate {
        if c < 10 then {
            d := d + 2
            c := c + 1
        }
    }

    while c < 10 do {
        f := f + 1
    }
    program( self ) := undef
}
)***";

SOURCE_TEST(
    symbolic_iterate,
    SymbolicConsistencyPass,
    source_iterate,
    true,
    ,
    ,
    "b",
    "~c",
    "~d",
    "e",
    "~f" );

static const auto source_choose = R"***(
CASM

init test

function a : -> Integer
function b : -> Integer
function c : -> Integer
function d : -> Integer
function e : -> Integer
function f : -> Integer


rule test =
{
	a := choose x in [0..10] do x + 1
    choose x in [0..10] do {
        c := x
        d := 2
    }

	b := choose x in [0..10] do 1
    program( self ) := undef
}
)***";

SOURCE_TEST(
    symbolic_choose, SymbolicConsistencyPass, source_choose, true, , , "a", "~b", "c", "~d" );

static const auto source_type_cast = R"***(
CASM

init test

[symbolic] function a : -> Integer
function b : -> String
function c : -> Integer
function d : -> String


rule test =
{
    b := a as String
    d := c as String
    program( self ) := undef
}
)***";

SOURCE_TEST(
    symbolic_type_cast, SymbolicConsistencyPass, source_type_cast, true, , , "b", "~c", "~d" );

static const auto source_expressions = R"***(
CASM

init test

[symbolic] function a : -> Integer
function b : -> Integer
function c : -> Integer
function d : -> Integer
[symbolic] function e : -> Boolean
function f : -> Boolean
function g : -> Boolean


rule test =
{
    b := a + 1
    f := not e

    c := 1 + 1
    d := c * 3
    g := not true

    program( self ) := undef
}
)***";

SOURCE_TEST(
    symbolic_expressions,
    SymbolicConsistencyPass,
    source_expressions,
    true,
    ,
    ,
    "b",
    "~c",
    "~d",
    "f",
    "~g" );

static const auto source_collections = R"***(
CASM

init test

[symbolic] function a : -> Integer
function b : -> (Integer,Integer)
function c : -> List< Integer >
//function d : -> [Integer..Integer]
function e : -> (Integer, Integer)
function f : -> List< Integer >
function g : -> Integer'[0..10]
function h : -> Integer
function i : -> Integer
function j : -> Integer

rule test =
{
    b := (a, 1)
    c := [a, a, 1, 2, 3]
    //d := [0..a]
	let x = [0..a] in
        h := |x|
    j := b.1

    e := (0, 1)
    f := [4, 5, 1, 2, 3]
    //f := []
    g := 5
	let x = [0..10] in
        i := |x|
    i := e.1

    program( self ) := undef
}

)***";

SOURCE_TEST(
    symbolic_collections,
    SymbolicConsistencyPass,
    source_collections,
    true,
    ,
    ,
    "b",
    "c",
    //"d",
    "~e",
    "~f",
    "~g",
    "h",
    "~i",
    "j" );

static const auto source_methods = R"***(
CASM

init test

[symbolic] function a : -> Integer
function b : Integer -> Integer
function c : Integer -> Integer
function d : Integer -> Integer
function e : -> Integer
function f : Integer -> Integer
function g : Integer -> Integer
function h : -> Boolean

rule test =
{
    b(1) := a.add(b(1))
    //only builtin methods are supported for now
    //b(2) := a.c()
	//d(2) := d(1).muladd(a, a)

	//f(1) := 1.g()
    f(2) := f(1).add(1)
    h := b(1).isSymbolic
    program( self ) := undef
}

rule muladd(mul1: Integer, mul2: Integer, add1: Integer) = {
	e := mul1 * mul2 + add1
}

)***";

SOURCE_TEST(
    method_call,
    SymbolicConsistencyPass,
    source_methods,
    true,
    ,
    ,
    "b",
    //"c",
    //"d",
    //"e",
    "~f",
    "~g",
    "~h" );

static const auto source_quantifier = R"***(
CASM

init test

[symbolic] function a : -> Integer
function b : -> Boolean
function c : -> Boolean
function d : -> Boolean
function e : -> Boolean
function f : -> Boolean
function g : -> Boolean
function h : Integer -> Integer
function i : -> Integer
function j : -> Integer
function k : -> Integer
function l : -> Integer

rule test =
{
    b := forall x in [0..a] holds x > 0
    c := forall x in [0..a] holds true
    d := exists x in [0..a] with x = 10
    e := exists x in [0..a] with true

    f := exists x in [0..9] with x < 10
    g := forall x in [0..9] holds x > 0

    forall x in [0..a] do {
        h(x) := x
        i := 1
    }
    forall x in [0..a] with x < 8 do {
        j := 1
    }
    forall x in [0..a] with k < 8 do {
        l := 1
    }
    program( self ) := undef
}
)***";

SOURCE_TEST(
    symbolic_quantifier,
    SymbolicConsistencyPass,
    source_quantifier,
    true,
    ,
    ,
    "b",
    "~c",
    "d",
    "~e",
    "~f",
    "~g",
    "h",
    "~i",
    "j",
    "~k",
    "~l" );

static const auto source_update_in_arg = R"***(
CASM

init test

[symbolic] function a : -> Integer
[symbolic] function b : -> Integer
function c : Integer -> Integer
rule test =
{
    callable(b, c(a))
    program( self ) := undef
}

rule callable(p1: Integer, p2: Integer) = skip

)***";

SOURCE_TEST(
    symbolic_update_in_arg, SymbolicConsistencyPass, source_update_in_arg, true, , , "b", "c" );

static const auto source_cannot_have_symbolic_function = R"***(
CASM

init test

[symbolic] function a : -> Integer
function b : Integer -> RuleRef< -> Void >
rule test =
{
	b(0) := @callable
    program( self ) := b(a)
}

rule callable = skip

)***";

SOURCE_TEST(
    symbolic_program_update,
    SymbolicConsistencyPass,
    source_cannot_have_symbolic_function,
    false,
    , );

static const auto source_derived_call = R"***(
CASM

init test

[symbolic] function a : -> Integer
function b : -> Integer
function c : -> Integer

derived identity (i: Integer) -> Integer = i

rule test =
{
	b := identity(a)
	c := identity(1)

    program( self ) := undef
}
)***";

SOURCE_TEST(
    symbolic_derived_calls, SymbolicConsistencyPass, source_derived_call, true, , , "b", "~c" );
//
//  Local variables:
//  mode: c++
//  indent-tabs-mode: nil
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//
