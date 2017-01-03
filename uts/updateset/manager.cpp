//
//  Copyright (c) 2014-2017 CASM Organization
//  All rights reserved.
//
//  Developed by: Florian Hahn
//                Philipp Paulweber
//                Emmanuel Pescosta
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

TEST( libcasm_fe__updateset_manager,
    lookupShouldReturnNullptrWhenNoUpdateSetExists )
{
    const value_t location;

    auto manager
        = std::unique_ptr< UpdateSetManager >( new UpdateSetManager() );

    EXPECT_EQ( nullptr, manager->lookup( &location ) );
}

TEST( libcasm_fe__updateset_manager, forkAndMerge )
{
    const value_t location1, location2, location3, location4;

    auto manager
        = std::unique_ptr< UpdateSetManager >( new UpdateSetManager() );

    manager->fork( UpdateSet::Type::Parallel, 10UL );

    manager->add( &location1, new Update );
    manager->add( &location2, new Update );

    EXPECT_EQ( manager->currentUpdateSet()->size(), 2 );
    EXPECT_EQ( manager->size(), 1 );

    {
        manager->fork( UpdateSet::Type::Sequential, 10UL );

        manager->add( &location3, new Update );
        manager->add( &location4, new Update );

        EXPECT_EQ( manager->currentUpdateSet()->size(), 2 );
        EXPECT_EQ( manager->size(), 2 );

        manager->merge();
    }

    EXPECT_EQ( manager->currentUpdateSet()->size(), 4 );
    EXPECT_EQ( manager->size(), 1 );
}
