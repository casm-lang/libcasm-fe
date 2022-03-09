//
//  Copyright (C) 2014-2021 CASM Organization <https://casm-lang.org>
//  All rights reserved.
//
//  Developed by: Philipp Paulweber
//                Emmanuel Pescosta
//                Jakob Moosbrugger
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
tff(0,hypothesis,'@c':($int*$int)>$o).
tff(1,hypothesis,'@a':($int*$int)>$o).
tff(2,hypothesis,'@b':($int*$int)>$o).
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

// TODO: @moosbruggerj, @ppaulweber: revert to use tptp_add in let test after LST bug fixed and
// function declaration order is stable
static const auto tptp_add_let = R"***(
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

SOURCE_TEST( execute_add, SymbolicExecutionPass, source_add, true, , , tptp_add );

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

// TODO: @moosbruggerj, @ppaulweber: change expected to tptp_add, see above
SOURCE_TEST( execute_let, SymbolicExecutionPass, source_let, true, , , tptp_add_let );

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
tff(13,type,'%5':$o).
tff(16,type,'%6':$int).
tff(18,type,'%7':$int).
tff(20,type,'%8':$int).
tff(23,type,'%9':$int).
tff(25,type,'%10':$int).
tff(28,type,'%11':$int).
tff(31,type,'%12':$int).
tff(0,hypothesis,'@a':($int*$int)>$o).
tff(1,hypothesis,'@c':($int*$int)>$o).
tff(2,hypothesis,'@b':($int*$int)>$o).
tff(4,hypothesis,'@a'(1,'%0')).
tff(6,hypothesis,'%1'<=>('%0'=0)).
tff(8,hypothesis,'%1'=>('@c'(1,'%2'))).
tff(10,hypothesis,'%1'=>('%3'<=>('%2'=0))).
tff(12,hypothesis,'%1'=>('%4'<=>~'%3')).
tff(14,hypothesis,'%1'=>('%4'=>('%5'<=>('%0'=0)))).
tff(15,hypothesis,'%1'=>('%4'=>('%5'=>('@b'(2,1))))).
tff(17,hypothesis,'%1'=>('%4'=>('@b'(1,'%6')))).
tff(19,hypothesis,'%1'=>('%4'=>(('%5'=>(1='%7'))&((~'%5')=>('%6'='%7'))))).
tff(21,hypothesis,'%1'=>(('%4'=>('%7'='%8'))&((~'%4')=>('%6'='%8')))).
tff(22,hypothesis,~'%1'=>('@b'(2,2))).
tff(24,hypothesis,('%1'=>('%8'='%9'))&((~'%1')=>(2='%9'))).
tff(26,hypothesis,'@a'(1,'%10')).
tff(27,hypothesis,'@a'(0,'%10')).
tff(29,hypothesis,'@b'(2,'%11')).
tff(30,hypothesis,'@b'(0,'%11')).
tff(32,hypothesis,'@c'(1,'%12')).
tff(33,hypothesis,'@c'(0,'%12')).
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
tff(31,type,'%10':$o).
tff(33,type,'%11':$o).
tff(36,type,'%12':$int).
tff(38,type,'%13':$int).
tff(40,type,'%14':$int).
tff(42,type,'%15':$o).
tff(45,type,'%16':$int).
tff(47,type,'%17':$int).
tff(49,type,'%18':$int).
tff(51,type,'%19':$o).
tff(53,type,'%20':$o).
tff(55,type,'%21':$o).
tff(58,type,'%22':$int).
tff(60,type,'%23':$int).
tff(62,type,'%24':$int).
tff(66,type,'%25':$int).
tff(70,type,'%26':$int).
tff(74,type,'%27':$int).
tff(78,type,'%28':$int).
tff(82,type,'%29':$o).
tff(84,type,'%30':$o).
tff(86,type,'%31':$o).
tff(88,type,'%32':$o).
tff(90,type,'%33':$o).
tff(92,type,'%34':$o).
tff(95,type,'%35':$o).
tff(98,type,'%36':$o).
tff(100,type,'%37':$o).
tff(102,type,'%38':$o).
tff(104,type,'%39':$o).
tff(106,type,'%40':$o).
tff(108,type,'%41':$o).
tff(110,type,'%42':$o).
tff(112,type,'%43':$o).
tff(114,type,'%44':$o).
tff(116,type,'%45':$o).
tff(118,type,'%46':$o).
tff(121,type,'%47':$o).
tff(123,type,'%48':$o).
tff(126,type,'%49':$int).
tff(129,type,'%50':$int).
tff(132,type,'%51':$int).
tff(135,type,'%52':$int).
tff(138,type,'%53':$int).
tff(141,type,'%54':$o).
tff(144,type,'%55':$o).
tff(147,type,'%56':$o).
tff(150,type,'%57':$o).
tff(153,type,'%58':$o).
tff(156,type,'%59':$o).
tff(159,type,'%60':$int).
tff(162,type,'%61':$int).
tff(165,type,'%62':$int).
tff(168,type,'%63':$int).
tff(171,type,'%64':$int).
tff(174,type,'%65':$int).
tff(177,type,'%66':$int).
tff(180,type,'%67':$int).
tff(183,type,'%68':$int).
tff(186,type,'%69':$int).
tff(63,hypothesis,'#add#i':($int*$int*$int)>$o).
tff(75,hypothesis,'#div#i':($int*$int*$int)>$o).
tff(79,hypothesis,'#mod#i':($int*$int*$int)>$o).
tff(71,hypothesis,'#mul#i':($int*$int*$int)>$o).
tff(67,hypothesis,'#sub#i':($int*$int*$int)>$o).
tff(0,hypothesis,'@a':($int*$int)>$o).
tff(1,hypothesis,'@z':($int*$int*$int)>$o).
tff(2,hypothesis,'@b':($int*$int)>$o).
tff(3,hypothesis,'@c':($int*$int)>$o).
tff(4,hypothesis,'@d':($int*$int)>$o).
tff(5,hypothesis,'@e':($int*$int)>$o).
tff(6,hypothesis,'@y':($int*$int*$o)>$o).
tff(7,hypothesis,'@f':($int*$o)>$o).
tff(8,hypothesis,'@g':($int*$o)>$o).
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
tff(30,hypothesis,'%9'<=>($greater('%8',1))).
tff(32,hypothesis,'%10'<=>('%8'=1)).
tff(34,hypothesis,'%11'<=>('%9'|'%10')).
tff(35,hypothesis,'%11'=>('@z'(2,2,3))).
tff(37,hypothesis,'@z'(1,2,'%12')).
tff(39,hypothesis,('%11'=>(3='%13'))&((~'%11')=>('%12'='%13'))).
tff(41,hypothesis,'@d'(1,'%14')).
tff(43,hypothesis,'%15'<=>($less('%14',0))).
tff(44,hypothesis,'%15'=>('@z'(2,3,4))).
tff(46,hypothesis,'@z'(1,3,'%16')).
tff(48,hypothesis,('%15'=>(4='%17'))&((~'%15')=>('%16'='%17'))).
tff(50,hypothesis,'@e'(1,'%18')).
tff(52,hypothesis,'%19'<=>($less('%18',1))).
tff(54,hypothesis,'%20'<=>('%18'=1)).
tff(56,hypothesis,'%21'<=>('%19'|'%20')).
tff(57,hypothesis,'%21'=>('@z'(2,4,5))).
tff(59,hypothesis,'@z'(1,4,'%22')).
tff(61,hypothesis,('%21'=>(5='%23'))&((~'%21')=>('%22'='%23'))).
tff(64,hypothesis,'#add#i'(1,'%0','%24')).
tff(65,hypothesis,'@z'(2,5,'%24')).
tff(68,hypothesis,'#sub#i'(1,'%0','%25')).
tff(69,hypothesis,'@z'(2,6,'%25')).
tff(72,hypothesis,'#mul#i'(1,'%0','%26')).
tff(73,hypothesis,'@z'(2,7,'%26')).
tff(76,hypothesis,'#div#i'(1,'%0','%27')).
tff(77,hypothesis,'@z'(2,8,'%27')).
tff(80,hypothesis,'#mod#i'(1,'%0','%28')).
tff(81,hypothesis,'@z'(2,9,'%28')).
tff(83,hypothesis,'@f'(1,'%29')).
tff(85,hypothesis,'@g'(1,'%30')).
tff(87,hypothesis,'%31'<=>~'%29').
tff(89,hypothesis,'%32'<=>~'%30').
tff(91,hypothesis,'%33'<=>('%31'|'%32')).
tff(93,hypothesis,'%34'<=>~'%33').
tff(94,hypothesis,'@y'(2,0,'%34')).
tff(96,hypothesis,'%35'<=>('%29'|'%30')).
tff(97,hypothesis,'@y'(2,1,'%35')).
tff(99,hypothesis,'%36'<=>~'%30').
tff(101,hypothesis,'%37'<=>~'%29').
tff(103,hypothesis,'%38'<=>~'%36').
tff(105,hypothesis,'%39'<=>('%37'|'%38')).
tff(107,hypothesis,'%40'<=>~'%39').
tff(109,hypothesis,'%41'<=>~'%29').
tff(111,hypothesis,'%42'<=>~'%41').
tff(113,hypothesis,'%43'<=>~'%30').
tff(115,hypothesis,'%44'<=>('%42'|'%43')).
tff(117,hypothesis,'%45'<=>~'%44').
tff(119,hypothesis,'%46'<=>('%40'|'%45')).
tff(120,hypothesis,'@y'(2,2,'%46')).
tff(122,hypothesis,'%47'<=>~'%29').
tff(124,hypothesis,'%48'<=>('%47'|'%30')).
tff(125,hypothesis,'@y'(2,3,'%48')).
tff(127,hypothesis,'@a'(1,'%49')).
tff(128,hypothesis,'@a'(0,'%49')).
tff(130,hypothesis,'@b'(1,'%50')).
tff(131,hypothesis,'@b'(0,'%50')).
tff(133,hypothesis,'@c'(1,'%51')).
tff(134,hypothesis,'@c'(0,'%51')).
tff(136,hypothesis,'@d'(1,'%52')).
tff(137,hypothesis,'@d'(0,'%52')).
tff(139,hypothesis,'@e'(1,'%53')).
tff(140,hypothesis,'@e'(0,'%53')).
tff(142,hypothesis,'@f'(1,'%54')).
tff(143,hypothesis,'@f'(0,'%54')).
tff(145,hypothesis,'@g'(1,'%55')).
tff(146,hypothesis,'@g'(0,'%55')).
tff(148,hypothesis,'@y'(2,0,'%56')).
tff(149,hypothesis,'@y'(0,0,'%56')).
tff(151,hypothesis,'@y'(2,1,'%57')).
tff(152,hypothesis,'@y'(0,1,'%57')).
tff(154,hypothesis,'@y'(2,2,'%58')).
tff(155,hypothesis,'@y'(0,2,'%58')).
tff(157,hypothesis,'@y'(2,3,'%59')).
tff(158,hypothesis,'@y'(0,3,'%59')).
tff(160,hypothesis,'@z'(2,0,'%60')).
tff(161,hypothesis,'@z'(0,0,'%60')).
tff(163,hypothesis,'@z'(2,1,'%61')).
tff(164,hypothesis,'@z'(0,1,'%61')).
tff(166,hypothesis,'@z'(2,4,'%62')).
tff(167,hypothesis,'@z'(0,4,'%62')).
tff(169,hypothesis,'@z'(2,5,'%63')).
tff(170,hypothesis,'@z'(0,5,'%63')).
tff(172,hypothesis,'@z'(2,2,'%64')).
tff(173,hypothesis,'@z'(0,2,'%64')).
tff(175,hypothesis,'@z'(2,3,'%65')).
tff(176,hypothesis,'@z'(0,3,'%65')).
tff(178,hypothesis,'@z'(2,8,'%66')).
tff(179,hypothesis,'@z'(0,8,'%66')).
tff(181,hypothesis,'@z'(2,9,'%67')).
tff(182,hypothesis,'@z'(0,9,'%67')).
tff(184,hypothesis,'@z'(2,6,'%68')).
tff(185,hypothesis,'@z'(0,6,'%68')).
tff(187,hypothesis,'@z'(2,7,'%69')).
tff(188,hypothesis,'@z'(0,7,'%69')).
)***";

SOURCE_TEST(
    execute_instructions,
    SymbolicExecutionPass,
    source_symbolic_instructions,
    true,
    ,
    ,
    tptp_instructions );  // TODO: FIXME:
