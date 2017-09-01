//
//  Copyright (c) 2014-2017 CASM Organization
//  All rights reserved.
//
//  Developed by: Philipp Paulweber
//                Emmanuel Pescosta
//                Florian Hahn
//                https://github.com/casm-lang/libcasm-fe
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

#include "gtest/gtest.h"

#include <memory>

#include "ast/Node.h"

using namespace libcasm_fe::Ast;

TEST( AstIdentifierPath, baseNameShouldBeEqualToTheLastIdentifier )
{
    // GIVEN
    auto identifiers = std::make_shared< Identifiers >();
    identifiers->add( std::make_shared< Identifier >( "foo" ) );
    identifiers->add( std::make_shared< Identifier >( "bar" ) );

    // WHEN
    const IdentifierPath identifierPath( identifiers );

    // THEN
    EXPECT_EQ( "bar", identifierPath.baseName() );
}

TEST( AstIdentifierPath,
    baseDirShouldBeEmptyIfAbsolutePathConsistsOfOnlyOneIdentifier )
{
    // WHEN
    const IdentifierPath identifierPath(
        std::make_shared< Identifier >( "foo" ),
        IdentifierPath::Type::ABSOLUTE );

    // THEN
    EXPECT_TRUE( identifierPath.baseDir().empty() );
}

TEST( AstIdentifierPath,
    baseDirShouldBeEmptyIfRelativePathConsistsOfOnlyOneIdentifier )
{
    // WHEN
    const IdentifierPath identifierPath(
        std::make_shared< Identifier >( "foo" ),
        IdentifierPath::Type::RELATIVE );

    // THEN
    EXPECT_TRUE( identifierPath.baseDir().empty() );
}

TEST( AstIdentifierPath,
    baseDirShouldBeEqualToFirstIdentifierIfAbsolutePathConsistsOfTwoIdentifiers )
{
    // GIVEN
    auto identifiers = std::make_shared< Identifiers >();
    identifiers->add( std::make_shared< Identifier >( "foo" ) );
    identifiers->add( std::make_shared< Identifier >( "bar" ) );

    // WHEN
    const IdentifierPath identifierPath(
        identifiers, IdentifierPath::Type::ABSOLUTE );

    // THEN
    EXPECT_EQ( "foo", identifierPath.baseDir() );
}

TEST( AstIdentifierPath,
    baseDirShouldBeEqualToFirstIdentifierWithLeadingDotIfRelativePathConsistsOfTwoIdentifiers )
{
    // GIVEN
    auto identifiers = std::make_shared< Identifiers >();
    identifiers->add( std::make_shared< Identifier >( "foo" ) );
    identifiers->add( std::make_shared< Identifier >( "bar" ) );

    // WHEN
    const IdentifierPath identifierPath(
        identifiers, IdentifierPath::Type::RELATIVE );

    // THEN
    EXPECT_EQ( ".foo", identifierPath.baseDir() );
}

TEST( AstIdentifierPath,
    pathShouldConcatenateIdentifiersWithDotIfIdentifierPathIsAbsolute )
{
    // GIVEN
    auto identifiers = std::make_shared< Identifiers >();
    identifiers->add( std::make_shared< Identifier >( "foo" ) );
    identifiers->add( std::make_shared< Identifier >( "bar" ) );

    // WHEN
    const IdentifierPath identifierPath(
        identifiers, IdentifierPath::Type::ABSOLUTE );

    // THEN
    EXPECT_EQ( "foo.bar", identifierPath.path() );
}

TEST( AstIdentifierPath,
    pathShouldConcatenateIdentifiersWithDotAndAddLeadingDotIfIdentifierPathIsRelative )
{
    // GIVEN
    auto identifiers = std::make_shared< Identifiers >();
    identifiers->add( std::make_shared< Identifier >( "foo" ) );
    identifiers->add( std::make_shared< Identifier >( "bar" ) );

    // WHEN
    const IdentifierPath identifierPath(
        identifiers, IdentifierPath::Type::RELATIVE );

    // THEN
    EXPECT_EQ( ".foo.bar", identifierPath.path() );
}
