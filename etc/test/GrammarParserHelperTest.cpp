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

#include "main.h"

#include <libcasm-fe/GrammarParserHelper>

using namespace libcasm_fe;

TEST(
    GrammarParser_parseIdentifierPath,
    shouldReturnOneIdentifierWithCorrectNameAndLocationWhenPathIsRelative )
{
    // GIVEN
    const std::string path( "::Ident" );
    const SourceLocation location( { nullptr, 1, 1 }, { nullptr, 1, 8 } );

    // WHEN
    const auto identifiers = GrammarParser::parseIdentifierPath( location, path );

    // THEN
    EXPECT_EQ( 1, identifiers->size() );

    const auto& firstIdentifier = *identifiers->at( 0 );
    EXPECT_EQ( "Ident", firstIdentifier.name() );
    EXPECT_EQ( 1, firstIdentifier.sourceLocation().begin.line );
    EXPECT_EQ( 3, firstIdentifier.sourceLocation().begin.column );
    EXPECT_EQ( 1, firstIdentifier.sourceLocation().end.line );
    EXPECT_EQ( 8, firstIdentifier.sourceLocation().end.column );
}

TEST(
    GrammarParser_parseIdentifierPath,
    shouldReturnOneIdentifierWithCorrectNameAndLocationWhenPathIsAbsoluteAndHasOneSegment )
{
    // GIVEN
    const std::string path( "Ident" );
    const SourceLocation location( { nullptr, 1, 1 }, { nullptr, 1, 6 } );

    // WHEN
    const auto identifiers = GrammarParser::parseIdentifierPath( location, path );

    // THEN
    EXPECT_EQ( 1, identifiers->size() );

    const auto& firstIdentifier = *identifiers->at( 0 );
    EXPECT_EQ( "Ident", firstIdentifier.name() );
    EXPECT_EQ( 1, firstIdentifier.sourceLocation().begin.line );
    EXPECT_EQ( 1, firstIdentifier.sourceLocation().begin.column );
    EXPECT_EQ( 1, firstIdentifier.sourceLocation().end.line );
    EXPECT_EQ( 6, firstIdentifier.sourceLocation().end.column );
}

TEST(
    GrammarParser_parseIdentifierPath,
    shouldReturnThreeIdentifiersWithCorrectNameAndLocationWhenPathIsAbsoluteAndHasThreeSegments )
{
    // GIVEN
    const std::string path( "Foo::Bar::Ident" );
    const SourceLocation location( { nullptr, 1, 1 }, { nullptr, 1, 16 } );

    // WHEN
    const auto identifiers = GrammarParser::parseIdentifierPath( location, path );

    // THEN
    EXPECT_EQ( 3, identifiers->size() );

    const auto& firstIdentifier = *identifiers->at( 0 );
    EXPECT_EQ( "Foo", firstIdentifier.name() );
    EXPECT_EQ( 1, firstIdentifier.sourceLocation().begin.line );
    EXPECT_EQ( 1, firstIdentifier.sourceLocation().begin.column );
    EXPECT_EQ( 1, firstIdentifier.sourceLocation().end.line );
    EXPECT_EQ( 4, firstIdentifier.sourceLocation().end.column );

    const auto& secondIdentifier = *identifiers->at( 1 );
    EXPECT_EQ( "Bar", secondIdentifier.name() );
    EXPECT_EQ( 1, secondIdentifier.sourceLocation().begin.line );
    EXPECT_EQ( 6, secondIdentifier.sourceLocation().begin.column );
    EXPECT_EQ( 1, secondIdentifier.sourceLocation().end.line );
    EXPECT_EQ( 9, secondIdentifier.sourceLocation().end.column );

    const auto& thirdIdentifier = *identifiers->at( 2 );
    EXPECT_EQ( "Ident", thirdIdentifier.name() );
    EXPECT_EQ( 1, thirdIdentifier.sourceLocation().begin.line );
    EXPECT_EQ( 11, thirdIdentifier.sourceLocation().begin.column );
    EXPECT_EQ( 1, thirdIdentifier.sourceLocation().end.line );
    EXPECT_EQ( 16, thirdIdentifier.sourceLocation().end.column );
}
