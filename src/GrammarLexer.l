%{
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cstdint>

#include "src/Types.h"
#include "src/Driver.h"
#include "src/LexerHelpers.h"

#include "src/various/GrammarParser.tab.h"

# undef yywrap
# define yywrap() 1

// The location of the current token.
static yy::location loc;

// driver must be global, because it is needed for YY_INPUT
// defined in src/libsyntax/driver.cpp
extern Driver *global_driver;

#define STRBUF_LENGTH 1000
void yyerror(const char *s);
char strbuf[STRBUF_LENGTH];

#define YY_INPUT(buf,result,max_size) { \
  result = global_driver->get_next_chars(buf, max_size); \
  if (  result <= 0  ) \
      result = YY_NULL; \
}

#define yyterminate() return( yy::casmi_parser::make_END(loc) )

// flex uses `register` keyword, which is deprecated in c++11
#pragma GCC diagnostic ignored "-Wdeprecated-register"

%}

/* use debug option for more output */
%option noyywrap nounput batch noinput

%x LCOMMENT
%x COMMENT
%x STRING

%{
    // Code run each time a pattern is matched.
    # define YY_USER_ACTION  loc.columns (yyleng);
%}
%%
%{
    // Code run each time yylex is called.
    loc.step ();
%}


{{grammartoken}}


[a-zA-Z_][a-zA-Z0-9\_]* { return yy::casmi_parser::make_IDENTIFIER(yytext, loc); }

0b[01]+ { 
            INTEGER_T val = convert_to_long(yytext+2, 2, driver, loc);
            return yy::casmi_parser::make_INTEGERCONST(val, loc);
            }

0x[0-9a-fA-F]+ { 
            INTEGER_T val = convert_to_long(yytext+2, 16, driver, loc);
            return yy::casmi_parser::make_INTEGERCONST(val, loc);
            }

[0-9]+ {
          INTEGER_T val = convert_to_long(yytext, 10, driver, loc);
          return yy::casmi_parser::make_INTEGERCONST(val, loc);
       }

[0-9]+\.[0-9]+([eE][+-]?[0-9]+)? { 
            FLOATING_T val = convert_to_float(yytext, driver, loc);
            return yy::casmi_parser::make_FLOATINGCONST(val, loc);
          }
[0-9]+[/][0-9]+ { 
            rational_t val = convert_to_rational(yytext, driver, loc);
            return yy::casmi_parser::make_RATIONALCONST(val, loc); 
}
[0-9]+r {
          yytext[strlen(yytext)-1] = 0;
          rational_t val = convert_to_rational(yytext, driver, loc);
          return yy::casmi_parser::make_RATIONALCONST(val, loc);
        }

[ \t\r]+ loc.step();/* ignore spaces */

\n+ {loc.lines(yyleng); loc.step(); } /* ignore newlines too, but reset yycolumn */

"//" { BEGIN(LCOMMENT); loc.lines(1); loc.step(); }
<LCOMMENT>.
<LCOMMENT>\n { BEGIN( INITIAL ); }
<LCOMMENT><<EOF>> { BEGIN( INITIAL ); }

"/*" { BEGIN(COMMENT); } /* ignore multi line comment */
<COMMENT>"*/" { BEGIN(INITIAL); }
<COMMENT>\n { }
<COMMENT>([^*]|\n|\r)+|.
<COMMENT><<EOF>> { printf( "Multiline comment not terminated on line %d", yylineno ); exit( 2 ); }

\" { BEGIN(STRING); strbuf[0] = '\0'; }
<STRING>[^\\\"\n]* { strncat( strbuf, yytext, STRBUF_LENGTH-1 ); } /* alle Zeichen */
<STRING>\n { }
<STRING>\\n { strncat( strbuf, "\n", STRBUF_LENGTH-1 ); }
<STRING>\\t { strncat( strbuf, "\t", STRBUF_LENGTH-1 ); }
<STRING>\\\" { strncat( strbuf, "\"", STRBUF_LENGTH-1 ); }
<STRING>\\' { strncat( strbuf, "\'", STRBUF_LENGTH-1 ); }
<STRING><<EOF>> { global_driver->error( loc, "unclosed string", libcasm_fe::Codes::SyntaxErrorUnclosedString ); exit( 1 ); }
<STRING>\" { BEGIN(INITIAL); return yy::casmi_parser::make_STRCONST(strbuf, loc); }

. { global_driver->error( loc, "unrecognized character '" + std::string( yytext ) + "'", libcasm_fe::Codes::SyntaxErrorUnrecognizedCharacter ); /*yytext, *yytext, yylineno*/ exit( 1 );
}

%%

//  
//  Local variables:
//  mode: c++
//  indent-tabs-mode: nil
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//  
