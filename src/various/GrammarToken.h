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
            /* 11 */ IMPLEMENT,
            /* 12 */ FOR,
            /* 13 */ THIS,
            /* 14 */ FUNCTION,
            /* 15 */ DEFINED,
            /* 16 */ SEQ,
            /* 17 */ ENDSEQ,
            /* 18 */ PAR,
            /* 19 */ ENDPAR,
            /* 20 */ SKIP,
            /* 21 */ LET,
            /* 22 */ LOCAL,
            /* 23 */ IN,
            /* 24 */ FORALL,
            /* 25 */ CHOOSE,
            /* 26 */ ITERATE,
            /* 27 */ DO,
            /* 28 */ IF,
            /* 29 */ THEN,
            /* 30 */ ELSE,
            /* 31 */ CASE,
            /* 32 */ OF,
            /* 33 */ DEFAULT,
            /* 34 */ HOLDS,
            /* 35 */ EXISTS,
            /* 36 */ WITH,
            /* 37 */ AS,
            /* 38 */ WHILE,
            /* 39 */ UNDEF,
            /* 40 */ FALSE,
            /* 41 */ TRUE,
            /* 42 */ AND,
            /* 43 */ OR,
            /* 44 */ XOR,
            /* 45 */ IMPLIES,
            /* 46 */ NOT,
            /* 47 */ PLUS,
            /* 48 */ MINUS,
            /* 49 */ EQUAL,
            /* 50 */ LPAREN,
            /* 51 */ RPAREN,
            /* 52 */ LSQPAREN,
            /* 53 */ RSQPAREN,
            /* 54 */ LCURPAREN,
            /* 55 */ RCURPAREN,
            /* 56 */ COLON,
            /* 57 */ DOUBLECOLON,
            /* 58 */ UNDERLINE,
            /* 59 */ VERTICAL_BAR,
            /* 60 */ AT,
            /* 61 */ COMMA,
            /* 62 */ LESSER,
            /* 63 */ GREATER,
            /* 64 */ ASTERIX,
            /* 65 */ SLASH,
            /* 66 */ PERCENT,
            /* 67 */ CARET,
            /* 68 */ MARK,
            /* 69 */ DOTDOT,
            /* 70 */ DOT,
            /* 71 */ MAPS,
            /* 72 */ ARROW,
            /* 73 */ UPDATE,
            /* 74 */ NEQUAL,
            /* 75 */ LESSEQ,
            /* 76 */ GREATEREQ,
            /* 77 */ SEQ_BRACKET,
            /* 78 */ ENDSEQ_BRACKET,
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
                case /* 11 */ Token::IMPLEMENT:
                {
                    return "implement";
                }
                case /* 12 */ Token::FOR:
                {
                    return "for";
                }
                case /* 13 */ Token::THIS:
                {
                    return "this";
                }
                case /* 14 */ Token::FUNCTION:
                {
                    return "function";
                }
                case /* 15 */ Token::DEFINED:
                {
                    return "defined";
                }
                case /* 16 */ Token::SEQ:
                {
                    return "seq";
                }
                case /* 17 */ Token::ENDSEQ:
                {
                    return "endseq";
                }
                case /* 18 */ Token::PAR:
                {
                    return "par";
                }
                case /* 19 */ Token::ENDPAR:
                {
                    return "endpar";
                }
                case /* 20 */ Token::SKIP:
                {
                    return "skip";
                }
                case /* 21 */ Token::LET:
                {
                    return "let";
                }
                case /* 22 */ Token::LOCAL:
                {
                    return "local";
                }
                case /* 23 */ Token::IN:
                {
                    return "in";
                }
                case /* 24 */ Token::FORALL:
                {
                    return "forall";
                }
                case /* 25 */ Token::CHOOSE:
                {
                    return "choose";
                }
                case /* 26 */ Token::ITERATE:
                {
                    return "iterate";
                }
                case /* 27 */ Token::DO:
                {
                    return "do";
                }
                case /* 28 */ Token::IF:
                {
                    return "if";
                }
                case /* 29 */ Token::THEN:
                {
                    return "then";
                }
                case /* 30 */ Token::ELSE:
                {
                    return "else";
                }
                case /* 31 */ Token::CASE:
                {
                    return "case";
                }
                case /* 32 */ Token::OF:
                {
                    return "of";
                }
                case /* 33 */ Token::DEFAULT:
                {
                    return "default";
                }
                case /* 34 */ Token::HOLDS:
                {
                    return "holds";
                }
                case /* 35 */ Token::EXISTS:
                {
                    return "exists";
                }
                case /* 36 */ Token::WITH:
                {
                    return "with";
                }
                case /* 37 */ Token::AS:
                {
                    return "as";
                }
                case /* 38 */ Token::WHILE:
                {
                    return "while";
                }
                case /* 39 */ Token::UNDEF:
                {
                    return "undef";
                }
                case /* 40 */ Token::FALSE:
                {
                    return "false";
                }
                case /* 41 */ Token::TRUE:
                {
                    return "true";
                }
                case /* 42 */ Token::AND:
                {
                    return "and";
                }
                case /* 43 */ Token::OR:
                {
                    return "or";
                }
                case /* 44 */ Token::XOR:
                {
                    return "xor";
                }
                case /* 45 */ Token::IMPLIES:
                {
                    return "implies";
                }
                case /* 46 */ Token::NOT:
                {
                    return "not";
                }
                case /* 47 */ Token::PLUS:
                {
                    return "+";
                }
                case /* 48 */ Token::MINUS:
                {
                    return "-";
                }
                case /* 49 */ Token::EQUAL:
                {
                    return "=";
                }
                case /* 50 */ Token::LPAREN:
                {
                    return "(";
                }
                case /* 51 */ Token::RPAREN:
                {
                    return ")";
                }
                case /* 52 */ Token::LSQPAREN:
                {
                    return "[";
                }
                case /* 53 */ Token::RSQPAREN:
                {
                    return "]";
                }
                case /* 54 */ Token::LCURPAREN:
                {
                    return "{";
                }
                case /* 55 */ Token::RCURPAREN:
                {
                    return "}";
                }
                case /* 56 */ Token::COLON:
                {
                    return ":";
                }
                case /* 57 */ Token::DOUBLECOLON:
                {
                    return "::";
                }
                case /* 58 */ Token::UNDERLINE:
                {
                    return "_";
                }
                case /* 59 */ Token::VERTICAL_BAR:
                {
                    return "|";
                }
                case /* 60 */ Token::AT:
                {
                    return "@";
                }
                case /* 61 */ Token::COMMA:
                {
                    return ",";
                }
                case /* 62 */ Token::LESSER:
                {
                    return "<";
                }
                case /* 63 */ Token::GREATER:
                {
                    return ">";
                }
                case /* 64 */ Token::ASTERIX:
                {
                    return "*";
                }
                case /* 65 */ Token::SLASH:
                {
                    return "/";
                }
                case /* 66 */ Token::PERCENT:
                {
                    return "%";
                }
                case /* 67 */ Token::CARET:
                {
                    return "^";
                }
                case /* 68 */ Token::MARK:
                {
                    return "'";
                }
                case /* 69 */ Token::DOTDOT:
                {
                    return "..";
                }
                case /* 70 */ Token::DOT:
                {
                    return ".";
                }
                case /* 71 */ Token::MAPS:
                {
                    return "->";
                }
                case /* 72 */ Token::ARROW:
                {
                    return "=>";
                }
                case /* 73 */ Token::UPDATE:
                {
                    return ":=";
                }
                case /* 74 */ Token::NEQUAL:
                {
                    return "!=";
                }
                case /* 75 */ Token::LESSEQ:
                {
                    return "<=";
                }
                case /* 76 */ Token::GREATEREQ:
                {
                    return ">=";
                }
                case /* 77 */ Token::SEQ_BRACKET:
                {
                    return "{|";
                }
                case /* 78 */ Token::ENDSEQ_BRACKET:
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
