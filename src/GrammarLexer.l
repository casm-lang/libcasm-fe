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

#include "src/Lexer.h"

#undef YY_DECL
#define YY_DECL yy::Parser::symbol_type yy::Lexer::nextToken()

#define yyterminate() return( yy::Parser::make_END(loc) )

// Code run each time a pattern is matched.
#define YY_USER_ACTION loc.columns( yyleng );

%}

/* %option debug */
%option noyywrap
%option nodefault
%option nounput
%option batch
%option noinput
%option yyclass="yy::Lexer"
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
    return yy::Parser::make_BINARY( yytext + 2, loc );
}

0[xX][0-9a-fA-F][0-9a-fA-F\']*[0-9a-fA-F]* {
    return yy::Parser::make_HEXADECIMAL( yytext + 2, loc );
}

0[rR][0-9][0-9\']*[0-9]*(\/[0-9][0-9\']*[0-9]*)? {
    return yy::Parser::make_RATIONAL( yytext + 2, loc );
}

[0-9][0-9\']*[0-9]* {
    return yy::Parser::make_INTEGER( yytext, loc );
}

[0-9]+\.[0-9]+([eE][+-]?[0-9]+)? {
    return yy::Parser::make_FLOATING( yytext, loc );
}

{{grammartoken}}

[a-zA-Z_][a-zA-Z0-9\_]* {
    return yy::Parser::make_IDENTIFIER( yytext, loc );
}

[ \t\r]+ { /* ignore spaces */
    loc.step();
}

\n+ { /* ignore newlines too, but reset yycolumn */
    loc.lines( yyleng );
    loc.step();
}

"//" {
    BEGIN( LCOMMENT );
    loc.lines( 1 );
    loc.step();
}
<LCOMMENT>.
<LCOMMENT>\n {
    BEGIN( INITIAL );
}
<LCOMMENT><<EOF>> {
    BEGIN( INITIAL );
}

"/*" { /* ignore multi line comments */
    BEGIN( COMMENT );
}
<COMMENT>"*/" {
    BEGIN( INITIAL );
}
<COMMENT>\n
<COMMENT>([^*]|\n|\r)+|.
<COMMENT><<EOF>> {
    printf( "Multiline comment not terminated on line %d", yylineno );
    exit( 2 );
}

\" {
    BEGIN( STRING );
    strbuf.clear();
}
<STRING>[^\\\"\n]* { /* eat all tokens */
    strbuf.append( yytext );
}
<STRING>\n
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
    /*global_driver->error( loc, "unclosed string",
            libcasm_fe::Codes::SyntaxErrorUnclosedString ); TODO*/
    exit( 1 ); // FIXME no exit!!
}
<STRING>\" {
    BEGIN( INITIAL );
    return yy::Parser::make_STRING( strbuf, loc );
}

. {
    /*global_driver->error( loc,
            "unrecognized character '" + std::string( yytext ) + "'",
            libcasm_fe::Codes::SyntaxErrorUnrecognizedCharacter ); TODO*/
    exit( 1 ); // FIXME no exit!!
}

%%

yy::Lexer::Lexer( std::istream& in, std::ostream& out )
: yyFlexLexer( in, out )
, loc()
, strbuf()
{
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
