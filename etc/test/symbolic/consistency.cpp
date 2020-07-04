//
//  Copyright (C) 2014-2020 CASM Organization <https://casm-lang.org>
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

#include "../main.h"

#include <libcasm-fe/import/SpecificationMergerPass>
#include <libcasm-fe/libcasm-fe>

#include <libpass/PassManager>
#include <libpass/PassResult>
#include <libpass/analyze/LoadFilePass>

using namespace libcasm_fe;
using namespace Ast;

bool isFunctionSymbolic( const Specification::Ptr& specification, std::string function )
{
    for( const auto& definition : *specification->definitions() )
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

rule test =
{
    b := a
    c := 7
    program( self ) := undef
}

)***";

SOURCE_TEST( symbolic_update, SymbolicConsistencyPass, source_update, true, , , "b", "~c" );

static const auto source_condition = R"***(
CASM

init test

[symbolic] function a : -> Integer
function b : -> Integer
function c : -> Integer
function d : -> Integer

rule test =
{
    if a = 0 then
        b := 1
    else
        b := 2

    if c = 0 then
        d := 4
    else
        d := 5

    program( self ) := undef
}

)***";

SOURCE_TEST(
    symbolic_from_condition, SymbolicConsistencyPass, source_condition, true, , , "b", "~c", "~d" );

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

//
//  Local variables:
//  mode: c++
//  indent-tabs-mode: nil
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//
