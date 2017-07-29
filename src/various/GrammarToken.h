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
            /*  9 */ STRUCTURE,
            /* 10 */ FUNCTION,
            /* 11 */ DEFINED,
            /* 12 */ SEQ,
            /* 13 */ ENDSEQ,
            /* 14 */ PAR,
            /* 15 */ ENDPAR,
            /* 16 */ SKIP,
            /* 17 */ LET,
            /* 18 */ LOCAL,
            /* 19 */ IN,
            /* 20 */ FORALL,
            /* 21 */ CHOOSE,
            /* 22 */ ITERATE,
            /* 23 */ DO,
            /* 24 */ IF,
            /* 25 */ THEN,
            /* 26 */ ELSE,
            /* 27 */ CASE,
            /* 28 */ OF,
            /* 29 */ DEFAULT,
            /* 30 */ HOLDS,
            /* 31 */ EXISTS,
            /* 32 */ WITH,
            /* 33 */ AS,
            /* 34 */ WHILE,
            /* 35 */ UNDEF,
            /* 36 */ FALSE,
            /* 37 */ TRUE,
            /* 38 */ AND,
            /* 39 */ OR,
            /* 40 */ XOR,
            /* 41 */ IMPLIES,
            /* 42 */ NOT,
            /* 43 */ PLUS,
            /* 44 */ MINUS,
            /* 45 */ EQUAL,
            /* 46 */ LPAREN,
            /* 47 */ RPAREN,
            /* 48 */ LSQPAREN,
            /* 49 */ RSQPAREN,
            /* 50 */ LCURPAREN,
            /* 51 */ RCURPAREN,
            /* 52 */ COLON,
            /* 53 */ DOUBLECOLON,
            /* 54 */ UNDERLINE,
            /* 55 */ VERTICAL_BAR,
            /* 56 */ AT,
            /* 57 */ COMMA,
            /* 58 */ LESSER,
            /* 59 */ GREATER,
            /* 60 */ ASTERIX,
            /* 61 */ SLASH,
            /* 62 */ PERCENT,
            /* 63 */ CARET,
            /* 64 */ MARK,
            /* 65 */ DOTDOT,
            /* 66 */ DOT,
            /* 67 */ MAPS,
            /* 68 */ ARROW,
            /* 69 */ UPDATE,
            /* 70 */ NEQUAL,
            /* 71 */ LESSEQ,
            /* 72 */ GREATEREQ,
            /* 73 */ SEQ_BRACKET,
            /* 74 */ ENDSEQ_BRACKET,
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
                case /*  9 */ Token::STRUCTURE:
                {
                    return "structure";
                }
                case /* 10 */ Token::FUNCTION:
                {
                    return "function";
                }
                case /* 11 */ Token::DEFINED:
                {
                    return "defined";
                }
                case /* 12 */ Token::SEQ:
                {
                    return "seq";
                }
                case /* 13 */ Token::ENDSEQ:
                {
                    return "endseq";
                }
                case /* 14 */ Token::PAR:
                {
                    return "par";
                }
                case /* 15 */ Token::ENDPAR:
                {
                    return "endpar";
                }
                case /* 16 */ Token::SKIP:
                {
                    return "skip";
                }
                case /* 17 */ Token::LET:
                {
                    return "let";
                }
                case /* 18 */ Token::LOCAL:
                {
                    return "local";
                }
                case /* 19 */ Token::IN:
                {
                    return "in";
                }
                case /* 20 */ Token::FORALL:
                {
                    return "forall";
                }
                case /* 21 */ Token::CHOOSE:
                {
                    return "choose";
                }
                case /* 22 */ Token::ITERATE:
                {
                    return "iterate";
                }
                case /* 23 */ Token::DO:
                {
                    return "do";
                }
                case /* 24 */ Token::IF:
                {
                    return "if";
                }
                case /* 25 */ Token::THEN:
                {
                    return "then";
                }
                case /* 26 */ Token::ELSE:
                {
                    return "else";
                }
                case /* 27 */ Token::CASE:
                {
                    return "case";
                }
                case /* 28 */ Token::OF:
                {
                    return "of";
                }
                case /* 29 */ Token::DEFAULT:
                {
                    return "default";
                }
                case /* 30 */ Token::HOLDS:
                {
                    return "holds";
                }
                case /* 31 */ Token::EXISTS:
                {
                    return "exists";
                }
                case /* 32 */ Token::WITH:
                {
                    return "with";
                }
                case /* 33 */ Token::AS:
                {
                    return "as";
                }
                case /* 34 */ Token::WHILE:
                {
                    return "while";
                }
                case /* 35 */ Token::UNDEF:
                {
                    return "undef";
                }
                case /* 36 */ Token::FALSE:
                {
                    return "false";
                }
                case /* 37 */ Token::TRUE:
                {
                    return "true";
                }
                case /* 38 */ Token::AND:
                {
                    return "and";
                }
                case /* 39 */ Token::OR:
                {
                    return "or";
                }
                case /* 40 */ Token::XOR:
                {
                    return "xor";
                }
                case /* 41 */ Token::IMPLIES:
                {
                    return "implies";
                }
                case /* 42 */ Token::NOT:
                {
                    return "not";
                }
                case /* 43 */ Token::PLUS:
                {
                    return "+";
                }
                case /* 44 */ Token::MINUS:
                {
                    return "-";
                }
                case /* 45 */ Token::EQUAL:
                {
                    return "=";
                }
                case /* 46 */ Token::LPAREN:
                {
                    return "(";
                }
                case /* 47 */ Token::RPAREN:
                {
                    return ")";
                }
                case /* 48 */ Token::LSQPAREN:
                {
                    return "[";
                }
                case /* 49 */ Token::RSQPAREN:
                {
                    return "]";
                }
                case /* 50 */ Token::LCURPAREN:
                {
                    return "{";
                }
                case /* 51 */ Token::RCURPAREN:
                {
                    return "}";
                }
                case /* 52 */ Token::COLON:
                {
                    return ":";
                }
                case /* 53 */ Token::DOUBLECOLON:
                {
                    return "::";
                }
                case /* 54 */ Token::UNDERLINE:
                {
                    return "_";
                }
                case /* 55 */ Token::VERTICAL_BAR:
                {
                    return "|";
                }
                case /* 56 */ Token::AT:
                {
                    return "@";
                }
                case /* 57 */ Token::COMMA:
                {
                    return ",";
                }
                case /* 58 */ Token::LESSER:
                {
                    return "<";
                }
                case /* 59 */ Token::GREATER:
                {
                    return ">";
                }
                case /* 60 */ Token::ASTERIX:
                {
                    return "*";
                }
                case /* 61 */ Token::SLASH:
                {
                    return "/";
                }
                case /* 62 */ Token::PERCENT:
                {
                    return "%";
                }
                case /* 63 */ Token::CARET:
                {
                    return "^";
                }
                case /* 64 */ Token::MARK:
                {
                    return "'";
                }
                case /* 65 */ Token::DOTDOT:
                {
                    return "..";
                }
                case /* 66 */ Token::DOT:
                {
                    return ".";
                }
                case /* 67 */ Token::MAPS:
                {
                    return "->";
                }
                case /* 68 */ Token::ARROW:
                {
                    return "=>";
                }
                case /* 69 */ Token::UPDATE:
                {
                    return ":=";
                }
                case /* 70 */ Token::NEQUAL:
                {
                    return "!=";
                }
                case /* 71 */ Token::LESSEQ:
                {
                    return "<=";
                }
                case /* 72 */ Token::GREATEREQ:
                {
                    return ">=";
                }
                case /* 73 */ Token::SEQ_BRACKET:
                {
                    return "{|";
                }
                case /* 74 */ Token::ENDSEQ_BRACKET:
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
