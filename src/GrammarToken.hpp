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


CASM            "CASM"          { return Parser::make_CASM(loc); }
INIT            "init"          { return Parser::make_INIT(loc); }

DERIVED         "derived"       { return Parser::make_DERIVED(loc); }
ENUMERATION     "enumeration"   { return Parser::make_ENUMERATION(loc); }
RULE            "rule"          { return Parser::make_RULE(loc); }
USING           "using"         { return Parser::make_USING(loc); }
INVARIANT       "invariant"     { return Parser::make_INVARIANT(loc); }

FUNCTION        "function"      { return Parser::make_FUNCTION(loc); }
INITIALLY       "initially"     { return Parser::make_INITIALLY(loc); }
DEFINED         "defined"       { return Parser::make_DEFINED(loc); }

SEQ             "seq"           { return Parser::make_SEQ(loc); }
ENDSEQ          "endseq"        { return Parser::make_ENDSEQ(loc); }
PAR             "par"           { return Parser::make_PAR(loc); }
ENDPAR          "endpar"        { return Parser::make_ENDPAR(loc); }

SKIP            "skip"          { return Parser::make_SKIP(loc); }
LET             "let"           { return Parser::make_LET(loc); }
IN              "in"            { return Parser::make_IN(loc); }
FORALL          "forall"        { return Parser::make_FORALL(loc); }
CHOOSE          "choose"        { return Parser::make_CHOOSE(loc); }
ITERATE         "iterate"       { return Parser::make_ITERATE(loc); }
DO              "do"            { return Parser::make_DO(loc); }
IF              "if"            { return Parser::make_IF(loc); }
THEN            "then"          { return Parser::make_THEN(loc); }
ELSE            "else"          { return Parser::make_ELSE(loc); }
CASE            "case"          { return Parser::make_CASE(loc); }
OF              "of"            { return Parser::make_OF(loc); }
DEFAULT         "default"       { return Parser::make_DEFAULT(loc); }
HOLDS           "holds"         { return Parser::make_HOLDS(loc); }
EXISTS          "exists"        { return Parser::make_EXISTS(loc); }
WITH            "with"          { return Parser::make_WITH(loc); }
AS              "as"            { return Parser::make_AS(loc); }
WHILE           "while"         { return Parser::make_WHILE(loc); }

UNDEF           "undef"         { return Parser::make_UNDEF(loc); }
FALSE           "false"         { return Parser::make_FALSE(loc); }
TRUE            "true"          { return Parser::make_TRUE(loc); }

AND             "and"           { return Parser::make_AND(loc); }
OR              "or"            { return Parser::make_OR(loc); }
XOR             "xor"           { return Parser::make_XOR(loc); }
IMPLIES         "implies"       { return Parser::make_IMPLIES(loc); }
NOT             "not"           { return Parser::make_NOT(loc); }

PLUS            "+"             { return Parser::make_PLUS(loc); }
MINUS           "-"             { return Parser::make_MINUS(loc); }
EQUAL           "="             { return Parser::make_EQUAL(loc); }
LPAREN          "("             { return Parser::make_LPAREN(loc); }
RPAREN          ")"             { return Parser::make_RPAREN(loc); }
LSQPAREN        "["             { return Parser::make_LSQPAREN(loc); }
RSQPAREN        "]"             { return Parser::make_RSQPAREN(loc); }
LCURPAREN       "{"             { return Parser::make_LCURPAREN(loc); }
RCURPAREN       "}"             { return Parser::make_RCURPAREN(loc); }
COLON           ":"             { return Parser::make_COLON(loc); }
DOUBLECOLON     "::"            { return Parser::make_DOUBLECOLON(loc); }
UNDERLINE       "_"             { return Parser::make_UNDERLINE(loc); }
VERTICAL_BAR    "|"             { return Parser::make_VERTICAL_BAR(loc); }
AT              "@"             { return Parser::make_AT(loc); }
COMMA           ","             { return Parser::make_COMMA(loc); }
LESSER          "<"             { return Parser::make_LESSER(loc); }
GREATER         ">"             { return Parser::make_GREATER(loc); }
ASTERIX         "*"             { return Parser::make_ASTERIX(loc); }
SLASH           "/"             { return Parser::make_SLASH(loc); }
PERCENT         "%"             { return Parser::make_PERCENT(loc); }
CARET           "^"             { return Parser::make_CARET(loc); }
MARK            "'"             { return Parser::make_MARK(loc); }

DOTDOT          ".."            { return Parser::make_DOTDOT(loc); }
DOT             "."             { return Parser::make_DOT(loc); }
MAPS            "->"            { return Parser::make_MAPS(loc); }
ARROW           "=>"            { return Parser::make_ARROW(loc); }
UPDATE          ":="            { return Parser::make_UPDATE(loc); }
NEQUAL          "!="            { return Parser::make_NEQUAL(loc); }
LESSEQ          "<="            { return Parser::make_LESSEQ(loc); }
GREATEREQ       ">="            { return Parser::make_GREATEREQ(loc); }
SEQ_BRACKET     "{|"            { return Parser::make_SEQ_BRACKET(loc); }
ENDSEQ_BRACKET  "|}"            { return Parser::make_ENDSEQ_BRACKET(loc); }


//  
//  Local variables:
//  mode: c++
//  indent-tabs-mode: nil
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//  
