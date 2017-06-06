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

#include "../stdhl/cpp/Default.h"

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

class UpdateSetManagerTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        manager = libstdhl::make_unique<UpdateSetManager< TestUpdateSet >>();
    }

    std::unique_ptr< UpdateSetManager< TestUpdateSet >> manager;
};

TEST_F( UpdateSetManagerTest,
    lookupShouldReturnEmptyOptionalWhenNoUpdateSetExists )
{
    // EXPECT_FALSE( manager->lookup( 42UL ).has_value() );
}

TEST_F( UpdateSetManagerTest, forkAndMerge )
{
    manager->fork( TestUpdateSet::Semantics::Parallel, 10UL );

    manager->add( 1UL, "update 1" );
    manager->add( 2UL, "update 2" );

    EXPECT_EQ( manager->currentUpdateSet()->size(), 2 );
    EXPECT_EQ( manager->size(), 1 );

    {
        manager->fork( TestUpdateSet::Semantics::Sequential, 10UL );

        manager->add( 3UL, "update 3" );
        manager->add( 4UL, "update 4" );

        EXPECT_EQ( manager->currentUpdateSet()->size(), 2 );
        EXPECT_EQ( manager->size(), 2 );

        manager->merge();
    }

    EXPECT_EQ( manager->currentUpdateSet()->size(), 4 );
    EXPECT_EQ( manager->size(), 1 );
}
