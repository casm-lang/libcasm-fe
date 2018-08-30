//
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


CASM            "CASM"          { return Parser::make_CASM(m_loc); }
INIT            "init"          { return Parser::make_INIT(m_loc); }

DERIVED         "derived"       { return Parser::make_DERIVED(m_loc); }
ENUMERATION     "enumeration"   { return Parser::make_ENUMERATION(m_loc); }
RULE            "rule"          { return Parser::make_RULE(m_loc); }
USING           "using"         { return Parser::make_USING(m_loc); }
INVARIANT       "invariant"     { return Parser::make_INVARIANT(loc); }

FUNCTION        "function"      { return Parser::make_FUNCTION(m_loc); }
INITIALLY       "initially"     { return Parser::make_INITIALLY(m_loc); }
DEFINED         "defined"       { return Parser::make_DEFINED(m_loc); }

SEQ             "seq"           { return Parser::make_SEQ(m_loc); }
ENDSEQ          "endseq"        { return Parser::make_ENDSEQ(m_loc); }
PAR             "par"           { return Parser::make_PAR(m_loc); }
ENDPAR          "endpar"        { return Parser::make_ENDPAR(m_loc); }

SKIP            "skip"          { return Parser::make_SKIP(m_loc); }
LET             "let"           { return Parser::make_LET(m_loc); }
IN              "in"            { return Parser::make_IN(m_loc); }
FORALL          "forall"        { return Parser::make_FORALL(m_loc); }
CHOOSE          "choose"        { return Parser::make_CHOOSE(m_loc); }
ITERATE         "iterate"       { return Parser::make_ITERATE(m_loc); }
DO              "do"            { return Parser::make_DO(m_loc); }
IF              "if"            { return Parser::make_IF(m_loc); }
THEN            "then"          { return Parser::make_THEN(m_loc); }
ELSE            "else"          { return Parser::make_ELSE(m_loc); }
CASE            "case"          { return Parser::make_CASE(m_loc); }
OF              "of"            { return Parser::make_OF(m_loc); }
DEFAULT         "default"       { return Parser::make_DEFAULT(m_loc); }
HOLDS           "holds"         { return Parser::make_HOLDS(m_loc); }
EXISTS          "exists"        { return Parser::make_EXISTS(m_loc); }
WITH            "with"          { return Parser::make_WITH(m_loc); }
AS              "as"            { return Parser::make_AS(m_loc); }
WHILE           "while"         { return Parser::make_WHILE(m_loc); }

UNDEF           "undef"         { return Parser::make_UNDEF(m_loc); }
FALSE           "false"         { return Parser::make_FALSE(m_loc); }
TRUE            "true"          { return Parser::make_TRUE(m_loc); }

AND             "and"           { return Parser::make_AND(m_loc); }
OR              "or"            { return Parser::make_OR(m_loc); }
XOR             "xor"           { return Parser::make_XOR(m_loc); }
IMPLIES         "implies"       { return Parser::make_IMPLIES(m_loc); }
NOT             "not"           { return Parser::make_NOT(m_loc); }

PLUS            "+"             { return Parser::make_PLUS(m_loc); }
MINUS           "-"             { return Parser::make_MINUS(m_loc); }
EQUAL           "="             { return Parser::make_EQUAL(m_loc); }
LPAREN          "("             { return Parser::make_LPAREN(m_loc); }
RPAREN          ")"             { return Parser::make_RPAREN(m_loc); }
LSQPAREN        "["             { return Parser::make_LSQPAREN(m_loc); }
RSQPAREN        "]"             { return Parser::make_RSQPAREN(m_loc); }
LCURPAREN       "{"             { return Parser::make_LCURPAREN(m_loc); }
RCURPAREN       "}"             { return Parser::make_RCURPAREN(m_loc); }
COLON           ":"             { return Parser::make_COLON(m_loc); }
DOUBLECOLON     "::"            { return Parser::make_DOUBLECOLON(m_loc); }
UNDERLINE       "_"             { return Parser::make_UNDERLINE(m_loc); }
VERTICAL_BAR    "|"             { return Parser::make_VERTICAL_BAR(m_loc); }
AT              "@"             { return Parser::make_AT(m_loc); }
COMMA           ","             { return Parser::make_COMMA(m_loc); }
LESSER          "<"             { return Parser::make_LESSER(m_loc); }
GREATER         ">"             { return Parser::make_GREATER(m_loc); }
ASTERIX         "*"             { return Parser::make_ASTERIX(m_loc); }
SLASH           "/"             { return Parser::make_SLASH(m_loc); }
PERCENT         "%"             { return Parser::make_PERCENT(m_loc); }
CARET           "^"             { return Parser::make_CARET(m_loc); }
MARK            "'"             { return Parser::make_MARK(m_loc); }

DOTDOT          ".."            { return Parser::make_DOTDOT(m_loc); }
DOT             "."             { return Parser::make_DOT(m_loc); }
MAPS            "->"            { return Parser::make_MAPS(m_loc); }
ARROW           "=>"            { return Parser::make_ARROW(m_loc); }
UPDATE          ":="            { return Parser::make_UPDATE(m_loc); }
NEQUAL          "!="            { return Parser::make_NEQUAL(m_loc); }
LESSEQ          "<="            { return Parser::make_LESSEQ(m_loc); }
GREATEREQ       ">="            { return Parser::make_GREATEREQ(m_loc); }
SEQ_BRACKET     "{|"            { return Parser::make_SEQ_BRACKET(m_loc); }
ENDSEQ_BRACKET  "|}"            { return Parser::make_ENDSEQ_BRACKET(m_loc); }


//  
//  Local variables:
//  mode: c++
//  indent-tabs-mode: nil
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//  
