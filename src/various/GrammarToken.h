//  
//  Copyright (C) 2014-2020 CASM Organization <https://casm-lang.org>
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
            /*  8 */ IMPORT,
            /*  9 */ FUNCTION,
            /* 10 */ DEFINED,
            /* 11 */ SEQ,
            /* 12 */ ENDSEQ,
            /* 13 */ PAR,
            /* 14 */ ENDPAR,
            /* 15 */ SKIP,
            /* 16 */ LET,
            /* 17 */ LOCAL,
            /* 18 */ IN,
            /* 19 */ FORALL,
            /* 20 */ CHOOSE,
            /* 21 */ ITERATE,
            /* 22 */ DO,
            /* 23 */ IF,
            /* 24 */ THEN,
            /* 25 */ ELSE,
            /* 26 */ CASE,
            /* 27 */ OF,
            /* 28 */ DEFAULT,
            /* 29 */ HOLDS,
            /* 30 */ EXISTS,
            /* 31 */ WITH,
            /* 32 */ AS,
            /* 33 */ WHILE,
            /* 34 */ UNDEF,
            /* 35 */ FALSE,
            /* 36 */ TRUE,
            /* 37 */ AND,
            /* 38 */ OR,
            /* 39 */ XOR,
            /* 40 */ IMPLIES,
            /* 41 */ NOT,
            /* 42 */ PLUS,
            /* 43 */ MINUS,
            /* 44 */ EQUAL,
            /* 45 */ LPAREN,
            /* 46 */ RPAREN,
            /* 47 */ LSQPAREN,
            /* 48 */ RSQPAREN,
            /* 49 */ LCURPAREN,
            /* 50 */ RCURPAREN,
            /* 51 */ COLON,
            /* 52 */ DOUBLECOLON,
            /* 53 */ UNDERLINE,
            /* 54 */ VERTICAL_BAR,
            /* 55 */ AT,
            /* 56 */ COMMA,
            /* 57 */ LESSER,
            /* 58 */ GREATER,
            /* 59 */ ASTERIX,
            /* 60 */ SLASH,
            /* 61 */ PERCENT,
            /* 62 */ CARET,
            /* 63 */ MARK,
            /* 64 */ DOTDOT,
            /* 65 */ DOT,
            /* 66 */ MAPS,
            /* 67 */ ARROW,
            /* 68 */ UPDATE,
            /* 69 */ NEQUAL,
            /* 70 */ LESSEQ,
            /* 71 */ GREATEREQ,
            /* 72 */ SEQ_BRACKET,
            /* 73 */ ENDSEQ_BRACKET,
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
                case /*  8 */ Token::IMPORT:
                {
                    return "import";
                }
                case /*  9 */ Token::FUNCTION:
                {
                    return "function";
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
                case /* 17 */ Token::LOCAL:
                {
                    return "local";
                }
                case /* 18 */ Token::IN:
                {
                    return "in";
                }
                case /* 19 */ Token::FORALL:
                {
                    return "forall";
                }
                case /* 20 */ Token::CHOOSE:
                {
                    return "choose";
                }
                case /* 21 */ Token::ITERATE:
                {
                    return "iterate";
                }
                case /* 22 */ Token::DO:
                {
                    return "do";
                }
                case /* 23 */ Token::IF:
                {
                    return "if";
                }
                case /* 24 */ Token::THEN:
                {
                    return "then";
                }
                case /* 25 */ Token::ELSE:
                {
                    return "else";
                }
                case /* 26 */ Token::CASE:
                {
                    return "case";
                }
                case /* 27 */ Token::OF:
                {
                    return "of";
                }
                case /* 28 */ Token::DEFAULT:
                {
                    return "default";
                }
                case /* 29 */ Token::HOLDS:
                {
                    return "holds";
                }
                case /* 30 */ Token::EXISTS:
                {
                    return "exists";
                }
                case /* 31 */ Token::WITH:
                {
                    return "with";
                }
                case /* 32 */ Token::AS:
                {
                    return "as";
                }
                case /* 33 */ Token::WHILE:
                {
                    return "while";
                }
                case /* 34 */ Token::UNDEF:
                {
                    return "undef";
                }
                case /* 35 */ Token::FALSE:
                {
                    return "false";
                }
                case /* 36 */ Token::TRUE:
                {
                    return "true";
                }
                case /* 37 */ Token::AND:
                {
                    return "and";
                }
                case /* 38 */ Token::OR:
                {
                    return "or";
                }
                case /* 39 */ Token::XOR:
                {
                    return "xor";
                }
                case /* 40 */ Token::IMPLIES:
                {
                    return "implies";
                }
                case /* 41 */ Token::NOT:
                {
                    return "not";
                }
                case /* 42 */ Token::PLUS:
                {
                    return "+";
                }
                case /* 43 */ Token::MINUS:
                {
                    return "-";
                }
                case /* 44 */ Token::EQUAL:
                {
                    return "=";
                }
                case /* 45 */ Token::LPAREN:
                {
                    return "(";
                }
                case /* 46 */ Token::RPAREN:
                {
                    return ")";
                }
                case /* 47 */ Token::LSQPAREN:
                {
                    return "[";
                }
                case /* 48 */ Token::RSQPAREN:
                {
                    return "]";
                }
                case /* 49 */ Token::LCURPAREN:
                {
                    return "{";
                }
                case /* 50 */ Token::RCURPAREN:
                {
                    return "}";
                }
                case /* 51 */ Token::COLON:
                {
                    return ":";
                }
                case /* 52 */ Token::DOUBLECOLON:
                {
                    return "::";
                }
                case /* 53 */ Token::UNDERLINE:
                {
                    return "_";
                }
                case /* 54 */ Token::VERTICAL_BAR:
                {
                    return "|";
                }
                case /* 55 */ Token::AT:
                {
                    return "@";
                }
                case /* 56 */ Token::COMMA:
                {
                    return ",";
                }
                case /* 57 */ Token::LESSER:
                {
                    return "<";
                }
                case /* 58 */ Token::GREATER:
                {
                    return ">";
                }
                case /* 59 */ Token::ASTERIX:
                {
                    return "*";
                }
                case /* 60 */ Token::SLASH:
                {
                    return "/";
                }
                case /* 61 */ Token::PERCENT:
                {
                    return "%";
                }
                case /* 62 */ Token::CARET:
                {
                    return "^";
                }
                case /* 63 */ Token::MARK:
                {
                    return "'";
                }
                case /* 64 */ Token::DOTDOT:
                {
                    return "..";
                }
                case /* 65 */ Token::DOT:
                {
                    return ".";
                }
                case /* 66 */ Token::MAPS:
                {
                    return "->";
                }
                case /* 67 */ Token::ARROW:
                {
                    return "=>";
                }
                case /* 68 */ Token::UPDATE:
                {
                    return ":=";
                }
                case /* 69 */ Token::NEQUAL:
                {
                    return "!=";
                }
                case /* 70 */ Token::LESSEQ:
                {
                    return "<=";
                }
                case /* 71 */ Token::GREATEREQ:
                {
                    return ">=";
                }
                case /* 72 */ Token::SEQ_BRACKET:
                {
                    return "{|";
                }
                case /* 73 */ Token::ENDSEQ_BRACKET:
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
