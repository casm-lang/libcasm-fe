//
//  Copyright (C) 2014-2018 CASM Organization <https://casm-lang.org>
//  All rights reserved.
//
//  Developed by: Philipp Paulweber
//                Emmanuel Pescosta
//                Florian Hahn
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

#include "../main.h"

#include <libcasm-fe/SourceLocation>

#include <libstdhl/File>

#include <memory>

using namespace libcasm_fe;
using namespace Ast;

TEST( AstSpan, Space )
{
    auto span = std::make_shared< Span >( Grammar::Span::SPACE, 10 );
    EXPECT_EQ( span->kind(), Grammar::Span::SPACE );
    EXPECT_EQ( span->length(), 10 );
    EXPECT_STREQ( span->toString().c_str(), "          " );
}

TEST( AstSpan, Newline )
{
    auto span = std::make_shared< Span >( Grammar::Span::NEWLINE, 5 );
    EXPECT_EQ( span->kind(), Grammar::Span::NEWLINE );
    EXPECT_EQ( span->length(), 5 );
    EXPECT_STREQ( span->toString().c_str(), "\n\n\n\n\n" );
}

TEST( AstSpan, Tabulator )
{
    auto span = std::make_shared< Span >( Grammar::Span::TABULATOR, 3 );
    EXPECT_EQ( span->kind(), Grammar::Span::TABULATOR );
    EXPECT_EQ( span->length(), 3 );
    EXPECT_STREQ( span->toString().c_str(), "\t\t\t" );
}

TEST( AstSpan, LineComment_single )
{
    const auto filename = std::make_shared< std::string >( TEST_NAME + ".txt" );

    auto file = libstdhl::File::open( *filename, std::fstream::out );
    file << "\n    //test\n\n   ";
    file.close();

    const auto begin = SourcePosition( filename, 2, 5 );
    const auto end = SourcePosition( filename, 3, 1 );
    const auto loc = SourceLocation( begin, end );

    auto span = std::make_shared< Span >( Grammar::Span::INLINE_COMMENT, 7 );
    span->setSourceLocation( loc );

    EXPECT_EQ( span->kind(), Grammar::Span::INLINE_COMMENT );
    EXPECT_EQ( span->length(), 7 );
    EXPECT_STREQ( span->toString().c_str(), "//test\n" );

    libstdhl::File::remove( *filename );
}

TEST( AstSpan, LineComment_compound )
{
    const auto filename = std::make_shared< std::string >( TEST_NAME + ".txt" );

    auto file = libstdhl::File::open( *filename, std::fstream::out );
    file << "\n    //test\n//test2\n\n   ";
    file.close();

    const auto begin = SourcePosition( filename, 2, 5 );
    const auto end = SourcePosition( filename, 4, 1 );
    const auto loc = SourceLocation( begin, end );

    auto span = std::make_shared< Span >( Grammar::Span::INLINE_COMMENT, 15 );
    span->setSourceLocation( loc );

    EXPECT_EQ( span->kind(), Grammar::Span::INLINE_COMMENT );
    EXPECT_EQ( span->length(), 15 );
    EXPECT_STREQ( span->toString().c_str(), "//test\n//test2\n" );

    libstdhl::File::remove( *filename );
}

TEST( AstSpan, BlockComment )
{
    const auto filename = std::make_shared< std::string >( TEST_NAME + ".txt" );
    auto file = libstdhl::File::open( *filename, std::fstream::out );
    file << "\n    /*test\ntest2\n   test3\n*/\n    ";
    file.close();

    const auto begin = SourcePosition( filename, 2, 5 );
    const auto end = SourcePosition( filename, 5, 3 );
    const auto loc = SourceLocation( begin, end );

    auto span = std::make_shared< Span >( Grammar::Span::BLOCK_COMMENT, 24 );
    span->setSourceLocation( loc );

    EXPECT_EQ( span->kind(), Grammar::Span::BLOCK_COMMENT );
    EXPECT_EQ( span->length(), 24 );
    EXPECT_STREQ( span->toString().c_str(), "/*test\ntest2\n   test3\n*/" );

    libstdhl::File::remove( *filename );
}

TEST( AstSpan, BlockCommentOneLine )
{
    const auto filename = std::make_shared< std::string >( TEST_NAME + ".txt" );
    auto file = libstdhl::File::open( *filename, std::fstream::out );
    file << " /*test*/ ";
    file.close();

    const auto begin = SourcePosition( filename, 1, 2 );
    const auto end = SourcePosition( filename, 1, 10 );
    const auto loc = SourceLocation( begin, end );

    auto span = std::make_shared< Span >( Grammar::Span::BLOCK_COMMENT, 8 );
    span->setSourceLocation( loc );

    EXPECT_EQ( span->kind(), Grammar::Span::BLOCK_COMMENT );
    EXPECT_EQ( span->length(), 8 );
    EXPECT_STREQ( span->toString().c_str(), "/*test*/" );  // "block comment" with only one line

    libstdhl::File::remove( *filename );
}
