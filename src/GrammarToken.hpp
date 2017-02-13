//
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


CASM            "CASM"          { return yy::Parser::make_CASM(loc); }
INIT            "init"          { return yy::Parser::make_INIT(loc); }

OPTION          "option"        { return yy::Parser::make_OPTION(loc); }

DERIVED         "derived"       { return yy::Parser::make_DERIVED(loc); }
ENUM            "enum"          { return yy::Parser::make_ENUM(loc); }

RULE            "rule"          { return yy::Parser::make_RULE(loc); }
DUMPS           "dumps"         { return yy::Parser::make_DUMPS(loc); }

FUNCTION        "function"      { return yy::Parser::make_FUNCTION(loc); }
INITIALLY       "initially"     { return yy::Parser::make_INITIALLY(loc); }
DEFINED         "defined"       { return yy::Parser::make_DEFINED(loc); }


SEQ             "seq"           { return yy::Parser::make_SEQ(loc); }
ENDSEQ          "endseq"        { return yy::Parser::make_ENDSEQ(loc); }
PAR             "par"           { return yy::Parser::make_PAR(loc); }
ENDPAR          "endpar"        { return yy::Parser::make_ENDPAR(loc); }


SKIP            "skip"          { return yy::Parser::make_SKIP(loc); }
LET             "let"           { return yy::Parser::make_LET(loc); }
IN              "in"            { return yy::Parser::make_IN(loc); }
FORALL          "forall"        { return yy::Parser::make_FORALL(loc); }
ITERATE         "iterate"       { return yy::Parser::make_ITERATE(loc); }
DO              "do"            { return yy::Parser::make_DO(loc); }
CALL            "call"          { return yy::Parser::make_CALL(loc); }
IF              "if"            { return yy::Parser::make_IF(loc); }
THEN            "then"          { return yy::Parser::make_THEN(loc); }
ELSE            "else"          { return yy::Parser::make_ELSE(loc); }
CASE            "case"          { return yy::Parser::make_CASE(loc); }
OF              "of"            { return yy::Parser::make_OF(loc); }
DEFAULT         "default"       { return yy::Parser::make_DEFAULT(loc); }
ENDCASE         "endcase"       { return yy::Parser::make_ENDCASE(loc); }

UNDEF           "undef"         { return yy::Parser::make_UNDEF(loc); }
FALSE           "false"         { return yy::Parser::make_FALSE(loc); }
TRUE            "true"          { return yy::Parser::make_TRUE(loc); }

AND             "and"           { return yy::Parser::make_AND(loc); }
OR              "or"            { return yy::Parser::make_OR(loc); }
XOR             "xor"           { return yy::Parser::make_XOR(loc); }
NOT             "not"           { return yy::Parser::make_NOT(loc); }

PLUS            "+"             { return yy::Parser::make_PLUS(loc); }
MINUS           "-"             { return yy::Parser::make_MINUS(loc); }
EQUAL           "="             { return yy::Parser::make_EQUAL(loc); }
LPAREN          "("             { return yy::Parser::make_LPAREN(loc); }
RPAREN          ")"             { return yy::Parser::make_RPAREN(loc); }
LSQPAREN        "["             { return yy::Parser::make_LSQPAREN(loc); }
RSQPAREN        "]"             { return yy::Parser::make_RSQPAREN(loc); }
LCURPAREN       "{"             { return yy::Parser::make_LCURPAREN(loc); }
RCURPAREN       "}"             { return yy::Parser::make_RCURPAREN(loc); }
DOT             "."             { return yy::Parser::make_DOT(loc); }
COLON           ":"             { return yy::Parser::make_COLON(loc); }
UNDERLINE       "_"             { return yy::Parser::make_UNDERLINE(loc); }
AT              "@"             { return yy::Parser::make_AT(loc); }
COMMA           ","             { return yy::Parser::make_COMMA(loc); }
LESSER          "<"             { return yy::Parser::make_LESSER(loc); }
GREATER         ">"             { return yy::Parser::make_GREATER(loc); }
STAR            "*"             { return yy::Parser::make_STAR(loc); }
SLASH           "/"             { return yy::Parser::make_SLASH(loc); }
PERCENT         "%"             { return yy::Parser::make_PERCENT(loc); }

DOTDOT          ".."            { return yy::Parser::make_DOTDOT(loc); }
ARROW           "->"            { return yy::Parser::make_ARROW(loc); }
UPDATE          ":="            { return yy::Parser::make_UPDATE(loc); }
NEQUAL          "!="            { return yy::Parser::make_NEQUAL(loc); }
LESSEQ          "<="            { return yy::Parser::make_LESSEQ(loc); }
GREATEREQ       ">="            { return yy::Parser::make_GREATEREQ(loc); }
SEQ_BRACKET     "{|"            { return yy::Parser::make_SEQ_BRACKET(loc); }
ENDSEQ_BRACKET  "|}"            { return yy::Parser::make_ENDSEQ_BRACKET(loc); }


//  
//  Local variables:
//  mode: c++
//  indent-tabs-mode: nil
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//  
