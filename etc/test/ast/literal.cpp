//
//  Copyright (C) 2014-2019 CASM Organization <https://casm-lang.org>
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

#include <memory>

using namespace libcasm_fe;
using namespace Ast;

TEST( AstValueLiteral, toStringOfBoolean )
{
    // 'true'
    {
        const auto filename = std::make_shared< std::string >( TEST_NAME + ".casm" );
        auto file = libstdhl::File::open( *filename, std::fstream::out );
        file << " true ";
        file.close();

        const auto begin = SourcePosition( filename, 1, 2 );
        const auto end = SourcePosition( filename, 1, 6 );
        const auto loc = SourceLocation( begin, end );

        const auto value = libstdhl::Memory::get< libcasm_ir::BooleanConstant >( true );
        const auto literal = Ast::make< ValueLiteral >( loc, value );
        EXPECT_EQ( literal->toString(), "true" );

        libstdhl::File::remove( *filename );
    }
    // 'false'
    {
        const auto filename = std::make_shared< std::string >( TEST_NAME + ".casm" );
        auto file = libstdhl::File::open( *filename, std::fstream::out );
        file << " false ";
        file.close();

        const auto begin = SourcePosition( filename, 1, 2 );
        const auto end = SourcePosition( filename, 1, 7 );
        const auto loc = SourceLocation( begin, end );

        const auto value = libstdhl::Memory::get< libcasm_ir::BooleanConstant >( false );
        const auto literal = Ast::make< ValueLiteral >( loc, value );
        EXPECT_EQ( literal->toString(), "false" );

        libstdhl::File::remove( *filename );
    }
}

TEST( AstValueLiteral, toStringOfBinary )
{
    {
        const auto radix = libstdhl::Type::Radix::BINARY;
        {
            const auto filename = std::make_shared< std::string >( TEST_NAME + ".casm" );
            auto file = libstdhl::File::open( *filename, std::fstream::out );
            file << " 0b0 ";
            file.close();

            const auto begin = SourcePosition( filename, 1, 2 );
            const auto end = SourcePosition( filename, 1, 5 );
            const auto loc = SourceLocation( begin, end );

            const auto value = libstdhl::Memory::get< libcasm_ir::BinaryConstant >( "0", radix );
            const auto literal = Ast::make< ValueLiteral >( loc, value );
            literal->setRadix( radix );
            EXPECT_EQ( literal->toString(), "0b0" );

            libstdhl::File::remove( *filename );
        }
        {
            const auto filename = std::make_shared< std::string >( TEST_NAME + ".casm" );
            auto file = libstdhl::File::open( *filename, std::fstream::out );
            file << " 0b1 ";
            file.close();

            const auto begin = SourcePosition( filename, 1, 2 );
            const auto end = SourcePosition( filename, 1, 5 );
            const auto loc = SourceLocation( begin, end );

            const auto value = libstdhl::Memory::get< libcasm_ir::BinaryConstant >( "1", radix );
            const auto literal = Ast::make< ValueLiteral >( loc, value );
            literal->setRadix( radix );
            EXPECT_EQ( literal->toString(), "0b1" );

            libstdhl::File::remove( *filename );
        }
        {
            const auto filename = std::make_shared< std::string >( TEST_NAME + ".casm" );
            auto file = libstdhl::File::open( *filename, std::fstream::out );
            file << " 0b0000111001010 ";
            file.close();

            const auto begin = SourcePosition( filename, 1, 2 );
            const auto end = SourcePosition( filename, 1, 17 );
            const auto loc = SourceLocation( begin, end );

            const auto value =
                libstdhl::Memory::get< libcasm_ir::BinaryConstant >( "0000111001010", radix );
            const auto literal = Ast::make< ValueLiteral >( loc, value );
            literal->setRadix( radix );
            EXPECT_EQ( literal->toString(), "0b0000111001010" );

            libstdhl::File::remove( *filename );
        }
        {
            const auto filename = std::make_shared< std::string >( TEST_NAME + ".casm" );
            auto file = libstdhl::File::open( *filename, std::fstream::out );
            file << " 0b11111 ";
            file.close();

            const auto begin = SourcePosition( filename, 1, 2 );
            const auto end = SourcePosition( filename, 1, 9 );
            const auto loc = SourceLocation( begin, end );

            const auto value =
                libstdhl::Memory::get< libcasm_ir::BinaryConstant >( "11111", radix );
            const auto literal = Ast::make< ValueLiteral >( loc, value );
            literal->setRadix( radix );
            EXPECT_EQ( literal->toString(), "0b11111" );

            libstdhl::File::remove( *filename );
        }
    }
    {
        const auto radix = libstdhl::Type::Radix::HEXADECIMAL;
        {
            const auto filename = std::make_shared< std::string >( TEST_NAME + ".casm" );
            auto file = libstdhl::File::open( *filename, std::fstream::out );
            file << " 0x0 ";
            file.close();

            const auto begin = SourcePosition( filename, 1, 2 );
            const auto end = SourcePosition( filename, 1, 5 );
            const auto loc = SourceLocation( begin, end );

            const auto value = libstdhl::Memory::get< libcasm_ir::BinaryConstant >( "0", radix );
            const auto literal = Ast::make< ValueLiteral >( loc, value );
            literal->setRadix( radix );
            EXPECT_EQ( literal->toString(), "0x0" );

            libstdhl::File::remove( *filename );
        }
        {
            const auto filename = std::make_shared< std::string >( TEST_NAME + ".casm" );
            auto file = libstdhl::File::open( *filename, std::fstream::out );
            file << " 0x1 ";
            file.close();

            const auto begin = SourcePosition( filename, 1, 2 );
            const auto end = SourcePosition( filename, 1, 5 );
            const auto loc = SourceLocation( begin, end );

            const auto value = libstdhl::Memory::get< libcasm_ir::BinaryConstant >( "1", radix );
            const auto literal = Ast::make< ValueLiteral >( loc, value );
            literal->setRadix( radix );
            EXPECT_EQ( literal->toString(), "0x1" );

            libstdhl::File::remove( *filename );
        }
        {
            const auto filename = std::make_shared< std::string >( TEST_NAME + ".casm" );
            auto file = libstdhl::File::open( *filename, std::fstream::out );
            file << " 0x0feed00123401 ";
            file.close();

            const auto begin = SourcePosition( filename, 1, 2 );
            const auto end = SourcePosition( filename, 1, 17 );
            const auto loc = SourceLocation( begin, end );

            const auto value =
                libstdhl::Memory::get< libcasm_ir::BinaryConstant >( "0feed00123401", radix );
            const auto literal = Ast::make< ValueLiteral >( loc, value );
            literal->setRadix( radix );
            EXPECT_EQ( literal->toString(), "0x0feed00123401" );

            libstdhl::File::remove( *filename );
        }
        {
            const auto filename = std::make_shared< std::string >( TEST_NAME + ".casm" );
            auto file = libstdhl::File::open( *filename, std::fstream::out );
            file << " 0xfffff ";
            file.close();

            const auto begin = SourcePosition( filename, 1, 2 );
            const auto end = SourcePosition( filename, 1, 9 );
            const auto loc = SourceLocation( begin, end );

            const auto value =
                libstdhl::Memory::get< libcasm_ir::BinaryConstant >( "fffff", radix );
            const auto literal = Ast::make< ValueLiteral >( loc, value );
            literal->setRadix( radix );
            EXPECT_EQ( literal->toString(), "0xfffff" );

            libstdhl::File::remove( *filename );
        }
    }
}

TEST( AstValueLiteral, toStringOfInteger )
{
    const auto radix = libstdhl::Type::Radix::DECIMAL;
    {
        const auto filename = std::make_shared< std::string >( TEST_NAME + ".casm" );
        auto file = libstdhl::File::open( *filename, std::fstream::out );
        file << " 0 ";
        file.close();

        const auto begin = SourcePosition( filename, 1, 2 );
        const auto end = SourcePosition( filename, 1, 3 );
        const auto loc = SourceLocation( begin, end );

        const auto value = libstdhl::Memory::get< libcasm_ir::IntegerConstant >( "0", radix );
        const auto literal = Ast::make< ValueLiteral >( loc, value );
        EXPECT_EQ( literal->toString(), "0" );

        libstdhl::File::remove( *filename );
    }
    {
        const auto filename = std::make_shared< std::string >( TEST_NAME + ".casm" );
        auto file = libstdhl::File::open( *filename, std::fstream::out );
        file << " 1 ";
        file.close();

        const auto begin = SourcePosition( filename, 1, 2 );
        const auto end = SourcePosition( filename, 1, 3 );
        const auto loc = SourceLocation( begin, end );

        const auto value = libstdhl::Memory::get< libcasm_ir::IntegerConstant >( "1", radix );
        const auto literal = Ast::make< ValueLiteral >( loc, value );
        EXPECT_EQ( literal->toString(), "1" );

        libstdhl::File::remove( *filename );
    }
    {
        const auto filename = std::make_shared< std::string >( TEST_NAME + ".casm" );
        auto file = libstdhl::File::open( *filename, std::fstream::out );
        file << " -1 ";
        file.close();

        const auto begin = SourcePosition( filename, 1, 2 );
        const auto end = SourcePosition( filename, 1, 4 );
        const auto loc = SourceLocation( begin, end );

        const auto value = libstdhl::Memory::get< libcasm_ir::IntegerConstant >( "-1", radix );
        const auto literal = Ast::make< ValueLiteral >( loc, value );
        EXPECT_EQ( literal->toString(), "-1" );

        libstdhl::File::remove( *filename );
    }
    {
        const auto filename = std::make_shared< std::string >( TEST_NAME + ".casm" );
        auto file = libstdhl::File::open( *filename, std::fstream::out );
        file << " 1782634879 ";
        file.close();

        const auto begin = SourcePosition( filename, 1, 2 );
        const auto end = SourcePosition( filename, 1, 12 );
        const auto loc = SourceLocation( begin, end );

        const auto value =
            libstdhl::Memory::get< libcasm_ir::IntegerConstant >( "1782634879", radix );
        const auto literal = Ast::make< ValueLiteral >( loc, value );
        EXPECT_EQ( literal->toString(), "1782634879" );

        libstdhl::File::remove( *filename );
    }
    {
        const auto filename = std::make_shared< std::string >( TEST_NAME + ".casm" );
        auto file = libstdhl::File::open( *filename, std::fstream::out );
        file << " -4343424 ";
        file.close();

        const auto begin = SourcePosition( filename, 1, 2 );
        const auto end = SourcePosition( filename, 1, 10 );
        const auto loc = SourceLocation( begin, end );

        const auto value =
            libstdhl::Memory::get< libcasm_ir::IntegerConstant >( "-4343424", radix );
        const auto literal = Ast::make< ValueLiteral >( loc, value );
        EXPECT_EQ( literal->toString(), "-4343424" );

        libstdhl::File::remove( *filename );
    }
}

//
//  Local variables:
//  mode: c++
//  indent-tabs-mode: nil
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//
