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

using namespace libcasm_fe;
using namespace LST;
static const auto source_add = R"***(
CASM

init test

[symbolic] function a : -> Integer
[symbolic] function b : -> Integer
[symbolic] function c : -> Integer

rule test =
{
	c := a + b
	program( self ) := undef
}

)***";

static const auto tptp_add = R"***(
% specification: 
tff(3,type,'%0':$int). 
tff(5,type,'%1':$int).
tff(7,type,'%2':$int).
tff(11,type,'%3':$int).
tff(14,type,'%4':$int).
tff(17,type,'%5':$int).
tff(8,hypothesis,'#add#i':($int*$int*$int)>$o).
tff(0,hypothesis,'@a':($int*$int)>$o).
tff(1,hypothesis,'@b':($int*$int)>$o).
tff(2,hypothesis,'@c':($int*$int)>$o).
tff(4,hypothesis,'@a'(1,'%0')).
tff(6,hypothesis,'@b'(1,'%1')).
tff(9,hypothesis,'#add#i'('%0','%1','%2')).
tff(10,hypothesis,'@c'(2,'%2')).
tff(12,hypothesis,'@a'(1,'%3')).
tff(13,hypothesis,'@a'(0,'%3')).
tff(15,hypothesis,'@b'(1,'%4')).
tff(16,hypothesis,'@b'(0,'%4')).
tff(18,hypothesis,'@c'(2,'%5')).
tff(19,hypothesis,'@c'(0,'%5')).
)***";

SOURCE_TEST( execute_add, SymbolicExecutionPass, source_add, true, , , tptp_add );  // TODO: FIXME:

static const auto source_let = R"***(
CASM

init test

[symbolic] function a : -> Integer
[symbolic] function b : -> Integer
[symbolic] function c : -> Integer

rule test =
{
	let d = a + b in
		c := d
	program( self ) := undef
}

)***";

SOURCE_TEST( execute_let, SymbolicExecutionPass, source_let, true, , , tptp_add );  // TODO: FIXME:

static const auto source_call_rule = R"***(
CASM

init test

[symbolic] function a : -> Integer
[symbolic] function b : -> Integer
[symbolic] function c : -> Integer

rule test =
{
	assign( a + b )
	program( self ) := undef
}

rule assign( d: Integer ) =
{
	c := d
}

)***";

SOURCE_TEST(
    execute_call, SymbolicExecutionPass, source_call_rule, true, , , tptp_add );  // TODO: FIXME:

static const auto source_conditional_rule = R"***(
CASM

init test

[symbolic] function a : -> Integer
[symbolic] function b : -> Integer

rule test =
{
    if a = 0 then
        b := 1
    else
        b := 2

    program( self ) := undef
}

)***";

static const auto tptp_conditional = R"***(
% specification: 
tff(2,type,'%0':$int).
tff(4,type,'%1':$o).
tff(8,type,'%2':$int).
tff(10,type,'%3':$int).
tff(13,type,'%4':$int).
tff(0,hypothesis,'@a':($int*$int)>$o).
tff(1,hypothesis,'@b':($int*$int)>$o).
tff(3,hypothesis,'@a'(1,'%0')).
tff(5,hypothesis,'%1'<=>('%0'=0)).
tff(6,hypothesis,'%1'=>('@b'(2,1))).
tff(7,hypothesis,~'%1'=>('@b'(2,2))).
tff(9,hypothesis,('%1'=>(1='%2'))&((~'%1')=>(2='%2'))).
tff(11,hypothesis,'@a'(1,'%3')).
tff(12,hypothesis,'@a'(0,'%3')).
tff(14,hypothesis,'@b'(2,'%4')).
tff(15,hypothesis,'@b'(0,'%4')).
)***";

SOURCE_TEST(
    execute_conditional,
    SymbolicExecutionPass,
    source_conditional_rule,
    true,
    ,
    ,
    tptp_conditional );  // TODO: FIXME:

static const auto source_nested_conditional_rule = R"***(
CASM

init test

[symbolic] function a : -> Integer
[symbolic] function b : -> Integer
[symbolic] function c : -> Integer

rule test =
{
    if a = 0 then {
        if c != 0 then
            if a = 0 then
                b := 1
    }
    else
        b := 2

    program( self ) := undef
}

)***";

static const auto tptp_nested_conditional = R"***(
% specification: 
tff(3,type,'%0':$int).
tff(5,type,'%1':$o).
tff(7,type,'%2':$int).
tff(9,type,'%3':$o).
tff(11,type,'%4':$o).
tff(14,type,'%5':$int).
tff(16,type,'%6':$int).
tff(18,type,'%7':$int).
tff(21,type,'%8':$int).
tff(23,type,'%9':$int).
tff(26,type,'%10':$int).
tff(29,type,'%11':$int).
tff(0,hypothesis,'@a':($int*$int)>$o).
tff(1,hypothesis,'@b':($int*$int)>$o).
tff(2,hypothesis,'@c':($int*$int)>$o).
tff(4,hypothesis,'@a'(1,'%0')).
tff(6,hypothesis,'%1'<=>('%0'=0)).
tff(8,hypothesis,'%1'=>('@c'(1,'%2'))).
tff(10,hypothesis,'%1'=>('%3'<=>('%2'!=0))).
tff(12,hypothesis,'%1'=>('%3'=>('%4'<=>('%0'=0)))).
tff(13,hypothesis,'%1'=>('%3'=>('%4'=>('@b'(2,1))))).
tff(15,hypothesis,'%1'=>('%3'=>('@b'(1,'%5')))).
tff(17,hypothesis,'%1'=>('%3'=>(('%4'=>(1='%6'))&((~'%4')=>('%5'='%6'))))).
tff(19,hypothesis,'%1'=>(('%3'=>('%6'='%7'))&((~'%3')=>('%5'='%7')))).
tff(20,hypothesis,~'%1'=>('@b'(2,2))).
tff(22,hypothesis,('%1'=>('%7'='%8'))&((~'%1')=>(2='%8'))).
tff(24,hypothesis,'@a'(1,'%9')).
tff(25,hypothesis,'@a'(0,'%9')).
tff(27,hypothesis,'@b'(2,'%10')).
tff(28,hypothesis,'@b'(0,'%10')).
tff(30,hypothesis,'@c'(1,'%11')).
tff(31,hypothesis,'@c'(0,'%11')).
)***";

SOURCE_TEST(
    execute_nested_conditional,
    SymbolicExecutionPass,
    source_nested_conditional_rule,
    true,
    ,
    ,
    tptp_nested_conditional );  // TODO: FIXME:

static const auto source_symbolic_instructions = R"***(
CASM

init test

[symbolic] function a : -> Integer
[symbolic] function b : -> Integer
[symbolic] function c : -> Integer
[symbolic] function d : -> Integer
[symbolic] function e : -> Integer
[symbolic] function f : -> Boolean
[symbolic] function g : -> Boolean

[symbolic] function y : Integer -> Boolean
[symbolic] function z : Integer -> Integer

rule test =
{
    if a = 0 then
        z(0) := 1
    if b > 0 then
        z(1) := 2
    if c >= 1 then
        z(2) := 3
    if d < 0 then
        z(3) := 4
    if e <= 1 then
        z(4) := 5

    z(5) := 1 + a
    z(6) := 1 - a
    z(7) := 1 * a
    z(8) := 1 / a
    z(9) := 1 % a
    y(0) := f and g
    y(1) := f or g
    y(2) := f xor g
    y(3) := f => g
    program( self ) := undef
}

)***";

static const auto tptp_instructions = R"***(
% specification: 
tff(9,type,'%0':$int).
tff(11,type,'%1':$o).
tff(14,type,'%2':$int).
tff(16,type,'%3':$int).
tff(18,type,'%4':$int).
tff(20,type,'%5':$o).
tff(23,type,'%6':$int).
tff(25,type,'%7':$int).
tff(27,type,'%8':$int).
tff(29,type,'%9':$o).
tff(32,type,'%10':$int).
tff(34,type,'%11':$int).
tff(36,type,'%12':$int).
tff(38,type,'%13':$o).
tff(41,type,'%14':$int).
tff(43,type,'%15':$int).
tff(45,type,'%16':$int).
tff(47,type,'%17':$o).
tff(50,type,'%18':$int).
tff(52,type,'%19':$int).
tff(54,type,'%20':$int).
tff(58,type,'%21':$int).
tff(62,type,'%22':$int).
tff(66,type,'%23':$int).
tff(70,type,'%24':$int).
tff(74,type,'%25':$o).
tff(76,type,'%26':$o).
tff(78,type,'%27':$o).
tff(81,type,'%28':$o).
tff(84,type,'%29':$o).
tff(87,type,'%30':$o).
tff(90,type,'%31':$int).
tff(93,type,'%32':$int).
tff(96,type,'%33':$int).
tff(99,type,'%34':$int).
tff(102,type,'%35':$int).
tff(105,type,'%36':$o).
tff(108,type,'%37':$o).
tff(111,type,'%38':$o).
tff(114,type,'%39':$o).
tff(117,type,'%40':$o).
tff(120,type,'%41':$o).
tff(123,type,'%42':$int).
tff(126,type,'%43':$int).
tff(129,type,'%44':$int).
tff(132,type,'%45':$int).
tff(135,type,'%46':$int).
tff(138,type,'%47':$int).
tff(141,type,'%48':$int).
tff(144,type,'%49':$int).
tff(147,type,'%50':$int).
tff(150,type,'%51':$int).
tff(55,hypothesis,'#add#i':($int*$int*$int)>$o).
tff(67,hypothesis,'#div#i':($int*$int*$int)>$o).
tff(71,hypothesis,'#mod#i':($int*$int*$int)>$o).
tff(63,hypothesis,'#mul#i':($int*$int*$int)>$o).
tff(59,hypothesis,'#sub#i':($int*$int*$int)>$o).
tff(0,hypothesis,'@a':($int*$int)>$o).
tff(1,hypothesis,'@b':($int*$int)>$o).
tff(2,hypothesis,'@c':($int*$int)>$o).
tff(3,hypothesis,'@d':($int*$int)>$o).
tff(4,hypothesis,'@e':($int*$int)>$o).
tff(5,hypothesis,'@f':($int*$o)>$o).
tff(6,hypothesis,'@g':($int*$o)>$o).
tff(7,hypothesis,'@y':($int*$int*$o)>$o).
tff(8,hypothesis,'@z':($int*$int*$int)>$o).
tff(10,hypothesis,'@a'(1,'%0')).
tff(12,hypothesis,'%1'<=>('%0'=0)).
tff(13,hypothesis,'%1'=>('@z'(2,0,1))).
tff(15,hypothesis,'@z'(1,0,'%2')).
tff(17,hypothesis,('%1'=>(1='%3'))&((~'%1')=>('%2'='%3'))).
tff(19,hypothesis,'@b'(1,'%4')).
tff(21,hypothesis,'%5'<=>($greater('%4',0))).
tff(22,hypothesis,'%5'=>('@z'(2,1,2))).
tff(24,hypothesis,'@z'(1,1,'%6')).
tff(26,hypothesis,('%5'=>(2='%7'))&((~'%5')=>('%6'='%7'))).
tff(28,hypothesis,'@c'(1,'%8')).
tff(30,hypothesis,'%9'<=>($greatereq('%8',1))).
tff(31,hypothesis,'%9'=>('@z'(2,2,3))).
tff(33,hypothesis,'@z'(1,2,'%10')).
tff(35,hypothesis,('%9'=>(3='%11'))&((~'%9')=>('%10'='%11'))).
tff(37,hypothesis,'@d'(1,'%12')).
tff(39,hypothesis,'%13'<=>($less('%12',0))).
tff(40,hypothesis,'%13'=>('@z'(2,3,4))).
tff(42,hypothesis,'@z'(1,3,'%14')).
tff(44,hypothesis,('%13'=>(4='%15'))&((~'%13')=>('%14'='%15'))).
tff(46,hypothesis,'@e'(1,'%16')).
tff(48,hypothesis,'%17'<=>($lesseq('%16',1))).
tff(49,hypothesis,'%17'=>('@z'(2,4,5))).
tff(51,hypothesis,'@z'(1,4,'%18')).
tff(53,hypothesis,('%17'=>(5='%19'))&((~'%17')=>('%18'='%19'))).
tff(56,hypothesis,'#add#i'(1,'%0','%20')).
tff(57,hypothesis,'@z'(2,5,'%20')).
tff(60,hypothesis,'#sub#i'(1,'%0','%21')).
tff(61,hypothesis,'@z'(2,6,'%21')).
tff(64,hypothesis,'#mul#i'(1,'%0','%22')).
tff(65,hypothesis,'@z'(2,7,'%22')).
tff(68,hypothesis,'#div#i'(1,'%0','%23')).
tff(69,hypothesis,'@z'(2,8,'%23')).
tff(72,hypothesis,'#mod#i'(1,'%0','%24')).
tff(73,hypothesis,'@z'(2,9,'%24')).
tff(75,hypothesis,'@f'(1,'%25')).
tff(77,hypothesis,'@g'(1,'%26')).
tff(79,hypothesis,'%27'<=>('%25'&'%26')).
tff(80,hypothesis,'@y'(2,0,'%27')).
tff(82,hypothesis,'%28'<=>('%25'|'%26')).
tff(83,hypothesis,'@y'(2,1,'%28')).
tff(85,hypothesis,'%29'<=>('%25'<~>'%26')).
tff(86,hypothesis,'@y'(2,2,'%29')).
tff(88,hypothesis,'%30'<=>('%25'=>'%26')).
tff(89,hypothesis,'@y'(2,3,'%30')).
tff(91,hypothesis,'@a'(1,'%31')).
tff(92,hypothesis,'@a'(0,'%31')).
tff(94,hypothesis,'@b'(1,'%32')).
tff(95,hypothesis,'@b'(0,'%32')).
tff(97,hypothesis,'@c'(1,'%33')).
tff(98,hypothesis,'@c'(0,'%33')).
tff(100,hypothesis,'@d'(1,'%34')).
tff(101,hypothesis,'@d'(0,'%34')).
tff(103,hypothesis,'@e'(1,'%35')).
tff(104,hypothesis,'@e'(0,'%35')).
tff(106,hypothesis,'@f'(1,'%36')).
tff(107,hypothesis,'@f'(0,'%36')).
tff(109,hypothesis,'@g'(1,'%37')).
tff(110,hypothesis,'@g'(0,'%37')).
tff(112,hypothesis,'@y'(2,3,'%38')).
tff(113,hypothesis,'@y'(0,3,'%38')).
tff(115,hypothesis,'@y'(2,2,'%39')).
tff(116,hypothesis,'@y'(0,2,'%39')).
tff(118,hypothesis,'@y'(2,1,'%40')).
tff(119,hypothesis,'@y'(0,1,'%40')).
tff(121,hypothesis,'@y'(2,0,'%41')).
tff(122,hypothesis,'@y'(0,0,'%41')).
tff(124,hypothesis,'@z'(2,3,'%42')).
tff(125,hypothesis,'@z'(0,3,'%42')).
tff(127,hypothesis,'@z'(2,5,'%43')).
tff(128,hypothesis,'@z'(0,5,'%43')).
tff(130,hypothesis,'@z'(2,2,'%44')).
tff(131,hypothesis,'@z'(0,2,'%44')).
tff(133,hypothesis,'@z'(2,4,'%45')).
tff(134,hypothesis,'@z'(0,4,'%45')).
tff(136,hypothesis,'@z'(2,1,'%46')).
tff(137,hypothesis,'@z'(0,1,'%46')).
tff(139,hypothesis,'@z'(2,0,'%47')).
tff(140,hypothesis,'@z'(0,0,'%47')).
tff(142,hypothesis,'@z'(2,7,'%48')).
tff(143,hypothesis,'@z'(0,7,'%48')).
tff(145,hypothesis,'@z'(2,9,'%49')).
tff(146,hypothesis,'@z'(0,9,'%49')).
tff(148,hypothesis,'@z'(2,6,'%50')).
tff(149,hypothesis,'@z'(0,6,'%50')).
tff(151,hypothesis,'@z'(2,8,'%51')).
tff(152,hypothesis,'@z'(0,8,'%51')).
)***";

SOURCE_TEST(
    execute_instructions,
    SymbolicExecutionPass,
    source_symbolic_instructions,
    true,
    ,
    ,
    tptp_instructions );  // TODO: FIXME:
