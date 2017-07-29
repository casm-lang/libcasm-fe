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
            /* 10 */ FEATURE,
            /* 11 */ FUNCTION,
            /* 12 */ DEFINED,
            /* 13 */ SEQ,
            /* 14 */ ENDSEQ,
            /* 15 */ PAR,
            /* 16 */ ENDPAR,
            /* 17 */ SKIP,
            /* 18 */ LET,
            /* 19 */ LOCAL,
            /* 20 */ IN,
            /* 21 */ FORALL,
            /* 22 */ CHOOSE,
            /* 23 */ ITERATE,
            /* 24 */ DO,
            /* 25 */ IF,
            /* 26 */ THEN,
            /* 27 */ ELSE,
            /* 28 */ CASE,
            /* 29 */ OF,
            /* 30 */ DEFAULT,
            /* 31 */ HOLDS,
            /* 32 */ EXISTS,
            /* 33 */ WITH,
            /* 34 */ AS,
            /* 35 */ WHILE,
            /* 36 */ UNDEF,
            /* 37 */ FALSE,
            /* 38 */ TRUE,
            /* 39 */ AND,
            /* 40 */ OR,
            /* 41 */ XOR,
            /* 42 */ IMPLIES,
            /* 43 */ NOT,
            /* 44 */ PLUS,
            /* 45 */ MINUS,
            /* 46 */ EQUAL,
            /* 47 */ LPAREN,
            /* 48 */ RPAREN,
            /* 49 */ LSQPAREN,
            /* 50 */ RSQPAREN,
            /* 51 */ LCURPAREN,
            /* 52 */ RCURPAREN,
            /* 53 */ COLON,
            /* 54 */ DOUBLECOLON,
            /* 55 */ UNDERLINE,
            /* 56 */ VERTICAL_BAR,
            /* 57 */ AT,
            /* 58 */ COMMA,
            /* 59 */ LESSER,
            /* 60 */ GREATER,
            /* 61 */ ASTERIX,
            /* 62 */ SLASH,
            /* 63 */ PERCENT,
            /* 64 */ CARET,
            /* 65 */ MARK,
            /* 66 */ DOTDOT,
            /* 67 */ DOT,
            /* 68 */ MAPS,
            /* 69 */ ARROW,
            /* 70 */ UPDATE,
            /* 71 */ NEQUAL,
            /* 72 */ LESSEQ,
            /* 73 */ GREATEREQ,
            /* 74 */ SEQ_BRACKET,
            /* 75 */ ENDSEQ_BRACKET,
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
                case /* 10 */ Token::FEATURE:
                {
                    return "feature";
                }
                case /* 11 */ Token::FUNCTION:
                {
                    return "function";
                }
                case /* 12 */ Token::DEFINED:
                {
                    return "defined";
                }
                case /* 13 */ Token::SEQ:
                {
                    return "seq";
                }
                case /* 14 */ Token::ENDSEQ:
                {
                    return "endseq";
                }
                case /* 15 */ Token::PAR:
                {
                    return "par";
                }
                case /* 16 */ Token::ENDPAR:
                {
                    return "endpar";
                }
                case /* 17 */ Token::SKIP:
                {
                    return "skip";
                }
                case /* 18 */ Token::LET:
                {
                    return "let";
                }
                case /* 19 */ Token::LOCAL:
                {
                    return "local";
                }
                case /* 20 */ Token::IN:
                {
                    return "in";
                }
                case /* 21 */ Token::FORALL:
                {
                    return "forall";
                }
                case /* 22 */ Token::CHOOSE:
                {
                    return "choose";
                }
                case /* 23 */ Token::ITERATE:
                {
                    return "iterate";
                }
                case /* 24 */ Token::DO:
                {
                    return "do";
                }
                case /* 25 */ Token::IF:
                {
                    return "if";
                }
                case /* 26 */ Token::THEN:
                {
                    return "then";
                }
                case /* 27 */ Token::ELSE:
                {
                    return "else";
                }
                case /* 28 */ Token::CASE:
                {
                    return "case";
                }
                case /* 29 */ Token::OF:
                {
                    return "of";
                }
                case /* 30 */ Token::DEFAULT:
                {
                    return "default";
                }
                case /* 31 */ Token::HOLDS:
                {
                    return "holds";
                }
                case /* 32 */ Token::EXISTS:
                {
                    return "exists";
                }
                case /* 33 */ Token::WITH:
                {
                    return "with";
                }
                case /* 34 */ Token::AS:
                {
                    return "as";
                }
                case /* 35 */ Token::WHILE:
                {
                    return "while";
                }
                case /* 36 */ Token::UNDEF:
                {
                    return "undef";
                }
                case /* 37 */ Token::FALSE:
                {
                    return "false";
                }
                case /* 38 */ Token::TRUE:
                {
                    return "true";
                }
                case /* 39 */ Token::AND:
                {
                    return "and";
                }
                case /* 40 */ Token::OR:
                {
                    return "or";
                }
                case /* 41 */ Token::XOR:
                {
                    return "xor";
                }
                case /* 42 */ Token::IMPLIES:
                {
                    return "implies";
                }
                case /* 43 */ Token::NOT:
                {
                    return "not";
                }
                case /* 44 */ Token::PLUS:
                {
                    return "+";
                }
                case /* 45 */ Token::MINUS:
                {
                    return "-";
                }
                case /* 46 */ Token::EQUAL:
                {
                    return "=";
                }
                case /* 47 */ Token::LPAREN:
                {
                    return "(";
                }
                case /* 48 */ Token::RPAREN:
                {
                    return ")";
                }
                case /* 49 */ Token::LSQPAREN:
                {
                    return "[";
                }
                case /* 50 */ Token::RSQPAREN:
                {
                    return "]";
                }
                case /* 51 */ Token::LCURPAREN:
                {
                    return "{";
                }
                case /* 52 */ Token::RCURPAREN:
                {
                    return "}";
                }
                case /* 53 */ Token::COLON:
                {
                    return ":";
                }
                case /* 54 */ Token::DOUBLECOLON:
                {
                    return "::";
                }
                case /* 55 */ Token::UNDERLINE:
                {
                    return "_";
                }
                case /* 56 */ Token::VERTICAL_BAR:
                {
                    return "|";
                }
                case /* 57 */ Token::AT:
                {
                    return "@";
                }
                case /* 58 */ Token::COMMA:
                {
                    return ",";
                }
                case /* 59 */ Token::LESSER:
                {
                    return "<";
                }
                case /* 60 */ Token::GREATER:
                {
                    return ">";
                }
                case /* 61 */ Token::ASTERIX:
                {
                    return "*";
                }
                case /* 62 */ Token::SLASH:
                {
                    return "/";
                }
                case /* 63 */ Token::PERCENT:
                {
                    return "%";
                }
                case /* 64 */ Token::CARET:
                {
                    return "^";
                }
                case /* 65 */ Token::MARK:
                {
                    return "'";
                }
                case /* 66 */ Token::DOTDOT:
                {
                    return "..";
                }
                case /* 67 */ Token::DOT:
                {
                    return ".";
                }
                case /* 68 */ Token::MAPS:
                {
                    return "->";
                }
                case /* 69 */ Token::ARROW:
                {
                    return "=>";
                }
                case /* 70 */ Token::UPDATE:
                {
                    return ":=";
                }
                case /* 71 */ Token::NEQUAL:
                {
                    return "!=";
                }
                case /* 72 */ Token::LESSEQ:
                {
                    return "<=";
                }
                case /* 73 */ Token::GREATEREQ:
                {
                    return ">=";
                }
                case /* 74 */ Token::SEQ_BRACKET:
                {
                    return "{|";
                }
                case /* 75 */ Token::ENDSEQ_BRACKET:
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
