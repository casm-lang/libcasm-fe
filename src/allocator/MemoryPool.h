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

#ifndef _MEMORY_POOL_H
#define _MEMORY_POOL_H

#include <cstdlib>
#include <memory>

template < size_t BlockSize >
class MemoryPool
{
    union Block {
        char memory[ BlockSize ];
        Block* next; // to build a list of free blocks when block is released
    };
    static_assert( BlockSize == sizeof( Block ), "Block has wrong size" );

  public:
    /**
     * Allocates a block of memory.
     *
     * @return a pointer to the allocated memory or nullptr if the request fails
     */
    void* get()
    {
        if( m_nextFreeBlock )
        {
            const auto block = m_nextFreeBlock;
            m_nextFreeBlock = block->next;
            return reinterpret_cast< void* >( block );
        }
        else
        {
            return aligned_alloc( BlockSize, BlockSize );
        }
    }

    /**
     * Frees the previously allocated memory.
     *
     * Does nothing if \a memory is a nullptr.
     *
     * @param memory A pointer to allocated memory
     */
    void release( void* memory ) noexcept
    {
        if( memory )
        {
            const auto block = reinterpret_cast< Block* >( memory );
            block->next = m_nextFreeBlock;
            m_nextFreeBlock = block;
        }
    }

    static MemoryPool& instance()
    {
        static MemoryPool instance;
        return instance;
    }

  private:
    MemoryPool() = default;
    MemoryPool( const MemoryPool& ) = delete;
    MemoryPool& operator=( const MemoryPool& ) = delete;
    MemoryPool( MemoryPool&& ) = delete;
    MemoryPool& operator=( MemoryPool&& ) = delete;

  private:
    Block* m_nextFreeBlock = nullptr; // linked list of free memory blocks
};

#endif // _MEMORY_POOL_H

//
//  Local variables:
//  mode: c++
//  indent-tabs-mode: nil
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//
