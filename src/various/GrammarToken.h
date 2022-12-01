//  
//  Copyright (C) 2014-2022 CASM Organization <https://casm-lang.org>
//  All rights reserved.
//  
//  Developed by: Philipp Paulweber et al.
//                <https://github.com/casm-lang/libcasm-fe/graphs/contributors>
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
            /* 15 */ DOMAINTYPE,
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
            /* 39 */ MATCH,
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
            /* 73 */ MAPS,
            /* 74 */ ARROW,
            /* 75 */ UPDATE,
            /* 76 */ NEQUAL,
            /* 77 */ LESSEQ,
            /* 78 */ GREATEREQ,
            /* 79 */ SEQ_BRACKET,
            /* 80 */ ENDSEQ_BRACKET,
            /* 81 */ DOT,
            /* 82 */ DOTDOT,
            /* 83 */ DOTDOTDOT,
        };
        
        static std::string tokenAsString( const Grammar::Token token )
        {
            switch( token )
            {
                case /*  0 */ Grammar::Token::UNRESOLVED:
                {
                    return "$unresolved$";
                }
                case /*  1 */ Grammar::Token::CASM:
                {
                    return "CASM";
                }
                case /*  2 */ Grammar::Token::INIT:
                {
                    return "init";
                }
                case /*  3 */ Grammar::Token::DERIVED:
                {
                    return "derived";
                }
                case /*  4 */ Grammar::Token::ENUMERATION:
                {
                    return "enumeration";
                }
                case /*  5 */ Grammar::Token::RULE:
                {
                    return "rule";
                }
                case /*  6 */ Grammar::Token::USING:
                {
                    return "using";
                }
                case /*  7 */ Grammar::Token::INVARIANT:
                {
                    return "invariant";
                }
                case /*  8 */ Grammar::Token::IMPORT:
                {
                    return "import";
                }
                case /*  9 */ Grammar::Token::STRUCTURE:
                {
                    return "structure";
                }
                case /* 10 */ Grammar::Token::BEHAVIOR:
                {
                    return "behavior";
                }
                case /* 11 */ Grammar::Token::IMPLEMENT:
                {
                    return "implement";
                }
                case /* 12 */ Grammar::Token::FOR:
                {
                    return "for";
                }
                case /* 13 */ Grammar::Token::SELF:
                {
                    return "self";
                }
                case /* 14 */ Grammar::Token::THIS:
                {
                    return "this";
                }
                case /* 15 */ Grammar::Token::DOMAINTYPE:
                {
                    return "domain";
                }
                case /* 16 */ Grammar::Token::BUILTIN:
                {
                    return "builtin";
                }
                case /* 17 */ Grammar::Token::FUNCTION:
                {
                    return "function";
                }
                case /* 18 */ Grammar::Token::DEFINED:
                {
                    return "defined";
                }
                case /* 19 */ Grammar::Token::SEQ:
                {
                    return "seq";
                }
                case /* 20 */ Grammar::Token::ENDSEQ:
                {
                    return "endseq";
                }
                case /* 21 */ Grammar::Token::PAR:
                {
                    return "par";
                }
                case /* 22 */ Grammar::Token::ENDPAR:
                {
                    return "endpar";
                }
                case /* 23 */ Grammar::Token::SKIP:
                {
                    return "skip";
                }
                case /* 24 */ Grammar::Token::LET:
                {
                    return "let";
                }
                case /* 25 */ Grammar::Token::LOCAL:
                {
                    return "local";
                }
                case /* 26 */ Grammar::Token::IN:
                {
                    return "in";
                }
                case /* 27 */ Grammar::Token::FORALL:
                {
                    return "forall";
                }
                case /* 28 */ Grammar::Token::CHOOSE:
                {
                    return "choose";
                }
                case /* 29 */ Grammar::Token::ITERATE:
                {
                    return "iterate";
                }
                case /* 30 */ Grammar::Token::DO:
                {
                    return "do";
                }
                case /* 31 */ Grammar::Token::IF:
                {
                    return "if";
                }
                case /* 32 */ Grammar::Token::THEN:
                {
                    return "then";
                }
                case /* 33 */ Grammar::Token::ELSE:
                {
                    return "else";
                }
                case /* 34 */ Grammar::Token::CASE:
                {
                    return "case";
                }
                case /* 35 */ Grammar::Token::OF:
                {
                    return "of";
                }
                case /* 36 */ Grammar::Token::DEFAULT:
                {
                    return "default";
                }
                case /* 37 */ Grammar::Token::HOLDS:
                {
                    return "holds";
                }
                case /* 38 */ Grammar::Token::EXISTS:
                {
                    return "exists";
                }
                case /* 39 */ Grammar::Token::MATCH:
                {
                    return "match";
                }
                case /* 40 */ Grammar::Token::WITH:
                {
                    return "with";
                }
                case /* 41 */ Grammar::Token::AS:
                {
                    return "as";
                }
                case /* 42 */ Grammar::Token::WHILE:
                {
                    return "while";
                }
                case /* 43 */ Grammar::Token::UNDEF:
                {
                    return "undef";
                }
                case /* 44 */ Grammar::Token::FALSE:
                {
                    return "false";
                }
                case /* 45 */ Grammar::Token::TRUE:
                {
                    return "true";
                }
                case /* 46 */ Grammar::Token::AND:
                {
                    return "and";
                }
                case /* 47 */ Grammar::Token::OR:
                {
                    return "or";
                }
                case /* 48 */ Grammar::Token::XOR:
                {
                    return "xor";
                }
                case /* 49 */ Grammar::Token::IMPLIES:
                {
                    return "implies";
                }
                case /* 50 */ Grammar::Token::NOT:
                {
                    return "not";
                }
                case /* 51 */ Grammar::Token::PLUS:
                {
                    return "+";
                }
                case /* 52 */ Grammar::Token::MINUS:
                {
                    return "-";
                }
                case /* 53 */ Grammar::Token::EQUAL:
                {
                    return "=";
                }
                case /* 54 */ Grammar::Token::LPAREN:
                {
                    return "(";
                }
                case /* 55 */ Grammar::Token::RPAREN:
                {
                    return ")";
                }
                case /* 56 */ Grammar::Token::LSQPAREN:
                {
                    return "[";
                }
                case /* 57 */ Grammar::Token::RSQPAREN:
                {
                    return "]";
                }
                case /* 58 */ Grammar::Token::LCURPAREN:
                {
                    return "{";
                }
                case /* 59 */ Grammar::Token::RCURPAREN:
                {
                    return "}";
                }
                case /* 60 */ Grammar::Token::COLON:
                {
                    return ":";
                }
                case /* 61 */ Grammar::Token::DOUBLECOLON:
                {
                    return "::";
                }
                case /* 62 */ Grammar::Token::UNDERLINE:
                {
                    return "_";
                }
                case /* 63 */ Grammar::Token::VERTICAL_BAR:
                {
                    return "|";
                }
                case /* 64 */ Grammar::Token::AT:
                {
                    return "@";
                }
                case /* 65 */ Grammar::Token::COMMA:
                {
                    return ",";
                }
                case /* 66 */ Grammar::Token::LESSER:
                {
                    return "<";
                }
                case /* 67 */ Grammar::Token::GREATER:
                {
                    return ">";
                }
                case /* 68 */ Grammar::Token::ASTERIX:
                {
                    return "*";
                }
                case /* 69 */ Grammar::Token::SLASH:
                {
                    return "/";
                }
                case /* 70 */ Grammar::Token::PERCENT:
                {
                    return "%";
                }
                case /* 71 */ Grammar::Token::CARET:
                {
                    return "^";
                }
                case /* 72 */ Grammar::Token::MARK:
                {
                    return "'";
                }
                case /* 73 */ Grammar::Token::MAPS:
                {
                    return "->";
                }
                case /* 74 */ Grammar::Token::ARROW:
                {
                    return "=>";
                }
                case /* 75 */ Grammar::Token::UPDATE:
                {
                    return ":=";
                }
                case /* 76 */ Grammar::Token::NEQUAL:
                {
                    return "!=";
                }
                case /* 77 */ Grammar::Token::LESSEQ:
                {
                    return "<=";
                }
                case /* 78 */ Grammar::Token::GREATEREQ:
                {
                    return ">=";
                }
                case /* 79 */ Grammar::Token::SEQ_BRACKET:
                {
                    return "{|";
                }
                case /* 80 */ Grammar::Token::ENDSEQ_BRACKET:
                {
                    return "|}";
                }
                case /* 81 */ Grammar::Token::DOT:
                {
                    return ".";
                }
                case /* 82 */ Grammar::Token::DOTDOT:
                {
                    return "..";
                }
                case /* 83 */ Grammar::Token::DOTDOTDOT:
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
