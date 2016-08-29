//  
//  Copyright (c) 2014-2016 CASM Organization
//  All rights reserved.
//  
//  Developed by: Florian Hahn
//                Philipp Paulweber
//                Emmanuel Pescosta
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


CASM            "CASM"          { return yy::casmi_parser::make_CASM(loc); }
INIT            "init"          { return yy::casmi_parser::make_INIT(loc); }

// PROVIDER        "provider"      { return yy::casmi_parser::make_PROVIDER(loc); }
OPTION          "option"        { return yy::casmi_parser::make_OPTION(loc); }

DERIVED         "derived"       { return yy::casmi_parser::make_DERIVED(loc); }
ENUM            "enum"          { return yy::casmi_parser::make_ENUM(loc); }

RULE            "rule"          { return yy::casmi_parser::make_RULE(loc); }
DUMPS           "dumps"         { return yy::casmi_parser::make_DUMPS(loc); }

FUNCTION        "function"      { return yy::casmi_parser::make_FUNCTION(loc); }
INITIALLY       "initially"     { return yy::casmi_parser::make_INITIALLY(loc); }



SEQ             "seq"           { return yy::casmi_parser::make_SEQ(loc); }
ENDSEQ          "endseq"        { return yy::casmi_parser::make_ENDSEQ(loc); }
PAR             "par"           { return yy::casmi_parser::make_PAR(loc); }
ENDPAR          "endpar"        { return yy::casmi_parser::make_ENDPAR(loc); }


ASSERT          "assert"        { return yy::casmi_parser::make_ASSERT(loc); }
ASSURE          "assure"        { return yy::casmi_parser::make_ASSURE(loc); }
DIEDIE          "diedie"        { return yy::casmi_parser::make_DIEDIE(loc); }
IMPOSSIBLE      "impossible"    { return yy::casmi_parser::make_IMPOSSIBLE(loc); }
SKIP            "skip"          { return yy::casmi_parser::make_SKIP(loc); }
LET             "let"           { return yy::casmi_parser::make_LET(loc); }
IN              "in"            { return yy::casmi_parser::make_IN(loc); }
FORALL          "forall"        { return yy::casmi_parser::make_FORALL(loc); }
ITERATE         "iterate"       { return yy::casmi_parser::make_ITERATE(loc); }
DO              "do"            { return yy::casmi_parser::make_DO(loc); }
CALL            "call"          { return yy::casmi_parser::make_CALL(loc); }
IF              "if"            { return yy::casmi_parser::make_IF(loc); }
THEN            "then"          { return yy::casmi_parser::make_THEN(loc); }
ELSE            "else"          { return yy::casmi_parser::make_ELSE(loc); }
CASE            "case"          { return yy::casmi_parser::make_CASE(loc); }
OF              "of"            { return yy::casmi_parser::make_OF(loc); }
DEFAULT         "default"       { return yy::casmi_parser::make_DEFAULT(loc); }
ENDCASE         "endcase"       { return yy::casmi_parser::make_ENDCASE(loc); }
PRINT           "print"         { return yy::casmi_parser::make_PRINT(loc); }
DEBUG           "debug"         { return yy::casmi_parser::make_DEBUG(loc); }

PUSH            "push"          { return yy::casmi_parser::make_PUSH(loc); }
INTO            "into"          { return yy::casmi_parser::make_INTO(loc); }
POP             "pop"           { return yy::casmi_parser::make_POP(loc); }
FROM            "from"          { return yy::casmi_parser::make_FROM(loc); }
// OBJDUMP         "objdump"       { return yy::casmi_parser::make_OBJDUMP(loc); }

SELF            "self"          { return yy::casmi_parser::make_SELF(loc); }
UNDEF           "undef"         { return yy::casmi_parser::make_UNDEF(loc); }
FALSE           "false"         { return yy::casmi_parser::make_FALSE(loc); }
TRUE            "true"          { return yy::casmi_parser::make_TRUE(loc); }
// SYMBOL          "symbol"        { return yy::casmi_parser::make_SYMBOL(loc); }
// INTERN          "intern_debug"  { return yy::casmi_parser::make_INTERN(loc); }

AND             "and"           { return yy::casmi_parser::make_AND(loc); }
OR              "or"            { return yy::casmi_parser::make_OR(loc); }
XOR             "xor"           { return yy::casmi_parser::make_XOR(loc); }
NOT             "not"           { return yy::casmi_parser::make_NOT(loc); }
RATIONAL_DIV    "div"           { return yy::casmi_parser::make_RATIONAL_DIV(loc); }

PLUS            "+"             { return yy::casmi_parser::make_PLUS(loc); }
MINUS           "-"             { return yy::casmi_parser::make_MINUS(loc); }
EQUAL           "="             { return yy::casmi_parser::make_EQUAL(loc); }
LPAREN          "("             { return yy::casmi_parser::make_LPAREN(loc); }
RPAREN          ")"             { return yy::casmi_parser::make_RPAREN(loc); }
LSQPAREN        "["             { return yy::casmi_parser::make_LSQPAREN(loc); }
RSQPAREN        "]"             { return yy::casmi_parser::make_RSQPAREN(loc); }
LCURPAREN       "{"             { return yy::casmi_parser::make_LCURPAREN(loc); }
RCURPAREN       "}"             { return yy::casmi_parser::make_RCURPAREN(loc); }
DOT             "."             { return yy::casmi_parser::make_DOT(loc); }
COLON           ":"             { return yy::casmi_parser::make_COLON(loc); }
UNDERLINE       "_"             { return yy::casmi_parser::make_UNDERLINE(loc); }
AT              "@"             { return yy::casmi_parser::make_AT(loc); }
COMMA           ","             { return yy::casmi_parser::make_COMMA(loc); }
LESSER          "<"             { return yy::casmi_parser::make_LESSER(loc); }
GREATER         ">"             { return yy::casmi_parser::make_GREATER(loc); }
STAR            "*"             { return yy::casmi_parser::make_STAR(loc); }
SLASH           "/"             { return yy::casmi_parser::make_SLASH(loc); }
PERCENT         "%"             { return yy::casmi_parser::make_PERCENT(loc); }

DOTDOT          ".."            { return yy::casmi_parser::make_DOTDOT(loc); }
ARROW           "->"            { return yy::casmi_parser::make_ARROW(loc); }
UPDATE          ":="            { return yy::casmi_parser::make_UPDATE(loc); }
NEQUAL          "!="            { return yy::casmi_parser::make_NEQUAL(loc); }
LESSEQ          "<="            { return yy::casmi_parser::make_LESSEQ(loc); }
GREATEREQ       ">="            { return yy::casmi_parser::make_GREATEREQ(loc); }
SEQ_BRACKET     "{|"            { return yy::casmi_parser::make_SEQ_BRACKET(loc); }
ENDSEQ_BRACKET  "|}"            { return yy::casmi_parser::make_ENDSEQ_BRACKET(loc); }


//  
//  Local variables:
//  mode: c++
//  indent-tabs-mode: nil
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//  
