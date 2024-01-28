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
#include <libtptp/transform/DumpSourcePass>
#include "testhelper.h"

using namespace libcasm_fe;
using namespace LST;

#define SOURCE( PASS, CONTENT, STATUS, CONFIG, RESULT )                                           \
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
        pr.setOutput< libtptp::SourceToAstPass >(                                                 \
            pm.result().output< SymbolicExecutionPass >()->specification() );                     \
        libtptp::DumpSourcePass dumpPass;                                                         \
        dumpPass.run( pr );                                                                       \
        std::cout << pr.output< libtptp::DumpSourcePass >()->stream().str();                      \
        EXPECT_EQ(                                                                                \
            TestHelper::compareTPTPFiles(                                                         \
                RESULT, pr.output< libtptp::DumpSourcePass >()->stream().str() ),                 \
            true );                                                                               \
                                                                                                  \
        pm.result().output< libpass::LoadFilePass >()->close();                                   \
        libstdhl::File::remove( filename );                                                       \
        EXPECT_EQ( libstdhl::File::exists( filename ), false );                                   \
    }

#define SOURCE_TEST( SCOPE, PASS, CONTENT, STATUS, DESCRIPTION, CONFIG, RESULT ) \
    TEST( libcasm_fe_passes, SCOPE##_##PASS##DESCRIPTION )                       \
    {                                                                            \
        SOURCE( PASS, CONTENT, STATUS, CONFIG, RESULT );                         \
    }

static const auto source_branch = R"***(
CASM

[symbolic] function a : -> Integer = { 1 }
[symbolic] function b : -> Integer = { 2 }
[symbolic] function c : -> Integer = { 3 }
[symbolic] function d : -> Integer = { 4 }
[symbolic] function e : -> Integer = { 5 }
[symbolic] function f : -> Integer = { 6 }

init test
rule test = {
  if a = 0 then
    skip
  else
    c := b

  if a = 1 then
    d := a
  else
    skip

  if a = 2 then
    e := a
  else
    e := b
  program( self ) := @test2
}

rule test2 = {
  f := if a = 3 then e else c
  program(self) := undef
}
)***";

static const auto tptp_branch = R"***(
% specification: 
tff(6,type,'%0':$int).
tff(8,type,'%1':$o).
tff(10,type,'%2':$int).
tff(13,type,'%3':$int).
tff(15,type,'%4':$int).
tff(17,type,'%5':$o).
tff(20,type,'%6':$int).
tff(22,type,'%7':$int).
tff(24,type,'%8':$o).
tff(28,type,'%9':$int).
tff(30,type,'%10':$o).
tff(32,type,'%11':$int).
tff(35,type,'%12':$int).
tff(38,type,'%13':$int).
tff(41,type,'%14':$int).
tff(44,type,'%15':$int).
tff(47,type,'%16':$int).
tff(50,type,'%17':$int).
tff(0,hypothesis,'@a':($int*$int)>$o).
tff(1,hypothesis,'@b':($int*$int)>$o).
tff(2,hypothesis,'@c':($int*$int)>$o).
tff(3,hypothesis,'@d':($int*$int)>$o).
tff(4,hypothesis,'@e':($int*$int)>$o).
tff(5,hypothesis,'@f':($int*$int)>$o).
tff(7,hypothesis,'@a'(1,'%0')).
tff(9,hypothesis,'%1'<=>('%0'=0)).
tff(11,hypothesis,~'%1'=>('@b'(1,'%2'))).
tff(12,hypothesis,~'%1'=>('@c'(2,'%2'))).
tff(14,hypothesis,'@c'(1,'%3')).
tff(16,hypothesis,('%1'=>('%3'='%4'))&((~'%1')=>('%2'='%4'))).
tff(18,hypothesis,'%5'<=>('%0'=1)).
tff(19,hypothesis,'%5'=>('@d'(2,'%0'))).
tff(21,hypothesis,'@d'(1,'%6')).
tff(23,hypothesis,('%5'=>('%0'='%7'))&((~'%5')=>('%6'='%7'))).
tff(25,hypothesis,'%8'<=>('%0'=2)).
tff(26,hypothesis,'%8'=>('@e'(2,'%0'))).
tff(27,hypothesis,~'%8'=>('@e'(2,'%2'))).
tff(29,hypothesis,('%8'=>('%0'='%9'))&((~'%8')=>('%2'='%9'))).
tff(31,hypothesis,'%10'<=>('%0'=3)).
tff(33,hypothesis,('%10'=>('%9'='%11'))&((~'%10')=>('%4'='%11'))).
tff(34,hypothesis,'@f'(3,'%11')).
tff(36,hypothesis,'@a'(1,'%12')).
tff(37,hypothesis,'@a'(0,'%12')).
tff(39,hypothesis,'@b'(1,'%13')).
tff(40,hypothesis,'@b'(0,'%13')).
tff(42,hypothesis,'@c'(2,'%14')).
tff(43,hypothesis,'@c'(0,'%14')).
tff(45,hypothesis,'@d'(2,'%15')).
tff(46,hypothesis,'@d'(0,'%15')).
tff(48,hypothesis,'@e'(2,'%16')).
tff(49,hypothesis,'@e'(0,'%16')).
tff(51,hypothesis,'@f'(3,'%17')).
tff(52,hypothesis,'@f'(0,'%17')).
)***";

SOURCE_TEST( symbolic_branch, SymbolicExecutionPass, source_branch, true, , , tptp_branch );

//
//  Local variables:
//  mode: c++
//  indent-tabs-mode: nil
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//
