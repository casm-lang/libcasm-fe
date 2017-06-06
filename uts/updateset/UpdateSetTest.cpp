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

#include "execute/UpdateSet.h"

struct UpdateSetDetails
{
    using Location = std::size_t;
    using Value = std::string;
    using LocationHash = std::hash< std::size_t >;
    using LocationEquals = std::equal_to< std::size_t >;
    using ValueEquals = std::equal_to< std::string >;
};

using TestUpdateSet = UpdateSet< UpdateSetDetails >;

TEST( UpdateSetTest,
    forkedParallelUpdateSetShouldBeSequentialWhenRequestingSequential )
{
    const auto updateSet = std::unique_ptr< TestUpdateSet >(
        new ParallelUpdateSet< UpdateSetDetails >( 10UL ) );
    const auto forkedUpdateSet = std::unique_ptr< TestUpdateSet >(
        updateSet->fork( TestUpdateSet::Semantics::Sequential, 10UL ) );
    EXPECT_EQ(
        TestUpdateSet::Semantics::Sequential, forkedUpdateSet->semantics() );
}

TEST( UpdateSetTest,
    forkedParallelUpdateSetShouldBeParallelWhenRequestingParallel )
{
    const auto updateSet = std::unique_ptr< TestUpdateSet >(
        new ParallelUpdateSet< UpdateSetDetails >( 10UL ) );
    const auto forkedUpdateSet = std::unique_ptr< TestUpdateSet >(
        updateSet->fork( TestUpdateSet::Semantics::Parallel, 10UL ) );
    EXPECT_EQ(
        TestUpdateSet::Semantics::Parallel, forkedUpdateSet->semantics() );
}

TEST( UpdateSetTest,
    forkedSequentialUpdateSetShouldBeParallelWhenRequestingParallel )
{
    const auto updateSet = std::unique_ptr< TestUpdateSet >(
        new SequentialUpdateSet< UpdateSetDetails >( 10UL ) );
    const auto forkedUpdateSet = std::unique_ptr< TestUpdateSet >(
        updateSet->fork( TestUpdateSet::Semantics::Parallel, 10UL ) );
    EXPECT_EQ(
        TestUpdateSet::Semantics::Parallel, forkedUpdateSet->semantics() );
}

TEST( UpdateSetTest,
    forkedSequentialUpdateSetShouldBeSequentialWhenRequestingSequential )
{
    const auto updateSet = std::unique_ptr< TestUpdateSet >(
        new SequentialUpdateSet< UpdateSetDetails >( 10UL ) );
    const auto forkedUpdateSet = std::unique_ptr< TestUpdateSet >(
        updateSet->fork( TestUpdateSet::Semantics::Sequential, 10UL ) );
    EXPECT_EQ(
        TestUpdateSet::Semantics::Sequential, forkedUpdateSet->semantics() );
}

TEST( UpdateSetTest,
    mergeParallelUpdateSetsIntoSequentialShouldOverwriteLocationValues )
{
    const std::size_t location = 42UL;

    const auto seqUpdateSet = std::unique_ptr< TestUpdateSet >(
        new SequentialUpdateSet< UpdateSetDetails >( 10UL ) );
    seqUpdateSet->add( location, "update 1" );

    const auto parUpdateSet = std::unique_ptr< TestUpdateSet >(
        seqUpdateSet->fork( TestUpdateSet::Semantics::Parallel, 10UL ) );
    parUpdateSet->add( location, "update 2" );

    parUpdateSet->merge();

    EXPECT_EQ( "update 2", seqUpdateSet->lookup( location ).value() );
}

TEST( UpdateSetTest, mergeUpdateSetsIntoEmptyUpdateSetsShouldSwapValues )
{
    const auto seqUpdateSet = std::unique_ptr< TestUpdateSet >(
        new SequentialUpdateSet< UpdateSetDetails >( 10UL ) );

    const auto parUpdateSet = std::unique_ptr< TestUpdateSet >(
        seqUpdateSet->fork( TestUpdateSet::Semantics::Parallel, 10UL ) );
    parUpdateSet->add( 1UL, "1000" );
    parUpdateSet->add( 2UL, "2000" );
    parUpdateSet->add( 3UL, "3000" );

    ASSERT_TRUE( seqUpdateSet->empty() );
    ASSERT_EQ( 3, parUpdateSet->size() );

    parUpdateSet->merge();

    EXPECT_TRUE( parUpdateSet->empty() );
    EXPECT_EQ( 3, seqUpdateSet->size() );
}

TEST( UpdateSetTest,
    mergeSequentialUpdateSetsIntoParallelShouldNotThrowWhenOverwritingSameLocationWithSameValue )
{
    const std::size_t location = 42UL;

    const auto parUpdateSet = std::unique_ptr< TestUpdateSet >(
        new ParallelUpdateSet< UpdateSetDetails >( 10UL ) );
    parUpdateSet->add( location, "update 1" );

    const auto seqUpdateSet = std::unique_ptr< TestUpdateSet >(
        parUpdateSet->fork( TestUpdateSet::Semantics::Sequential, 10UL ) );
    seqUpdateSet->add( location, "update 1" );

    EXPECT_NO_THROW( seqUpdateSet->merge() );
}

TEST( UpdateSetTest,
    mergeSequentialUpdateSetsIntoParallelShouldThrowWhenOverwritingSameLocationWithDifferentValue )
{
    const std::size_t location = 42UL;

    const auto parUpdateSet = std::unique_ptr< TestUpdateSet >(
        new ParallelUpdateSet< UpdateSetDetails >( 10UL ) );
    parUpdateSet->add( location, "update 1" );

    const auto seqUpdateSet = std::unique_ptr< TestUpdateSet >(
        parUpdateSet->fork( TestUpdateSet::Semantics::Sequential, 10UL ) );
    seqUpdateSet->add( location, "update 2" );

    EXPECT_THROW( seqUpdateSet->merge(), TestUpdateSet::Conflict );
}

TEST( UpdateSetTest, lookupShouldPreferUpdatesOfCurrentUpdateSet )
{
    const std::size_t location = 42UL;

    const auto seqUpdateSet1 = std::unique_ptr< TestUpdateSet >(
        new SequentialUpdateSet< UpdateSetDetails >( 10UL ) );
    seqUpdateSet1->add( location, "update 1" );

    const auto parUpdateSet = std::unique_ptr< TestUpdateSet >(
        seqUpdateSet1->fork( TestUpdateSet::Semantics::Parallel, 10UL ) );

    const auto seqUpdateSet2 = std::unique_ptr< TestUpdateSet >(
        parUpdateSet->fork( TestUpdateSet::Semantics::Sequential, 10UL ) );
    seqUpdateSet2->add( location, "update 2" ); // winner

    EXPECT_EQ( "update 2", seqUpdateSet2->lookup( location ).value() );
}

TEST( UpdateSetTest, lookupShouldConsiderAllSequentialParentUpdateSets )
{
    const std::size_t location = 42UL;

    const auto seqUpdateSet1 = std::unique_ptr< TestUpdateSet >(
        new SequentialUpdateSet< UpdateSetDetails >( 10UL ) );
    seqUpdateSet1->add( location, "update 1" );

    const auto parUpdateSet1 = std::unique_ptr< TestUpdateSet >(
        seqUpdateSet1->fork( TestUpdateSet::Semantics::Parallel, 10UL ) );

    const auto seqUpdateSet2 = std::unique_ptr< TestUpdateSet >(
        parUpdateSet1->fork( TestUpdateSet::Semantics::Sequential, 10UL ) );
    seqUpdateSet2->add( location, "update 2" ); // winner

    const auto parUpdateSet2 = std::unique_ptr< TestUpdateSet >(
        seqUpdateSet2->fork( TestUpdateSet::Semantics::Parallel, 10UL ) );
    parUpdateSet2->add( location, "update 3" );

    const auto seqUpdateSet3 = std::unique_ptr< TestUpdateSet >(
        parUpdateSet2->fork( TestUpdateSet::Semantics::Sequential, 10UL ) );

    EXPECT_EQ( "update 2", seqUpdateSet3->lookup( location ).value() );
}

TEST( UpdateSetTest, lookupShouldReturnEmptyOptionalWhenUpdateDoesNotExist )
{
    const auto seqUpdateSet = std::unique_ptr< TestUpdateSet >(
        new SequentialUpdateSet< UpdateSetDetails >( 10UL ) );

    EXPECT_THROW( seqUpdateSet->lookup( 42UL ).value(),
        std::experimental::bad_optional_access );
}

TEST( UpdateSetTest,
    parallelUpdateSetsShouldThrowIfAddingUpdatesWithSameLocationButDifferentValue )
{
    const std::size_t location = 42UL;

    const auto updateSet = std::unique_ptr< TestUpdateSet >(
        new ParallelUpdateSet< UpdateSetDetails >( 10UL ) );
    updateSet->add( location, "update 1" );

    EXPECT_THROW(
        updateSet->add( location, "update 2" ), TestUpdateSet::Conflict );
}

TEST( UpdateSetTest,
    sequentialUpdateSetsShouldOverwriteOldUpdatesIfAddingUpdatesWithSameLocationButDifferentValue )
{
    const std::size_t location = 42UL;

    const auto updateSet = std::unique_ptr< TestUpdateSet >(
        new SequentialUpdateSet< UpdateSetDetails >( 10UL ) );
    updateSet->add( location, "update 1" );
    EXPECT_NO_THROW( updateSet->add( location, "update 2" ) );

    EXPECT_EQ( "update 2", updateSet->lookup( location ).value() );
}
