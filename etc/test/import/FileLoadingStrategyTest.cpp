//
//  Copyright (C) 2014-2021 CASM Organization <https://casm-lang.org>
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

#include "../main.h"

#include <libstdhl/File>
#include <libstdhl/Standard>

using namespace libcasm_fe;

TEST(
    libcasm_fe_import_FileLoadingStrategyTest,
    shouldThrowNoSuchSpecificationErrorIfRequestedSourceDoesNotExist )
{
    // GIVEN
    FileLoadingStrategy loadingStrategy( "." );

    const auto importPath = Ast::IdentifierPath::fromIdentifier(
        std::make_shared< Ast::Identifier >( "NonExistingLib" ) );
    const auto importPathURI = loadingStrategy.toURI( importPath );

    // WHEN
    EXPECT_THROW( loadingStrategy.loadSource( importPathURI ), NoSuchSpecificationError );
}

static const auto specification = R"***(
CASM init test

rule test = skip

)***";

TEST( libcasm_fe_import_FileLoadingStrategyTest, shouldReturnSourceOfIdentifier )
{
    // GIVEN
    FileLoadingStrategy loadingStrategy( "." );

    const std::string fileName( "./" + TEST_NAME + ".casm" );
    const auto importPath =
        Ast::IdentifierPath::fromIdentifier( std::make_shared< Ast::Identifier >( TEST_NAME ) );
    const auto importPathURI = loadingStrategy.toURI( importPath );

    auto file = libstdhl::File::open( fileName, std::fstream::out );
    file << specification;
    file.close();

    // WHEN
    const auto source = loadingStrategy.loadSource( importPathURI );

    // THEN
    EXPECT_STREQ( fileName.c_str(), source->filename().c_str() );

    // CLEANUP
    libstdhl::File::remove( fileName );
    EXPECT_EQ( libstdhl::File::exists( fileName ), false );
}

TEST( libcasm_fe_import_FileLoadingStrategyTest, shouldReturnSourceInFolderOfIdentifierPath )
{
    // GIVEN
    FileLoadingStrategy loadingStrategy( "." );

    const std::string filePath( TEST_CASE );
    const std::string fileName( "./" + filePath + "/" + TEST_UNIT + ".casm" );
    const auto identifiers = std::make_shared< Ast::Identifiers >();
    identifiers->add( std::make_shared< Ast::Identifier >( filePath ) );
    identifiers->add( std::make_shared< Ast::Identifier >( TEST_UNIT ) );
    const auto importPath = std::make_shared< Ast::IdentifierPath >( identifiers );
    const auto importPathURI = loadingStrategy.toURI( importPath );

    libstdhl::File::Path::create( filePath );
    auto file = libstdhl::File::open( fileName, std::fstream::out );
    file << specification;
    file.close();

    // WHEN
    const auto source = loadingStrategy.loadSource( importPathURI );

    // THEN
    EXPECT_STREQ( fileName.c_str(), source->filename().c_str() );

    // CLEANUP
    File::remove( fileName );
    EXPECT_EQ( libstdhl::File::exists( fileName ), false );
    File::Path::remove( filePath );
    EXPECT_EQ( libstdhl::File::Path::exists( filePath ), false );
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
