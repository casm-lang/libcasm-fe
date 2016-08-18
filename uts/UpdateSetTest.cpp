//
//  Copyright (c) 2014-2016 CASM Organization
//  All rights reserved.
//
//  Developed by: Florian Hahn
//                Philipp Paulweber
//                Emmanuel Pescosta
//                https://github.com/ppaulweber/libcasm-fe
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

static value_t make_integer_value(INTEGER_T v)
{
    return value_t(v);
}

TEST(UpdateSetTest, forkedParallelUpdateSetShouldBeSequentialWhenRequestingSequential) {
    const auto updateSet = std::unique_ptr<UpdateSet>(new UpdateSet(UpdateSet::Type::Parallel));
    const auto forkedUpdateSet = std::unique_ptr<UpdateSet>(updateSet->fork(UpdateSet::Type::Sequential));
    EXPECT_EQ(UpdateSet::Type::Sequential, forkedUpdateSet->type());
}

TEST(UpdateSetTest, forkedParallelUpdateSetShouldBeParallelWhenRequestingParallel) {
    const auto updateSet = std::unique_ptr<UpdateSet>(new UpdateSet(UpdateSet::Type::Parallel));
    const auto forkedUpdateSet = std::unique_ptr<UpdateSet>(updateSet->fork(UpdateSet::Type::Parallel));
    EXPECT_EQ(UpdateSet::Type::Parallel, forkedUpdateSet->type());
}

TEST(UpdateSetTest, forkedSequentialUpdateSetShouldBeParallelWhenRequestingParallel) {
    const auto updateSet = std::unique_ptr<UpdateSet>(new UpdateSet(UpdateSet::Type::Sequential));
    const auto forkedUpdateSet = std::unique_ptr<UpdateSet>(updateSet->fork(UpdateSet::Type::Parallel));
    EXPECT_EQ(UpdateSet::Type::Parallel, forkedUpdateSet->type());
}

TEST(UpdateSetTest, forkedSequentialUpdateSetShouldBeSequentialWhenRequestingSequential) {
    const auto updateSet = std::unique_ptr<UpdateSet>(new UpdateSet(UpdateSet::Type::Sequential));
    const auto forkedUpdateSet = std::unique_ptr<UpdateSet>(updateSet->fork(UpdateSet::Type::Sequential));
    EXPECT_EQ(UpdateSet::Type::Sequential, forkedUpdateSet->type());
}

TEST(UpdateSetTest, mergingParallelUpdateSetsIntoSequentialOnesShouldOverrideLocationValues) {
    const auto seqUpdateSet = std::unique_ptr<UpdateSet>(new UpdateSet(UpdateSet::Type::Sequential));
    seqUpdateSet->add(1, new Update{.value = make_integer_value(10)});

    const auto parUpdateSet = std::unique_ptr<UpdateSet>(seqUpdateSet->fork(UpdateSet::Type::Parallel));
    parUpdateSet->add(1, new Update{.value = make_integer_value(1000)});

    parUpdateSet->merge();

    EXPECT_EQ(make_integer_value(1000), seqUpdateSet->lookup(1)->value);
}

TEST(UpdateSetTest, mergingUpdateSetsIntoEmptyUpdateSetsShouldSwapValues) {
    const auto seqUpdateSet = std::unique_ptr<UpdateSet>(new UpdateSet(UpdateSet::Type::Sequential));

    const auto parUpdateSet = std::unique_ptr<UpdateSet>(seqUpdateSet->fork(UpdateSet::Type::Parallel));
    parUpdateSet->add(1, new Update{.value = make_integer_value(1000)});
    parUpdateSet->add(2, new Update{.value = make_integer_value(2000)});
    parUpdateSet->add(3, new Update{.value = make_integer_value(3000)});

    ASSERT_TRUE(seqUpdateSet->empty());
    ASSERT_EQ(3, parUpdateSet->size());

    parUpdateSet->merge();

    EXPECT_TRUE(parUpdateSet->empty());
    EXPECT_EQ(3, seqUpdateSet->size());
}

TEST(UpdateSetTest, mergingSequentialUpdateSetsIntoParallelOnesShouldNotThrowWhenOverridingLocationValuesWithSameValues) {
    const auto parUpdateSet = std::unique_ptr<UpdateSet>(new UpdateSet(UpdateSet::Type::Parallel));
    parUpdateSet->add(1, new Update{.value = make_integer_value(10)});

    const auto seqUpdateSet = std::unique_ptr<UpdateSet>(parUpdateSet->fork(UpdateSet::Type::Sequential));
    seqUpdateSet->add(1, new Update{.value = make_integer_value(10)});

    EXPECT_NO_THROW(seqUpdateSet->merge());
}

TEST(UpdateSetTest, mergingSequentialUpdateSetsIntoParallelOnesShouldThrowWhenOverridingLocationValuesWithDifferentValues) {
    const auto parUpdateSet = std::unique_ptr<UpdateSet>(new UpdateSet(UpdateSet::Type::Parallel));
    parUpdateSet->add(1, new Update{.value = make_integer_value(10)});

    const auto seqUpdateSet = std::unique_ptr<UpdateSet>(parUpdateSet->fork(UpdateSet::Type::Sequential));
    seqUpdateSet->add(1, new Update{.value = make_integer_value(1000)});

    EXPECT_THROW(seqUpdateSet->merge(), UpdateSet::Conflict);
}

TEST(UpdateSetTest, lookupShouldPreferUpdatesOfCurrentUpdateSet) {
    const auto seqUpdateSet1 = std::unique_ptr<UpdateSet>(new UpdateSet(UpdateSet::Type::Sequential));
    seqUpdateSet1->add(1, new Update{.value = make_integer_value(1)});

    const auto parUpdateSet = std::unique_ptr<UpdateSet>(seqUpdateSet1->fork(UpdateSet::Type::Parallel));

    const auto seqUpdateSet2 = std::unique_ptr<UpdateSet>(parUpdateSet->fork(UpdateSet::Type::Sequential));
    seqUpdateSet2->add(1, new Update{.value = make_integer_value(2)}); // winner

    EXPECT_EQ(make_integer_value(2), seqUpdateSet2->lookup(1)->value);
}

TEST(UpdateSetTest, lookupShouldConsiderAllSequentialParentUpdateSets) {
    const auto seqUpdateSet1 = std::unique_ptr<UpdateSet>(new UpdateSet(UpdateSet::Type::Sequential));
    seqUpdateSet1->add(1, new Update{.value = make_integer_value(1)});

    const auto parUpdateSet1 = std::unique_ptr<UpdateSet>(seqUpdateSet1->fork(UpdateSet::Type::Parallel));

    const auto seqUpdateSet2 = std::unique_ptr<UpdateSet>(parUpdateSet1->fork(UpdateSet::Type::Sequential));
    seqUpdateSet2->add(1, new Update{.value = make_integer_value(2)}); // winner

    const auto parUpdateSet2 = std::unique_ptr<UpdateSet>(seqUpdateSet2->fork(UpdateSet::Type::Parallel));
    parUpdateSet2->add(1, new Update{.value = make_integer_value(0)});

    const auto seqUpdateSet3 = std::unique_ptr<UpdateSet>(parUpdateSet2->fork(UpdateSet::Type::Sequential));

    EXPECT_EQ(make_integer_value(2), seqUpdateSet3->lookup(1)->value);
}

TEST(UpdateSetTest, lookupShouldReturnNullptrWhenUpdateDoesNotExist) {
    const auto seqUpdateSet = std::unique_ptr<UpdateSet>(new UpdateSet(UpdateSet::Type::Sequential));

    EXPECT_EQ(nullptr, seqUpdateSet->lookup(1));
}

TEST(UpdateSetTest, parallelUpdateSetsShouldThrowIfAddingUpdatesWithSameKeyButDifferentValues) {
    const auto updateSet = std::unique_ptr<UpdateSet>(new UpdateSet(UpdateSet::Type::Parallel));
    updateSet->add(1, new Update{.value = make_integer_value(1)});
    EXPECT_THROW(updateSet->add(1, new Update{.value = make_integer_value(2)}), UpdateSet::Conflict);
}

TEST(UpdateSetTest, sequentialUpdateSetsShouldOverrideOldUpdatesIfAddingUpdatesWithSameKeyButDifferentValues) {
    const auto updateSet = std::unique_ptr<UpdateSet>(new UpdateSet(UpdateSet::Type::Sequential));
    updateSet->add(1, new Update{.value = make_integer_value(1)});
    EXPECT_NO_THROW(updateSet->add(1, new Update{.value = make_integer_value(2)}));

    EXPECT_EQ(make_integer_value(2), updateSet->lookup(1)->value);
}

TEST(UpdateSetManagerTest, lookupShouldReturnNullptrWhenNoUpdateSetExists) {
  auto manager = std::unique_ptr<UpdateSetManager>(new UpdateSetManager());

  EXPECT_EQ(nullptr, manager->lookup(1));
}

TEST(UpdateSetManagerTest, forkAndMerge) {
    auto manager = std::unique_ptr<UpdateSetManager>(new UpdateSetManager());

    manager->fork(UpdateSet::Type::Parallel);

    manager->add(1, new Update);
    manager->add(2, new Update);

    EXPECT_EQ(manager->currentUpdateSet()->size(), 2);
    EXPECT_EQ(manager->size(), 1);

    {
        manager->fork(UpdateSet::Type::Sequential);

        manager->add(3, new Update);
        manager->add(4, new Update);

        EXPECT_EQ(manager->currentUpdateSet()->size(), 2);
        EXPECT_EQ(manager->size(), 2);

        manager->merge();
    }

    EXPECT_EQ(manager->currentUpdateSet()->size(), 4);
    EXPECT_EQ(manager->size(), 1);
}
