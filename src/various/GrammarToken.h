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
            /* 10 */ BEHAVIOR,
            /* 11 */ IMPLEMENT,
            /* 12 */ FOR,
            /* 13 */ SELF,
            /* 14 */ THIS,
            /* 15 */ DOMAIN,
            /* 16 */ BUILTIN,
            /* 17 */ FUNCTION,
            /* 18 */ DEFINED,
            /* 19 */ SEQ,
            /* 20 */ ENDSEQ,
            /* 21 */ PAR,
            /* 22 */ ENDPAR,
            /* 23 */ SKIP,
            /* 24 */ LET,
            /* 25 */ LOCAL,
            /* 26 */ IN,
            /* 27 */ FORALL,
            /* 28 */ CHOOSE,
            /* 29 */ ITERATE,
            /* 30 */ DO,
            /* 31 */ IF,
            /* 32 */ THEN,
            /* 33 */ ELSE,
            /* 34 */ CASE,
            /* 35 */ OF,
            /* 36 */ DEFAULT,
            /* 37 */ HOLDS,
            /* 38 */ EXISTS,
            /* 39 */ WITH,
            /* 40 */ AS,
            /* 41 */ WHILE,
            /* 42 */ UNDEF,
            /* 43 */ FALSE,
            /* 44 */ TRUE,
            /* 45 */ AND,
            /* 46 */ OR,
            /* 47 */ XOR,
            /* 48 */ IMPLIES,
            /* 49 */ NOT,
            /* 50 */ PLUS,
            /* 51 */ MINUS,
            /* 52 */ EQUAL,
            /* 53 */ LPAREN,
            /* 54 */ RPAREN,
            /* 55 */ LSQPAREN,
            /* 56 */ RSQPAREN,
            /* 57 */ LCURPAREN,
            /* 58 */ RCURPAREN,
            /* 59 */ COLON,
            /* 60 */ DOUBLECOLON,
            /* 61 */ UNDERLINE,
            /* 62 */ VERTICAL_BAR,
            /* 63 */ AT,
            /* 64 */ COMMA,
            /* 65 */ LESSER,
            /* 66 */ GREATER,
            /* 67 */ ASTERIX,
            /* 68 */ SLASH,
            /* 69 */ PERCENT,
            /* 70 */ CARET,
            /* 71 */ MARK,
            /* 72 */ MAPS,
            /* 73 */ ARROW,
            /* 74 */ UPDATE,
            /* 75 */ NEQUAL,
            /* 76 */ LESSEQ,
            /* 77 */ GREATEREQ,
            /* 78 */ SEQ_BRACKET,
            /* 79 */ ENDSEQ_BRACKET,
            /* 80 */ DOT,
            /* 81 */ DOTDOT,
            /* 82 */ DOTDOTDOT,
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
                case /* 10 */ Token::BEHAVIOR:
                {
                    return "behavior";
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
                case /* 15 */ Token::DOMAIN:
                {
                    return "domain";
                }
                case /* 16 */ Token::BUILTIN:
                {
                    return "builtin";
                }
                case /* 17 */ Token::FUNCTION:
                {
                    return "function";
                }
                case /* 18 */ Token::DEFINED:
                {
                    return "defined";
                }
                case /* 19 */ Token::SEQ:
                {
                    return "seq";
                }
                case /* 20 */ Token::ENDSEQ:
                {
                    return "endseq";
                }
                case /* 21 */ Token::PAR:
                {
                    return "par";
                }
                case /* 22 */ Token::ENDPAR:
                {
                    return "endpar";
                }
                case /* 23 */ Token::SKIP:
                {
                    return "skip";
                }
                case /* 24 */ Token::LET:
                {
                    return "let";
                }
                case /* 25 */ Token::LOCAL:
                {
                    return "local";
                }
                case /* 26 */ Token::IN:
                {
                    return "in";
                }
                case /* 27 */ Token::FORALL:
                {
                    return "forall";
                }
                case /* 28 */ Token::CHOOSE:
                {
                    return "choose";
                }
                case /* 29 */ Token::ITERATE:
                {
                    return "iterate";
                }
                case /* 30 */ Token::DO:
                {
                    return "do";
                }
                case /* 31 */ Token::IF:
                {
                    return "if";
                }
                case /* 32 */ Token::THEN:
                {
                    return "then";
                }
                case /* 33 */ Token::ELSE:
                {
                    return "else";
                }
                case /* 34 */ Token::CASE:
                {
                    return "case";
                }
                case /* 35 */ Token::OF:
                {
                    return "of";
                }
                case /* 36 */ Token::DEFAULT:
                {
                    return "default";
                }
                case /* 37 */ Token::HOLDS:
                {
                    return "holds";
                }
                case /* 38 */ Token::EXISTS:
                {
                    return "exists";
                }
                case /* 39 */ Token::WITH:
                {
                    return "with";
                }
                case /* 40 */ Token::AS:
                {
                    return "as";
                }
                case /* 41 */ Token::WHILE:
                {
                    return "while";
                }
                case /* 42 */ Token::UNDEF:
                {
                    return "undef";
                }
                case /* 43 */ Token::FALSE:
                {
                    return "false";
                }
                case /* 44 */ Token::TRUE:
                {
                    return "true";
                }
                case /* 45 */ Token::AND:
                {
                    return "and";
                }
                case /* 46 */ Token::OR:
                {
                    return "or";
                }
                case /* 47 */ Token::XOR:
                {
                    return "xor";
                }
                case /* 48 */ Token::IMPLIES:
                {
                    return "implies";
                }
                case /* 49 */ Token::NOT:
                {
                    return "not";
                }
                case /* 50 */ Token::PLUS:
                {
                    return "+";
                }
                case /* 51 */ Token::MINUS:
                {
                    return "-";
                }
                case /* 52 */ Token::EQUAL:
                {
                    return "=";
                }
                case /* 53 */ Token::LPAREN:
                {
                    return "(";
                }
                case /* 54 */ Token::RPAREN:
                {
                    return ")";
                }
                case /* 55 */ Token::LSQPAREN:
                {
                    return "[";
                }
                case /* 56 */ Token::RSQPAREN:
                {
                    return "]";
                }
                case /* 57 */ Token::LCURPAREN:
                {
                    return "{";
                }
                case /* 58 */ Token::RCURPAREN:
                {
                    return "}";
                }
                case /* 59 */ Token::COLON:
                {
                    return ":";
                }
                case /* 60 */ Token::DOUBLECOLON:
                {
                    return "::";
                }
                case /* 61 */ Token::UNDERLINE:
                {
                    return "_";
                }
                case /* 62 */ Token::VERTICAL_BAR:
                {
                    return "|";
                }
                case /* 63 */ Token::AT:
                {
                    return "@";
                }
                case /* 64 */ Token::COMMA:
                {
                    return ",";
                }
                case /* 65 */ Token::LESSER:
                {
                    return "<";
                }
                case /* 66 */ Token::GREATER:
                {
                    return ">";
                }
                case /* 67 */ Token::ASTERIX:
                {
                    return "*";
                }
                case /* 68 */ Token::SLASH:
                {
                    return "/";
                }
                case /* 69 */ Token::PERCENT:
                {
                    return "%";
                }
                case /* 70 */ Token::CARET:
                {
                    return "^";
                }
                case /* 71 */ Token::MARK:
                {
                    return "'";
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
                case /* 80 */ Token::DOT:
                {
                    return ".";
                }
                case /* 81 */ Token::DOTDOT:
                {
                    return "..";
                }
                case /* 82 */ Token::DOTDOTDOT:
                {
                    return "...";
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
