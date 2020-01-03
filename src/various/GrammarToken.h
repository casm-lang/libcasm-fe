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
            /* 17 */ TEMPLATE,
            /* 18 */ FUNCTION,
            /* 19 */ DEFINED,
            /* 20 */ SEQ,
            /* 21 */ ENDSEQ,
            /* 22 */ PAR,
            /* 23 */ ENDPAR,
            /* 24 */ SKIP,
            /* 25 */ LET,
            /* 26 */ LOCAL,
            /* 27 */ IN,
            /* 28 */ FORALL,
            /* 29 */ CHOOSE,
            /* 30 */ ITERATE,
            /* 31 */ DO,
            /* 32 */ IF,
            /* 33 */ THEN,
            /* 34 */ ELSE,
            /* 35 */ CASE,
            /* 36 */ OF,
            /* 37 */ DEFAULT,
            /* 38 */ HOLDS,
            /* 39 */ EXISTS,
            /* 40 */ WITH,
            /* 41 */ AS,
            /* 42 */ WHILE,
            /* 43 */ UNDEF,
            /* 44 */ FALSE,
            /* 45 */ TRUE,
            /* 46 */ AND,
            /* 47 */ OR,
            /* 48 */ XOR,
            /* 49 */ IMPLIES,
            /* 50 */ NOT,
            /* 51 */ PLUS,
            /* 52 */ MINUS,
            /* 53 */ EQUAL,
            /* 54 */ LPAREN,
            /* 55 */ RPAREN,
            /* 56 */ LSQPAREN,
            /* 57 */ RSQPAREN,
            /* 58 */ LCURPAREN,
            /* 59 */ RCURPAREN,
            /* 60 */ COLON,
            /* 61 */ DOUBLECOLON,
            /* 62 */ UNDERLINE,
            /* 63 */ VERTICAL_BAR,
            /* 64 */ AT,
            /* 65 */ COMMA,
            /* 66 */ LESSER,
            /* 67 */ GREATER,
            /* 68 */ ASTERIX,
            /* 69 */ SLASH,
            /* 70 */ PERCENT,
            /* 71 */ CARET,
            /* 72 */ MARK,
            /* 73 */ DOTDOT,
            /* 74 */ DOT,
            /* 75 */ MAPS,
            /* 76 */ ARROW,
            /* 77 */ UPDATE,
            /* 78 */ NEQUAL,
            /* 79 */ LESSEQ,
            /* 80 */ GREATEREQ,
            /* 81 */ SEQ_BRACKET,
            /* 82 */ ENDSEQ_BRACKET,
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
                case /* 17 */ Token::TEMPLATE:
                {
                    return "template";
                }
                case /* 18 */ Token::FUNCTION:
                {
                    return "function";
                }
                case /* 19 */ Token::DEFINED:
                {
                    return "defined";
                }
                case /* 20 */ Token::SEQ:
                {
                    return "seq";
                }
                case /* 21 */ Token::ENDSEQ:
                {
                    return "endseq";
                }
                case /* 22 */ Token::PAR:
                {
                    return "par";
                }
                case /* 23 */ Token::ENDPAR:
                {
                    return "endpar";
                }
                case /* 24 */ Token::SKIP:
                {
                    return "skip";
                }
                case /* 25 */ Token::LET:
                {
                    return "let";
                }
                case /* 26 */ Token::LOCAL:
                {
                    return "local";
                }
                case /* 27 */ Token::IN:
                {
                    return "in";
                }
                case /* 28 */ Token::FORALL:
                {
                    return "forall";
                }
                case /* 29 */ Token::CHOOSE:
                {
                    return "choose";
                }
                case /* 30 */ Token::ITERATE:
                {
                    return "iterate";
                }
                case /* 31 */ Token::DO:
                {
                    return "do";
                }
                case /* 32 */ Token::IF:
                {
                    return "if";
                }
                case /* 33 */ Token::THEN:
                {
                    return "then";
                }
                case /* 34 */ Token::ELSE:
                {
                    return "else";
                }
                case /* 35 */ Token::CASE:
                {
                    return "case";
                }
                case /* 36 */ Token::OF:
                {
                    return "of";
                }
                case /* 37 */ Token::DEFAULT:
                {
                    return "default";
                }
                case /* 38 */ Token::HOLDS:
                {
                    return "holds";
                }
                case /* 39 */ Token::EXISTS:
                {
                    return "exists";
                }
                case /* 40 */ Token::WITH:
                {
                    return "with";
                }
                case /* 41 */ Token::AS:
                {
                    return "as";
                }
                case /* 42 */ Token::WHILE:
                {
                    return "while";
                }
                case /* 43 */ Token::UNDEF:
                {
                    return "undef";
                }
                case /* 44 */ Token::FALSE:
                {
                    return "false";
                }
                case /* 45 */ Token::TRUE:
                {
                    return "true";
                }
                case /* 46 */ Token::AND:
                {
                    return "and";
                }
                case /* 47 */ Token::OR:
                {
                    return "or";
                }
                case /* 48 */ Token::XOR:
                {
                    return "xor";
                }
                case /* 49 */ Token::IMPLIES:
                {
                    return "implies";
                }
                case /* 50 */ Token::NOT:
                {
                    return "not";
                }
                case /* 51 */ Token::PLUS:
                {
                    return "+";
                }
                case /* 52 */ Token::MINUS:
                {
                    return "-";
                }
                case /* 53 */ Token::EQUAL:
                {
                    return "=";
                }
                case /* 54 */ Token::LPAREN:
                {
                    return "(";
                }
                case /* 55 */ Token::RPAREN:
                {
                    return ")";
                }
                case /* 56 */ Token::LSQPAREN:
                {
                    return "[";
                }
                case /* 57 */ Token::RSQPAREN:
                {
                    return "]";
                }
                case /* 58 */ Token::LCURPAREN:
                {
                    return "{";
                }
                case /* 59 */ Token::RCURPAREN:
                {
                    return "}";
                }
                case /* 60 */ Token::COLON:
                {
                    return ":";
                }
                case /* 61 */ Token::DOUBLECOLON:
                {
                    return "::";
                }
                case /* 62 */ Token::UNDERLINE:
                {
                    return "_";
                }
                case /* 63 */ Token::VERTICAL_BAR:
                {
                    return "|";
                }
                case /* 64 */ Token::AT:
                {
                    return "@";
                }
                case /* 65 */ Token::COMMA:
                {
                    return ",";
                }
                case /* 66 */ Token::LESSER:
                {
                    return "<";
                }
                case /* 67 */ Token::GREATER:
                {
                    return ">";
                }
                case /* 68 */ Token::ASTERIX:
                {
                    return "*";
                }
                case /* 69 */ Token::SLASH:
                {
                    return "/";
                }
                case /* 70 */ Token::PERCENT:
                {
                    return "%";
                }
                case /* 71 */ Token::CARET:
                {
                    return "^";
                }
                case /* 72 */ Token::MARK:
                {
                    return "'";
                }
                case /* 73 */ Token::DOTDOT:
                {
                    return "..";
                }
                case /* 74 */ Token::DOT:
                {
                    return ".";
                }
                case /* 75 */ Token::MAPS:
                {
                    return "->";
                }
                case /* 76 */ Token::ARROW:
                {
                    return "=>";
                }
                case /* 77 */ Token::UPDATE:
                {
                    return ":=";
                }
                case /* 78 */ Token::NEQUAL:
                {
                    return "!=";
                }
                case /* 79 */ Token::LESSEQ:
                {
                    return "<=";
                }
                case /* 80 */ Token::GREATEREQ:
                {
                    return ">=";
                }
                case /* 81 */ Token::SEQ_BRACKET:
                {
                    return "{|";
                }
                case /* 82 */ Token::ENDSEQ_BRACKET:
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
