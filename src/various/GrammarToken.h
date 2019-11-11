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
            /* 13 */ SELF,
            /* 14 */ THIS,
            /* 15 */ FUNCTION,
            /* 16 */ DEFINED,
            /* 17 */ SEQ,
            /* 18 */ ENDSEQ,
            /* 19 */ PAR,
            /* 20 */ ENDPAR,
            /* 21 */ SKIP,
            /* 22 */ LET,
            /* 23 */ LOCAL,
            /* 24 */ IN,
            /* 25 */ FORALL,
            /* 26 */ CHOOSE,
            /* 27 */ ITERATE,
            /* 28 */ DO,
            /* 29 */ IF,
            /* 30 */ THEN,
            /* 31 */ ELSE,
            /* 32 */ CASE,
            /* 33 */ OF,
            /* 34 */ DEFAULT,
            /* 35 */ HOLDS,
            /* 36 */ EXISTS,
            /* 37 */ WITH,
            /* 38 */ AS,
            /* 39 */ WHILE,
            /* 40 */ UNDEF,
            /* 41 */ FALSE,
            /* 42 */ TRUE,
            /* 43 */ AND,
            /* 44 */ OR,
            /* 45 */ XOR,
            /* 46 */ IMPLIES,
            /* 47 */ NOT,
            /* 48 */ PLUS,
            /* 49 */ MINUS,
            /* 50 */ EQUAL,
            /* 51 */ LPAREN,
            /* 52 */ RPAREN,
            /* 53 */ LSQPAREN,
            /* 54 */ RSQPAREN,
            /* 55 */ LCURPAREN,
            /* 56 */ RCURPAREN,
            /* 57 */ COLON,
            /* 58 */ DOUBLECOLON,
            /* 59 */ UNDERLINE,
            /* 60 */ VERTICAL_BAR,
            /* 61 */ AT,
            /* 62 */ COMMA,
            /* 63 */ LESSER,
            /* 64 */ GREATER,
            /* 65 */ ASTERIX,
            /* 66 */ SLASH,
            /* 67 */ PERCENT,
            /* 68 */ CARET,
            /* 69 */ MARK,
            /* 70 */ DOTDOT,
            /* 71 */ DOT,
            /* 72 */ MAPS,
            /* 73 */ ARROW,
            /* 74 */ UPDATE,
            /* 75 */ NEQUAL,
            /* 76 */ LESSEQ,
            /* 77 */ GREATEREQ,
            /* 78 */ SEQ_BRACKET,
            /* 79 */ ENDSEQ_BRACKET,
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
                case /* 13 */ Token::SELF:
                {
                    return "self";
                }
                case /* 14 */ Token::THIS:
                {
                    return "this";
                }
                case /* 15 */ Token::FUNCTION:
                {
                    return "function";
                }
                case /* 16 */ Token::DEFINED:
                {
                    return "defined";
                }
                case /* 17 */ Token::SEQ:
                {
                    return "seq";
                }
                case /* 18 */ Token::ENDSEQ:
                {
                    return "endseq";
                }
                case /* 19 */ Token::PAR:
                {
                    return "par";
                }
                case /* 20 */ Token::ENDPAR:
                {
                    return "endpar";
                }
                case /* 21 */ Token::SKIP:
                {
                    return "skip";
                }
                case /* 22 */ Token::LET:
                {
                    return "let";
                }
                case /* 23 */ Token::LOCAL:
                {
                    return "local";
                }
                case /* 24 */ Token::IN:
                {
                    return "in";
                }
                case /* 25 */ Token::FORALL:
                {
                    return "forall";
                }
                case /* 26 */ Token::CHOOSE:
                {
                    return "choose";
                }
                case /* 27 */ Token::ITERATE:
                {
                    return "iterate";
                }
                case /* 28 */ Token::DO:
                {
                    return "do";
                }
                case /* 29 */ Token::IF:
                {
                    return "if";
                }
                case /* 30 */ Token::THEN:
                {
                    return "then";
                }
                case /* 31 */ Token::ELSE:
                {
                    return "else";
                }
                case /* 32 */ Token::CASE:
                {
                    return "case";
                }
                case /* 33 */ Token::OF:
                {
                    return "of";
                }
                case /* 34 */ Token::DEFAULT:
                {
                    return "default";
                }
                case /* 35 */ Token::HOLDS:
                {
                    return "holds";
                }
                case /* 36 */ Token::EXISTS:
                {
                    return "exists";
                }
                case /* 37 */ Token::WITH:
                {
                    return "with";
                }
                case /* 38 */ Token::AS:
                {
                    return "as";
                }
                case /* 39 */ Token::WHILE:
                {
                    return "while";
                }
                case /* 40 */ Token::UNDEF:
                {
                    return "undef";
                }
                case /* 41 */ Token::FALSE:
                {
                    return "false";
                }
                case /* 42 */ Token::TRUE:
                {
                    return "true";
                }
                case /* 43 */ Token::AND:
                {
                    return "and";
                }
                case /* 44 */ Token::OR:
                {
                    return "or";
                }
                case /* 45 */ Token::XOR:
                {
                    return "xor";
                }
                case /* 46 */ Token::IMPLIES:
                {
                    return "implies";
                }
                case /* 47 */ Token::NOT:
                {
                    return "not";
                }
                case /* 48 */ Token::PLUS:
                {
                    return "+";
                }
                case /* 49 */ Token::MINUS:
                {
                    return "-";
                }
                case /* 50 */ Token::EQUAL:
                {
                    return "=";
                }
                case /* 51 */ Token::LPAREN:
                {
                    return "(";
                }
                case /* 52 */ Token::RPAREN:
                {
                    return ")";
                }
                case /* 53 */ Token::LSQPAREN:
                {
                    return "[";
                }
                case /* 54 */ Token::RSQPAREN:
                {
                    return "]";
                }
                case /* 55 */ Token::LCURPAREN:
                {
                    return "{";
                }
                case /* 56 */ Token::RCURPAREN:
                {
                    return "}";
                }
                case /* 57 */ Token::COLON:
                {
                    return ":";
                }
                case /* 58 */ Token::DOUBLECOLON:
                {
                    return "::";
                }
                case /* 59 */ Token::UNDERLINE:
                {
                    return "_";
                }
                case /* 60 */ Token::VERTICAL_BAR:
                {
                    return "|";
                }
                case /* 61 */ Token::AT:
                {
                    return "@";
                }
                case /* 62 */ Token::COMMA:
                {
                    return ",";
                }
                case /* 63 */ Token::LESSER:
                {
                    return "<";
                }
                case /* 64 */ Token::GREATER:
                {
                    return ">";
                }
                case /* 65 */ Token::ASTERIX:
                {
                    return "*";
                }
                case /* 66 */ Token::SLASH:
                {
                    return "/";
                }
                case /* 67 */ Token::PERCENT:
                {
                    return "%";
                }
                case /* 68 */ Token::CARET:
                {
                    return "^";
                }
                case /* 69 */ Token::MARK:
                {
                    return "'";
                }
                case /* 70 */ Token::DOTDOT:
                {
                    return "..";
                }
                case /* 71 */ Token::DOT:
                {
                    return ".";
                }
                case /* 72 */ Token::MAPS:
                {
                    return "->";
                }
                case /* 73 */ Token::ARROW:
                {
                    return "=>";
                }
                case /* 74 */ Token::UPDATE:
                {
                    return ":=";
                }
                case /* 75 */ Token::NEQUAL:
                {
                    return "!=";
                }
                case /* 76 */ Token::LESSEQ:
                {
                    return "<=";
                }
                case /* 77 */ Token::GREATEREQ:
                {
                    return ">=";
                }
                case /* 78 */ Token::SEQ_BRACKET:
                {
                    return "{|";
                }
                case /* 79 */ Token::ENDSEQ_BRACKET:
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
