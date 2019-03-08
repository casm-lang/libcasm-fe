//  
//  Copyright (C) 2014-2019 CASM Organization <https://casm-lang.org>
//  All rights reserved.
//  
//  Developed by: Philipp Paulweber
//                Emmanuel Pescosta
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

#ifndef _LIBCASM_FE_GRAMMAR_TOKEN_H_
#define _LIBCASM_FE_GRAMMAR_TOKEN_H_

#include <libcasm-fe/CasmFE>

#include <cassert>

namespace libcasm_fe
{
    namespace Grammar
    {
        enum class Token : u8
        {
            /*  0 */ UNRESOLVED,
            /*  1 */ CASM,
            /*  2 */ INIT,
            /*  3 */ DERIVED,
            /*  4 */ ENUMERATION,
            /*  5 */ RULE,
            /*  6 */ USING,
            /*  7 */ INVARIANT,
            /*  8 */ FUNCTION,
            /*  9 */ INITIALLY,
            /* 10 */ DEFINED,
            /* 11 */ SEQ,
            /* 12 */ ENDSEQ,
            /* 13 */ PAR,
            /* 14 */ ENDPAR,
            /* 15 */ SKIP,
            /* 16 */ LET,
            /* 17 */ IN,
            /* 18 */ FORALL,
            /* 19 */ CHOOSE,
            /* 20 */ ITERATE,
            /* 21 */ DO,
            /* 22 */ IF,
            /* 23 */ THEN,
            /* 24 */ ELSE,
            /* 25 */ CASE,
            /* 26 */ OF,
            /* 27 */ DEFAULT,
            /* 28 */ HOLDS,
            /* 29 */ EXISTS,
            /* 30 */ WITH,
            /* 31 */ AS,
            /* 32 */ WHILE,
            /* 33 */ UNDEF,
            /* 34 */ FALSE,
            /* 35 */ TRUE,
            /* 36 */ AND,
            /* 37 */ OR,
            /* 38 */ XOR,
            /* 39 */ IMPLIES,
            /* 40 */ NOT,
            /* 41 */ PLUS,
            /* 42 */ MINUS,
            /* 43 */ EQUAL,
            /* 44 */ LPAREN,
            /* 45 */ RPAREN,
            /* 46 */ LSQPAREN,
            /* 47 */ RSQPAREN,
            /* 48 */ LCURPAREN,
            /* 49 */ RCURPAREN,
            /* 50 */ COLON,
            /* 51 */ DOUBLECOLON,
            /* 52 */ UNDERLINE,
            /* 53 */ VERTICAL_BAR,
            /* 54 */ AT,
            /* 55 */ COMMA,
            /* 56 */ LESSER,
            /* 57 */ GREATER,
            /* 58 */ ASTERIX,
            /* 59 */ SLASH,
            /* 60 */ PERCENT,
            /* 61 */ CARET,
            /* 62 */ MARK,
            /* 63 */ DOTDOT,
            /* 64 */ DOT,
            /* 65 */ MAPS,
            /* 66 */ ARROW,
            /* 67 */ UPDATE,
            /* 68 */ NEQUAL,
            /* 69 */ LESSEQ,
            /* 70 */ GREATEREQ,
            /* 71 */ SEQ_BRACKET,
            /* 72 */ ENDSEQ_BRACKET,
        };
        
        static std::string tokenAsString( const Token token )
        {
            switch( token )
            {
                case /*  0 */ Token::UNRESOLVED:
                {
                    return "$unresolved$";
                }
                case /*  1 */ Token::CASM:
                {
                    return "CASM";
                }
                case /*  2 */ Token::INIT:
                {
                    return "init";
                }
                case /*  3 */ Token::DERIVED:
                {
                    return "derived";
                }
                case /*  4 */ Token::ENUMERATION:
                {
                    return "enumeration";
                }
                case /*  5 */ Token::RULE:
                {
                    return "rule";
                }
                case /*  6 */ Token::USING:
                {
                    return "using";
                }
                case /*  7 */ Token::INVARIANT:
                {
                    return "invariant";
                }
                case /*  8 */ Token::FUNCTION:
                {
                    return "function";
                }
                case /*  9 */ Token::INITIALLY:
                {
                    return "initially";
                }
                case /* 10 */ Token::DEFINED:
                {
                    return "defined";
                }
                case /* 11 */ Token::SEQ:
                {
                    return "seq";
                }
                case /* 12 */ Token::ENDSEQ:
                {
                    return "endseq";
                }
                case /* 13 */ Token::PAR:
                {
                    return "par";
                }
                case /* 14 */ Token::ENDPAR:
                {
                    return "endpar";
                }
                case /* 15 */ Token::SKIP:
                {
                    return "skip";
                }
                case /* 16 */ Token::LET:
                {
                    return "let";
                }
                case /* 17 */ Token::IN:
                {
                    return "in";
                }
                case /* 18 */ Token::FORALL:
                {
                    return "forall";
                }
                case /* 19 */ Token::CHOOSE:
                {
                    return "choose";
                }
                case /* 20 */ Token::ITERATE:
                {
                    return "iterate";
                }
                case /* 21 */ Token::DO:
                {
                    return "do";
                }
                case /* 22 */ Token::IF:
                {
                    return "if";
                }
                case /* 23 */ Token::THEN:
                {
                    return "then";
                }
                case /* 24 */ Token::ELSE:
                {
                    return "else";
                }
                case /* 25 */ Token::CASE:
                {
                    return "case";
                }
                case /* 26 */ Token::OF:
                {
                    return "of";
                }
                case /* 27 */ Token::DEFAULT:
                {
                    return "default";
                }
                case /* 28 */ Token::HOLDS:
                {
                    return "holds";
                }
                case /* 29 */ Token::EXISTS:
                {
                    return "exists";
                }
                case /* 30 */ Token::WITH:
                {
                    return "with";
                }
                case /* 31 */ Token::AS:
                {
                    return "as";
                }
                case /* 32 */ Token::WHILE:
                {
                    return "while";
                }
                case /* 33 */ Token::UNDEF:
                {
                    return "undef";
                }
                case /* 34 */ Token::FALSE:
                {
                    return "false";
                }
                case /* 35 */ Token::TRUE:
                {
                    return "true";
                }
                case /* 36 */ Token::AND:
                {
                    return "and";
                }
                case /* 37 */ Token::OR:
                {
                    return "or";
                }
                case /* 38 */ Token::XOR:
                {
                    return "xor";
                }
                case /* 39 */ Token::IMPLIES:
                {
                    return "implies";
                }
                case /* 40 */ Token::NOT:
                {
                    return "not";
                }
                case /* 41 */ Token::PLUS:
                {
                    return "+";
                }
                case /* 42 */ Token::MINUS:
                {
                    return "-";
                }
                case /* 43 */ Token::EQUAL:
                {
                    return "=";
                }
                case /* 44 */ Token::LPAREN:
                {
                    return "(";
                }
                case /* 45 */ Token::RPAREN:
                {
                    return ")";
                }
                case /* 46 */ Token::LSQPAREN:
                {
                    return "[";
                }
                case /* 47 */ Token::RSQPAREN:
                {
                    return "]";
                }
                case /* 48 */ Token::LCURPAREN:
                {
                    return "{";
                }
                case /* 49 */ Token::RCURPAREN:
                {
                    return "}";
                }
                case /* 50 */ Token::COLON:
                {
                    return ":";
                }
                case /* 51 */ Token::DOUBLECOLON:
                {
                    return "::";
                }
                case /* 52 */ Token::UNDERLINE:
                {
                    return "_";
                }
                case /* 53 */ Token::VERTICAL_BAR:
                {
                    return "|";
                }
                case /* 54 */ Token::AT:
                {
                    return "@";
                }
                case /* 55 */ Token::COMMA:
                {
                    return ",";
                }
                case /* 56 */ Token::LESSER:
                {
                    return "<";
                }
                case /* 57 */ Token::GREATER:
                {
                    return ">";
                }
                case /* 58 */ Token::ASTERIX:
                {
                    return "*";
                }
                case /* 59 */ Token::SLASH:
                {
                    return "/";
                }
                case /* 60 */ Token::PERCENT:
                {
                    return "%";
                }
                case /* 61 */ Token::CARET:
                {
                    return "^";
                }
                case /* 62 */ Token::MARK:
                {
                    return "'";
                }
                case /* 63 */ Token::DOTDOT:
                {
                    return "..";
                }
                case /* 64 */ Token::DOT:
                {
                    return ".";
                }
                case /* 65 */ Token::MAPS:
                {
                    return "->";
                }
                case /* 66 */ Token::ARROW:
                {
                    return "=>";
                }
                case /* 67 */ Token::UPDATE:
                {
                    return ":=";
                }
                case /* 68 */ Token::NEQUAL:
                {
                    return "!=";
                }
                case /* 69 */ Token::LESSEQ:
                {
                    return "<=";
                }
                case /* 70 */ Token::GREATEREQ:
                {
                    return ">=";
                }
                case /* 71 */ Token::SEQ_BRACKET:
                {
                    return "{|";
                }
                case /* 72 */ Token::ENDSEQ_BRACKET:
                {
                    return "|}";
                }
            }
            assert( !"internal error" );
            return std::string();
        }
    };
}

#endif  // _LIBCASM_FE_GRAMMAR_TOKEN_H_

//
//  Local variables:
//  mode: c++
//  indent-tabs-mode: nil
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//
