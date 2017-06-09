%{
//  Copyright (c) 2014-2017 CASM Organization
//  All rights reserved.
//  
//  Developed by: Philipp Paulweber
//                Emmanuel Pescosta
//                Florian Hahn
//                https://github.com/casm-lang/libcasm-fe
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

#include "Lexer.h"

#include "Codes.h"
#include "Logger.h"
#include "SourceLocation.h"

using namespace libcasm_fe;

#undef YY_DECL
#define YY_DECL Parser::symbol_type Lexer::nextToken()

#define yyterminate() return( Parser::make_END(loc) )

// Code run each time a pattern is matched.
#define YY_USER_ACTION loc.columns( yyleng );

%}

/* %option debug */
%option noyywrap
%option nodefault
%option nounput
%option batch
%option noinput
%option yyclass="Lexer"
%option c++

%x LCOMMENT
%x COMMENT
%x STRING

%%
%{
    // Code run each time yylex is called.
    loc.step();
%}

0[bB][01][01\']*[01]* {
    return Parser::make_BINARY( yytext + 2, loc );
}

0[xX][0-9a-fA-F][0-9a-fA-F\']*[0-9a-fA-F]* {
    return Parser::make_HEXADECIMAL( yytext + 2, loc );
}

0[rR][0-9][0-9\']*[0-9]*(\/[0-9][0-9\']*[0-9]*)? {
    return Parser::make_RATIONAL( yytext + 2, loc );
}

[0-9][0-9\']*[0-9]* {
    return Parser::make_INTEGER( yytext, loc );
}

[0-9]+\.[0-9]+([eE][+-]?[0-9]+)? {
    return Parser::make_FLOATING( yytext, loc );
}

{{grammartoken}}

[a-zA-Z_][a-zA-Z0-9\_]* {
    return Parser::make_IDENTIFIER( yytext, loc );
}

[ \t\r]+ { // ignore spaces
    loc.step();
}

\n+ { // ignore newlines
    loc.lines( yyleng );
    loc.step();
}

"//" { // single-line comments
    BEGIN( LCOMMENT );
}
<LCOMMENT>.
<LCOMMENT>\n {
    BEGIN( INITIAL );
    loc.lines( 1 );
    loc.step();
}
<LCOMMENT><<EOF>> {
    BEGIN( INITIAL );
}

"/*" { // multi-line comments
    BEGIN( COMMENT );
}
<COMMENT>"*/" {
    BEGIN( INITIAL );
}
<COMMENT>\n {
    loc.lines( 1 );
}
<COMMENT>([^*\n]|\r)+|.
<COMMENT><<EOF>> {
    BEGIN( INITIAL );
    log.error( {loc}, "multiline comment not terminated", Code::SyntaxErrorUnclosedComment );
    yyterminate();
}

\" { // strings
    BEGIN( STRING );
    strbuf.clear();
}
<STRING>[^\\\"\n]* { /* eat all tokens */
    strbuf.append( yytext );
}
<STRING>\n {
    loc.lines( 1 );
}
<STRING>\\n {
    strbuf.append( "\n" );
}
<STRING>\\t {
    strbuf.append( "\t" );
}
<STRING>\\\" {
    strbuf.append( "\"" );
}
<STRING>\\' {
    strbuf.append( "\'" );
}
<STRING><<EOF>> {
    BEGIN( INITIAL );
    log.error( {loc}, "string not terminated", Code::SyntaxErrorUnclosedString );
    yyterminate();
}
<STRING>\" {
    BEGIN( INITIAL );
    return Parser::make_STRING( strbuf, loc );
}

. {
    log.error( {loc}, "unrecognized character `" + std::string( yytext ) + "`",
        Code::SyntaxErrorUnrecognizedCharacter );
}

%%

Lexer::Lexer( Logger& log, std::istream& in, std::ostream& out )
: yyFlexLexer( in, out )
, log(log)
, loc()
, strbuf()
{
}

void Lexer::setFileName( const std::string& fileName )
{
    loc.begin.fileName = loc.end.fileName = std::make_shared< std::string >( fileName );
}

void Lexer::LexerError( const char* msg )
{
    log.error( {loc}, msg, Code::SyntaxError );
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
