%{
//  Copyright (C) 2014-2018 CASM Organization <https://casm-lang.org>
//  All rights reserved.
//
//  Developed by: Philipp Paulweber
//                Emmanuel Pescosta
//                Florian Hahn
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

#include "../../src/Lexer.h"

#include <libcasm-fe/Codes>
#include <libcasm-fe/Logger>
#include "various/GrammarToken.h"
#include "../../src/SourceLocation.h"

#include <libcasm-fe/ast/Span>

using namespace libcasm_fe;

#undef YY_DECL
#define YY_DECL Parser::symbol_type Lexer::nextToken()

#define yyterminate() return( Parser::make_END(m_loc) )

// Code run each time a pattern is matched.
#define YY_USER_ACTION m_loc.columns( yyleng );

// Code run each time a token is matched, see GrammarToken.hpp.
#define YY_TOKEN_ACTION( TOKEN ) \
    auto token = Ast::make< Ast::Token >( m_loc, Grammar::Token:: TOKEN ); \
    token->setSpans( fetchSpansAndReset() ); \
    return Parser::make_##TOKEN( token, m_loc );

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
    m_loc.step();
%}

0[bB][01][01\']*[01]* {
    return Parser::make_BINARY( yytext + 2, m_loc );
}

0[xX][0-9a-fA-F][0-9a-fA-F\']*[0-9a-fA-F]* {
    return Parser::make_HEXADECIMAL( yytext + 2, m_loc );
}

0[rR][0-9][0-9\']*[0-9]*(\/[0-9][0-9\']*[0-9]*)? {
    return Parser::make_RATIONAL( yytext + 2, m_loc );
}

[0-9][0-9\']*[0-9]* {
    return Parser::make_INTEGER( yytext, m_loc );
}

[0-9]+\.[0-9]+([eE][+-]?[0-9]+)? {
    return Parser::make_DECIMAL( yytext, m_loc );
}

{{grammartoken}}

[a-zA-Z_][a-zA-Z0-9\_]* {
    return Parser::make_IDENTIFIER( yytext, m_loc );
}

[\x20]+ { // space
    const auto span = Ast::make< Span >( m_loc, Grammar::Span::SPACE, yyleng);
    m_spans->add(span);
    m_loc.step();
}

[\r]+ { // carriage return
    m_loc.step();
}

[\t]+ { // tabulator
    const auto span = Ast::make< Span >( m_loc, Grammar::Span::TABULATOR, yyleng );
    m_spans->add(span);
    m_loc.step();
}

[\n]+ { // newline
    m_loc.lines( yyleng );
    const auto span = Ast::make< Span >( m_loc, Grammar::Span::NEWLINE, yyleng );
    m_spans->add(span);
    m_loc.step();
}

"//" { // single-line comments
    m_strbuf.clear();
    m_strbuf.append( yytext );
    BEGIN( LCOMMENT );
}
<LCOMMENT>. {
    m_strbuf.append( yytext );
}
<LCOMMENT>\n {
    unput( *yytext );
    m_loc.columns( -1 );
    const auto span = Ast::make< Span >( m_loc, Grammar::Span::INLINE_COMMENT, m_strbuf.length() );
    m_spans->add(span);
    m_loc.step();
    BEGIN( INITIAL );
}
<LCOMMENT><<EOF>> {
    const auto span = Ast::make< Span >( m_loc, Grammar::Span::INLINE_COMMENT, m_strbuf.length() );
    m_spans->add(span);
    BEGIN( INITIAL );
}

"/*" { // multi-line comments
    m_strbuf.clear();
    m_strbuf.append( yytext );
    BEGIN( COMMENT );
}
<COMMENT>"*/" {
    m_strbuf.append( yytext );
    const auto span = Ast::make< Span >( m_loc, Grammar::Span::BLOCK_COMMENT, m_strbuf.length() );
    m_spans->add(span);
    m_loc.step();
    BEGIN( INITIAL );
}
<COMMENT>\n {
    m_strbuf.append( yytext );
    m_loc.lines( 1 );
}
<COMMENT>([^*\n]|\r)+|. {
    m_strbuf.append( yytext );
}
<COMMENT><<EOF>> {
    m_log.error( {m_loc}, "multiline comment not terminated", Code::SyntaxErrorUnclosedComment );
    BEGIN( INITIAL );
    yyterminate();
}

\" { // strings
    m_strbuf.clear();
    BEGIN( STRING );
}
<STRING>[^\\"\n]* { /* eat all tokens */
    m_strbuf.append( yytext );
}
<STRING>\n {
    m_loc.lines( 1 );
}
<STRING>\\n {
    m_strbuf.append( "\n" );
}
<STRING>\\t {
    m_strbuf.append( "\t" );
}
<STRING>\\["\\] {
    m_strbuf.append( yytext + 1 );
}
<STRING>\\. {
    m_log.error( {m_loc}, "unrecognized escape sequence", Code::SyntaxErrorUnrecognizedCharacter );
}
<STRING><<EOF>> {
    m_log.error( {m_loc}, "string not terminated", Code::SyntaxErrorUnclosedString );
    BEGIN( INITIAL );
    yyterminate();
}
<STRING>\" {
    BEGIN( INITIAL );
    return Parser::make_STRING( m_strbuf, m_loc );
}

. {
    m_log.error( {m_loc}, "unrecognized character `" + std::string( yytext ) + "`",
        Code::SyntaxErrorUnrecognizedCharacter );
    m_loc.step();
}

%%

Lexer::Lexer( Logger& log, std::istream& in, std::ostream& out )
: yyFlexLexer( in, out )
, m_log( log )
, m_loc()
, m_strbuf()
, m_spans( std::make_shared <Spans> () )
{
}

void Lexer::setFileName( const std::string& fileName )
{
    m_loc.begin.fileName = m_loc.end.fileName = std::make_shared< std::string >( fileName );
}

const Spans::Ptr& Lexer::fetchSpansAndReset( void )
{
    const auto currentSpans = m_spans;
    m_spans = std::make_shared<Spans>();
    return currentSpans;
}

void Lexer::LexerError( const char* msg )
{
    m_log.error( {m_loc}, msg, Code::SyntaxError );
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
