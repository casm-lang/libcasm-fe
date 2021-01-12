//
//  Copyright (C) 2014-2021 CASM Organization <https://casm-lang.org>
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
using namespace Ast;
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
tff(11,type,'%3':$int).
tff(0,hypothesis,'@a':($int*$int)>$o).
tff(1,hypothesis,'@b':($int*$int)>$o).
tff(3,hypothesis,'@a'(1,'%0')).
tff(5,hypothesis,'%1'<=>('%0'=0)).
tff(6,hypothesis,'%1'=>('@b'(2,1))).
tff(7,hypothesis,~'%1'=>('@b'(2,2))).
tff(9,hypothesis,'@a'(1,'%2')).
tff(10,hypothesis,'@a'(0,'%2')).
tff(12,hypothesis,'@b'(2,'%3')).
tff(13,hypothesis,'@b'(0,'%3')).
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
tff(11,type,'%4':$int).
tff(13,type,'%5':$o).
tff(17,type,'%6':$int).
tff(20,type,'%7':$int).
tff(23,type,'%8':$int).
tff(0,hypothesis,'@a':($int*$int)>$o).
tff(1,hypothesis,'@b':($int*$int)>$o).
tff(2,hypothesis,'@c':($int*$int)>$o).
tff(4,hypothesis,'@a'(1,'%0')).
tff(6,hypothesis,'%1'<=>('%0'=0)).
tff(8,hypothesis,'%1'=>('@c'(1,'%2'))).
tff(10,hypothesis,'%1'=>('%3'<=>('%2'!=0))).
tff(12,hypothesis,'%1'=>('%3'=>('@a'(1,'%4')))).
tff(14,hypothesis,'%1'=>('%3'=>('%5'<=>('%4'=0)))).
tff(15,hypothesis,'%1'=>('%3'=>('%5'=>('@b'(2,1))))).
tff(16,hypothesis,~'%1'=>('@b'(2,2))).
tff(18,hypothesis,'@a'(1,'%6')).
tff(19,hypothesis,'@a'(0,'%6')).
tff(21,hypothesis,'@b'(2,'%7')).
tff(22,hypothesis,'@b'(0,'%7')).
tff(24,hypothesis,'@c'(1,'%8')).
tff(25,hypothesis,'@c'(0,'%8')).
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
tff(16,type,'%3':$o).
tff(19,type,'%4':$int).
tff(21,type,'%5':$o).
tff(24,type,'%6':$int).
tff(26,type,'%7':$o).
tff(29,type,'%8':$int).
tff(31,type,'%9':$o).
tff(34,type,'%10':$int).
tff(36,type,'%11':$int).
tff(40,type,'%12':$int).
tff(42,type,'%13':$int).
tff(46,type,'%14':$int).
tff(48,type,'%15':$int).
tff(52,type,'%16':$int).
tff(54,type,'%17':$int).
tff(58,type,'%18':$int).
tff(60,type,'%19':$int).
tff(64,type,'%20':$o).
tff(66,type,'%21':$o).
tff(68,type,'%22':$o).
tff(71,type,'%23':$o).
tff(73,type,'%24':$o).
tff(75,type,'%25':$o).
tff(78,type,'%26':$o).
tff(80,type,'%27':$o).
tff(82,type,'%28':$o).
tff(85,type,'%29':$o).
tff(87,type,'%30':$o).
tff(89,type,'%31':$o).
tff(92,type,'%32':$int).
tff(95,type,'%33':$int).
tff(98,type,'%34':$int).
tff(101,type,'%35':$int).
tff(104,type,'%36':$int).
tff(107,type,'%37':$o).
tff(110,type,'%38':$o).
tff(113,type,'%39':$o).
tff(116,type,'%40':$o).
tff(119,type,'%41':$o).
tff(122,type,'%42':$o).
tff(125,type,'%43':$int).
tff(128,type,'%44':$int).
tff(131,type,'%45':$int).
tff(134,type,'%46':$int).
tff(137,type,'%47':$int).
tff(140,type,'%48':$int).
tff(143,type,'%49':$int).
tff(146,type,'%50':$int).
tff(149,type,'%51':$int).
tff(152,type,'%52':$int).
tff(37,hypothesis,'#add#i':($int*$int*$int)>$o).
tff(55,hypothesis,'#div#i':($int*$int*$int)>$o).
tff(61,hypothesis,'#mod#i':($int*$int*$int)>$o).
tff(49,hypothesis,'#mul#i':($int*$int*$int)>$o).
tff(43,hypothesis,'#sub#i':($int*$int*$int)>$o).
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
tff(15,hypothesis,'@b'(1,'%2')).
tff(17,hypothesis,'%3'<=>($greater('%2',0))).
tff(18,hypothesis,'%3'=>('@z'(2,1,2))).
tff(20,hypothesis,'@c'(1,'%4')).
tff(22,hypothesis,'%5'<=>($greatereq('%4',1))).
tff(23,hypothesis,'%5'=>('@z'(2,2,3))).
tff(25,hypothesis,'@d'(1,'%6')).
tff(27,hypothesis,'%7'<=>($less('%6',0))).
tff(28,hypothesis,'%7'=>('@z'(2,3,4))).
tff(30,hypothesis,'@e'(1,'%8')).
tff(32,hypothesis,'%9'<=>($lesseq('%8',1))).
tff(33,hypothesis,'%9'=>('@z'(2,4,5))).
tff(35,hypothesis,'@a'(1,'%10')).
tff(38,hypothesis,'#add#i'(1,'%10','%11')).
tff(39,hypothesis,'@z'(2,5,'%11')).
tff(41,hypothesis,'@a'(1,'%12')).
tff(44,hypothesis,'#sub#i'(1,'%12','%13')).
tff(45,hypothesis,'@z'(2,6,'%13')).
tff(47,hypothesis,'@a'(1,'%14')).
tff(50,hypothesis,'#mul#i'(1,'%14','%15')).
tff(51,hypothesis,'@z'(2,7,'%15')).
tff(53,hypothesis,'@a'(1,'%16')).
tff(56,hypothesis,'#div#i'(1,'%16','%17')).
tff(57,hypothesis,'@z'(2,8,'%17')).
tff(59,hypothesis,'@a'(1,'%18')).
tff(62,hypothesis,'#mod#i'(1,'%18','%19')).
tff(63,hypothesis,'@z'(2,9,'%19')).
tff(65,hypothesis,'@f'(1,'%20')).
tff(67,hypothesis,'@g'(1,'%21')).
tff(69,hypothesis,'%22'<=>('%20'&'%21')).
tff(70,hypothesis,'@y'(2,0,'%22')).
tff(72,hypothesis,'@f'(1,'%23')).
tff(74,hypothesis,'@g'(1,'%24')).
tff(76,hypothesis,'%25'<=>('%23'|'%24')).
tff(77,hypothesis,'@y'(2,1,'%25')).
tff(79,hypothesis,'@f'(1,'%26')).
tff(81,hypothesis,'@g'(1,'%27')).
tff(83,hypothesis,'%28'<=>('%26'<~>'%27')).
tff(84,hypothesis,'@y'(2,2,'%28')).
tff(86,hypothesis,'@f'(1,'%29')).
tff(88,hypothesis,'@g'(1,'%30')).
tff(90,hypothesis,'%31'<=>('%29'=>'%30')).
tff(91,hypothesis,'@y'(2,3,'%31')).
tff(93,hypothesis,'@a'(1,'%32')).
tff(94,hypothesis,'@a'(0,'%32')).
tff(96,hypothesis,'@b'(1,'%33')).
tff(97,hypothesis,'@b'(0,'%33')).
tff(99,hypothesis,'@c'(1,'%34')).
tff(100,hypothesis,'@c'(0,'%34')).
tff(102,hypothesis,'@d'(1,'%35')).
tff(103,hypothesis,'@d'(0,'%35')).
tff(105,hypothesis,'@e'(1,'%36')).
tff(106,hypothesis,'@e'(0,'%36')).
tff(108,hypothesis,'@f'(1,'%37')).
tff(109,hypothesis,'@f'(0,'%37')).
tff(111,hypothesis,'@g'(1,'%38')).
tff(112,hypothesis,'@g'(0,'%38')).
tff(114,hypothesis,'@y'(2,3,'%39')).
tff(115,hypothesis,'@y'(0,3,'%39')).
tff(117,hypothesis,'@y'(2,2,'%40')).
tff(118,hypothesis,'@y'(0,2,'%40')).
tff(120,hypothesis,'@y'(2,1,'%41')).
tff(121,hypothesis,'@y'(0,1,'%41')).
tff(123,hypothesis,'@y'(2,0,'%42')).
tff(124,hypothesis,'@y'(0,0,'%42')).
tff(126,hypothesis,'@z'(2,3,'%43')).
tff(127,hypothesis,'@z'(0,3,'%43')).
tff(129,hypothesis,'@z'(2,5,'%44')).
tff(130,hypothesis,'@z'(0,5,'%44')).
tff(132,hypothesis,'@z'(2,2,'%45')).
tff(133,hypothesis,'@z'(0,2,'%45')).
tff(135,hypothesis,'@z'(2,4,'%46')).
tff(136,hypothesis,'@z'(0,4,'%46')).
tff(138,hypothesis,'@z'(2,1,'%47')).
tff(139,hypothesis,'@z'(0,1,'%47')).
tff(141,hypothesis,'@z'(2,0,'%48')).
tff(142,hypothesis,'@z'(0,0,'%48')).
tff(144,hypothesis,'@z'(2,7,'%49')).
tff(145,hypothesis,'@z'(0,7,'%49')).
tff(147,hypothesis,'@z'(2,9,'%50')).
tff(148,hypothesis,'@z'(0,9,'%50')).
tff(150,hypothesis,'@z'(2,6,'%51')).
tff(151,hypothesis,'@z'(0,6,'%51')).
tff(153,hypothesis,'@z'(2,8,'%52')).
tff(154,hypothesis,'@z'(0,8,'%52')).
)***";

SOURCE_TEST(
    execute_instructions,
    SymbolicExecutionPass,
    source_symbolic_instructions,
    true,
    ,
    ,
    tptp_instructions );  // TODO: FIXME:
