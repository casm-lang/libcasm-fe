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

#include "../src/execute/UpdateSet.h"

using namespace libcasm_fe;

static value_t make_integer_value( INTEGER_T v )
{
    return value_t( v );
}

TEST( libcasm_fe__updateset, forkedParUSetShouldBeSeqWhenRequestingSeq )
{
    const auto updateSet
        = std::unique_ptr< UpdateSet >( new ParallelUpdateSet( 10UL ) );
    const auto forkedUpdateSet = std::unique_ptr< UpdateSet >(
        updateSet->fork( UpdateSet::Type::Sequential, 10UL ) );
    EXPECT_EQ( UpdateSet::Type::Sequential, forkedUpdateSet->type() );
}

TEST( libcasm_fe__updateset, forkedParUSetShouldBeParWhenRequestingPar )
{
    const auto updateSet
        = std::unique_ptr< UpdateSet >( new ParallelUpdateSet( 10UL ) );
    const auto forkedUpdateSet = std::unique_ptr< UpdateSet >(
        updateSet->fork( UpdateSet::Type::Parallel, 10UL ) );
    EXPECT_EQ( UpdateSet::Type::Parallel, forkedUpdateSet->type() );
}

TEST( libcasm_fe__updateset, forkedSeqUSetShouldBeParWhenRequestingPar )
{
    const auto updateSet
        = std::unique_ptr< UpdateSet >( new SequentialUpdateSet( 10UL ) );
    const auto forkedUpdateSet = std::unique_ptr< UpdateSet >(
        updateSet->fork( UpdateSet::Type::Parallel, 10UL ) );
    EXPECT_EQ( UpdateSet::Type::Parallel, forkedUpdateSet->type() );
}

TEST( libcasm_fe__updateset, forkedSeqUSetShouldBeSeqWhenRequestingSeq )
{
    const auto updateSet
        = std::unique_ptr< UpdateSet >( new SequentialUpdateSet( 10UL ) );
    const auto forkedUpdateSet = std::unique_ptr< UpdateSet >(
        updateSet->fork( UpdateSet::Type::Sequential, 10UL ) );
    EXPECT_EQ( UpdateSet::Type::Sequential, forkedUpdateSet->type() );
}

TEST( libcasm_fe__updateset, mergeParUSetsIntoSeqShouldOverrideLocationValues )
{
    const value_t location;

    const auto seqUpdateSet
        = std::unique_ptr< UpdateSet >( new SequentialUpdateSet( 10UL ) );
    seqUpdateSet->add(
        &location, new Update{.value = make_integer_value( 10 ) } );

    const auto parUpdateSet = std::unique_ptr< UpdateSet >(
        seqUpdateSet->fork( UpdateSet::Type::Parallel, 10UL ) );
    parUpdateSet->add(
        &location, new Update{.value = make_integer_value( 1000 ) } );

    parUpdateSet->merge();

    EXPECT_EQ(
        make_integer_value( 1000 ), seqUpdateSet->lookup( &location )->value );
}

TEST( libcasm_fe__updateset, mergeUSetsIntoEmptyUSetsShouldSwapValues )
{
    const value_t location1, location2, location3;

    const auto seqUpdateSet
        = std::unique_ptr< UpdateSet >( new SequentialUpdateSet( 10UL ) );

    const auto parUpdateSet = std::unique_ptr< UpdateSet >(
        seqUpdateSet->fork( UpdateSet::Type::Parallel, 10UL ) );
    parUpdateSet->add(
        &location1, new Update{.value = make_integer_value( 1000 ) } );
    parUpdateSet->add(
        &location2, new Update{.value = make_integer_value( 2000 ) } );
    parUpdateSet->add(
        &location3, new Update{.value = make_integer_value( 3000 ) } );

    ASSERT_TRUE( seqUpdateSet->empty() );
    ASSERT_EQ( 3, parUpdateSet->size() );

    parUpdateSet->merge();

    EXPECT_TRUE( parUpdateSet->empty() );
    EXPECT_EQ( 3, seqUpdateSet->size() );
}

TEST( libcasm_fe__updateset,
    mergeSeqUSetsIntoParShouldNotThrowWhenOrideLocValWithSameVal )
{
    const value_t location;

    const auto parUpdateSet
        = std::unique_ptr< UpdateSet >( new ParallelUpdateSet( 10UL ) );
    parUpdateSet->add(
        &location, new Update{.value = make_integer_value( 10 ) } );

    const auto seqUpdateSet = std::unique_ptr< UpdateSet >(
        parUpdateSet->fork( UpdateSet::Type::Sequential, 10UL ) );
    seqUpdateSet->add(
        &location, new Update{.value = make_integer_value( 10 ) } );

    EXPECT_NO_THROW( seqUpdateSet->merge() );
}

TEST( libcasm_fe__updateset,
    mergeSeqUSetsIntoParShouldThrowWhenOrideLocValWithDiffVal )
{
    const value_t location;

    const auto parUpdateSet
        = std::unique_ptr< UpdateSet >( new ParallelUpdateSet( 10UL ) );
    parUpdateSet->add(
        &location, new Update{.value = make_integer_value( 10 ) } );

    const auto seqUpdateSet = std::unique_ptr< UpdateSet >(
        parUpdateSet->fork( UpdateSet::Type::Sequential, 10UL ) );
    seqUpdateSet->add(
        &location, new Update{.value = make_integer_value( 1000 ) } );

    EXPECT_THROW( seqUpdateSet->merge(), UpdateSet::Conflict );
}

TEST( libcasm_fe__updateset, lookupShouldPreferUpdatesOfCurrentUpdateSet )
{
    const value_t location;

    const auto seqUpdateSet1
        = std::unique_ptr< UpdateSet >( new SequentialUpdateSet( 10UL ) );
    seqUpdateSet1->add(
        &location, new Update{.value = make_integer_value( 1 ) } );

    const auto parUpdateSet = std::unique_ptr< UpdateSet >(
        seqUpdateSet1->fork( UpdateSet::Type::Parallel, 10UL ) );

    const auto seqUpdateSet2 = std::unique_ptr< UpdateSet >(
        parUpdateSet->fork( UpdateSet::Type::Sequential, 10UL ) );
    seqUpdateSet2->add(
        &location, new Update{.value = make_integer_value( 2 ) } ); // winner

    EXPECT_EQ(
        make_integer_value( 2 ), seqUpdateSet2->lookup( &location )->value );
}

TEST( libcasm_fe__updateset, lookupShouldConsiderAllSequentialParentUpdateSets )
{
    const value_t location;

    const auto seqUpdateSet1
        = std::unique_ptr< UpdateSet >( new SequentialUpdateSet( 10UL ) );
    seqUpdateSet1->add(
        &location, new Update{.value = make_integer_value( 1 ) } );

    const auto parUpdateSet1 = std::unique_ptr< UpdateSet >(
        seqUpdateSet1->fork( UpdateSet::Type::Parallel, 10UL ) );

    const auto seqUpdateSet2 = std::unique_ptr< UpdateSet >(
        parUpdateSet1->fork( UpdateSet::Type::Sequential, 10UL ) );
    seqUpdateSet2->add(
        &location, new Update{.value = make_integer_value( 2 ) } ); // winner

    const auto parUpdateSet2 = std::unique_ptr< UpdateSet >(
        seqUpdateSet2->fork( UpdateSet::Type::Parallel, 10UL ) );
    parUpdateSet2->add(
        &location, new Update{.value = make_integer_value( 0 ) } );

    const auto seqUpdateSet3 = std::unique_ptr< UpdateSet >(
        parUpdateSet2->fork( UpdateSet::Type::Sequential, 10UL ) );

    EXPECT_EQ(
        make_integer_value( 2 ), seqUpdateSet3->lookup( &location )->value );
}

TEST( libcasm_fe__updateset, lookupShouldReturnNullptrWhenUpdateDoesNotExist )
{
    const value_t location;

    const auto seqUpdateSet
        = std::unique_ptr< UpdateSet >( new SequentialUpdateSet( 10UL ) );

    EXPECT_EQ( nullptr, seqUpdateSet->lookup( &location ) );
}

TEST( libcasm_fe__updateset,
    parUSetsShouldThrowIfAddUpdatesWithSameKeyButDiffVal )
{
    const value_t location;

    const auto updateSet
        = std::unique_ptr< UpdateSet >( new ParallelUpdateSet( 10UL ) );
    updateSet->add( &location, new Update{.value = make_integer_value( 1 ) } );

    EXPECT_THROW( updateSet->add( &location,
                      new Update{.value = make_integer_value( 2 ) } ),
        UpdateSet::Conflict );
}

TEST( libcasm_fe__updateset,
    seqUSetsShouldOrideOldUpdatesIfAddUpdatesWithEqKeyButDiffVal )
{
    const value_t location;

    const auto updateSet
        = std::unique_ptr< UpdateSet >( new SequentialUpdateSet( 10UL ) );
    updateSet->add( &location, new Update{.value = make_integer_value( 1 ) } );
    EXPECT_NO_THROW( updateSet->add(
        &location, new Update{.value = make_integer_value( 2 ) } ) );

    EXPECT_EQ( make_integer_value( 2 ), updateSet->lookup( &location )->value );
}
