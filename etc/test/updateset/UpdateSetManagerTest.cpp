//
//  Copyright (C) 2014-2019 CASM Organization <https://casm-lang.org>
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

#include <memory>

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
        manager = libstdhl::Memory::make_unique< UpdateSetManager< TestUpdateSet > >();
    }

    std::unique_ptr< UpdateSetManager< TestUpdateSet > > manager;
};

TEST_F( UpdateSetManagerTest, lookupShouldReturnEmptyOptionalWhenNoUpdateSetExists )
{
    EXPECT_THROW( manager->lookup( 42UL ).value(), std::logic_error );
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
