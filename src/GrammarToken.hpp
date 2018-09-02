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


CASM            "CASM"          { YY_TOKEN_ACTION( CASM ) }
INIT            "init"          { YY_TOKEN_ACTION( INIT ) }

DERIVED         "derived"       { YY_TOKEN_ACTION( DERIVED ) }
ENUMERATION     "enumeration"   { YY_TOKEN_ACTION( ENUMERATION ) }
RULE            "rule"          { YY_TOKEN_ACTION( RULE ) }
USING           "using"         { YY_TOKEN_ACTION( USING ) }
INVARIANT       "invariant"     { YY_TOKEN_ACTION( INVARIANT ) }

FUNCTION        "function"      { YY_TOKEN_ACTION( FUNCTION ) }
INITIALLY       "initially"     { YY_TOKEN_ACTION( INITIALLY ) }
DEFINED         "defined"       { YY_TOKEN_ACTION( DEFINED ) }

SEQ             "seq"           { YY_TOKEN_ACTION( SEQ ) }
ENDSEQ          "endseq"        { YY_TOKEN_ACTION( ENDSEQ ) }
PAR             "par"           { YY_TOKEN_ACTION( PAR ) }
ENDPAR          "endpar"        { YY_TOKEN_ACTION( ENDPAR ) }

SKIP            "skip"          { YY_TOKEN_ACTION( SKIP ) }
LET             "let"           { YY_TOKEN_ACTION( LET ) }
IN              "in"            { YY_TOKEN_ACTION( IN ) }
FORALL          "forall"        { YY_TOKEN_ACTION( FORALL ) }
CHOOSE          "choose"        { YY_TOKEN_ACTION( CHOOSE ) }
ITERATE         "iterate"       { YY_TOKEN_ACTION( ITERATE ) }
DO              "do"            { YY_TOKEN_ACTION( DO ) }
IF              "if"            { YY_TOKEN_ACTION( IF ) }
THEN            "then"          { YY_TOKEN_ACTION( THEN ) }
ELSE            "else"          { YY_TOKEN_ACTION( ELSE ) }
CASE            "case"          { YY_TOKEN_ACTION( CASE ) }
OF              "of"            { YY_TOKEN_ACTION( OF ) }
DEFAULT         "default"       { YY_TOKEN_ACTION( DEFAULT ) }
HOLDS           "holds"         { YY_TOKEN_ACTION( HOLDS ) }
EXISTS          "exists"        { YY_TOKEN_ACTION( EXISTS ) }
WITH            "with"          { YY_TOKEN_ACTION( WITH ) }
AS              "as"            { YY_TOKEN_ACTION( AS ) }
WHILE           "while"         { YY_TOKEN_ACTION( WHILE ) }

UNDEF           "undef"         { YY_TOKEN_ACTION( UNDEF ) }
FALSE           "false"         { YY_TOKEN_ACTION( FALSE ) }
TRUE            "true"          { YY_TOKEN_ACTION( TRUE ) }

AND             "and"           { YY_TOKEN_ACTION( AND ) }
OR              "or"            { YY_TOKEN_ACTION( OR ) }
XOR             "xor"           { YY_TOKEN_ACTION( XOR ) }
IMPLIES         "implies"       { YY_TOKEN_ACTION( IMPLIES ) }
NOT             "not"           { YY_TOKEN_ACTION( NOT ) }

PLUS            "+"             { YY_TOKEN_ACTION( PLUS ) }
MINUS           "-"             { YY_TOKEN_ACTION( MINUS ) }
EQUAL           "="             { YY_TOKEN_ACTION( EQUAL ) }
LPAREN          "("             { YY_TOKEN_ACTION( LPAREN ) }
RPAREN          ")"             { YY_TOKEN_ACTION( RPAREN ) }
LSQPAREN        "["             { YY_TOKEN_ACTION( LSQPAREN ) }
RSQPAREN        "]"             { YY_TOKEN_ACTION( RSQPAREN ) }
LCURPAREN       "{"             { YY_TOKEN_ACTION( LCURPAREN ) }
RCURPAREN       "}"             { YY_TOKEN_ACTION( RCURPAREN ) }
COLON           ":"             { YY_TOKEN_ACTION( COLON ) }
DOUBLECOLON     "::"            { YY_TOKEN_ACTION( DOUBLECOLON ) }
UNDERLINE       "_"             { YY_TOKEN_ACTION( UNDERLINE ) }
VERTICAL_BAR    "|"             { YY_TOKEN_ACTION( VERTICAL_BAR ) }
AT              "@"             { YY_TOKEN_ACTION( AT ) }
COMMA           ","             { YY_TOKEN_ACTION( COMMA ) }
LESSER          "<"             { YY_TOKEN_ACTION( LESSER ) }
GREATER         ">"             { YY_TOKEN_ACTION( GREATER ) }
ASTERIX         "*"             { YY_TOKEN_ACTION( ASTERIX ) }
SLASH           "/"             { YY_TOKEN_ACTION( SLASH ) }
PERCENT         "%"             { YY_TOKEN_ACTION( PERCENT ) }
CARET           "^"             { YY_TOKEN_ACTION( CARET ) }
MARK            "'"             { YY_TOKEN_ACTION( MARK ) }

DOTDOT          ".."            { YY_TOKEN_ACTION( DOTDOT ) }
DOT             "."             { YY_TOKEN_ACTION( DOT ) }
MAPS            "->"            { YY_TOKEN_ACTION( MAPS ) }
ARROW           "=>"            { YY_TOKEN_ACTION( ARROW ) }
UPDATE          ":="            { YY_TOKEN_ACTION( UPDATE ) }
NEQUAL          "!="            { YY_TOKEN_ACTION( NEQUAL ) }
LESSEQ          "<="            { YY_TOKEN_ACTION( LESSEQ ) }
GREATEREQ       ">="            { YY_TOKEN_ACTION( GREATEREQ ) }
SEQ_BRACKET     "{|"            { YY_TOKEN_ACTION( SEQ_BRACKET ) }
ENDSEQ_BRACKET  "|}"            { YY_TOKEN_ACTION( ENDSEQ_BRACKET ) }


//  
//  Local variables:
//  mode: c++
//  indent-tabs-mode: nil
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//  
