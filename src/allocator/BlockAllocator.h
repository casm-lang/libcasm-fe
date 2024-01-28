//
//  Copyright (C) 2014-2024 CASM Organization <https://casm-lang.org>
//  All rights reserved.
//
//  Developed by: Philipp Paulweber et al.
//  <https://github.com/casm-lang/libcasm-fe/graphs/contributors>
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

#ifndef _BLOCK_ALLOCATOR_H
#define _BLOCK_ALLOCATOR_H

#include <libcasm-fe/allocator/MemoryPool>

#include <algorithm>
#include <cassert>
#include <stdexcept>

template < size_t BlockSize >
class BlockAllocator
{
    /**
     * The block memory consists of management information and user data.
     * - The size of the management information is sizeof(Block)
     * - The size of the user data is the remaining BlockSize
     */
    class Block
    {
      public:
        explicit Block( Block* previous = nullptr )
        : m_freePosition( (char*)this + sizeof( Block ) )
        , m_previous( previous )
        {
        }

        size_t remaining() const noexcept
        {
            return (char*)this + BlockSize - m_freePosition;
        }

        Block* previous() const noexcept
        {
            return m_previous;
        }

        void* allocate( const size_t n ) noexcept
        {
            assert( n <= ( BlockSize - sizeof( Block ) ) );

            const auto addr = m_freePosition;
            m_freePosition += n;
            return addr;
        }

        void reset( void* addr ) noexcept
        {
            assert(
                ( ( (char*)this + sizeof( Block ) ) <= addr ) and
                ( addr <= ( (char*)this + BlockSize ) ) );

            m_freePosition = (char*)addr;
        }

        void free() noexcept
        {
            m_freePosition = (char*)this + sizeof( Block );
        }

      private:
        Block( const Block& ) = delete;
        Block& operator=( const Block& ) = delete;
        Block( Block&& ) = delete;
        Block& operator=( Block&& ) = delete;

      private:
        char* m_freePosition;
        Block* m_previous;
    };

  public:
    BlockAllocator()
    {
        static_assert(
            BlockSize > sizeof( Block ),
            "block size must be larger than the management information of the "
            "block" );
        static_assert(
            ( BlockSize & ( BlockSize - 1 ) ) == 0, "block size must be a power of two" );
    }

    BlockAllocator( BlockAllocator&& other )
    {
        std::swap( m_topBlock, other.m_topBlock );
    }

    ~BlockAllocator()
    {
        freeAll();
    }

    BlockAllocator& operator=( BlockAllocator&& other ) noexcept
    {
        std::swap( m_topBlock, other.m_topBlock );
        return *this;
    }

    void* allocate( const size_t n )
    {
        if( n > ( BlockSize - sizeof( Block ) ) )
        {
            throw std::length_error( "requested size was larger than the block size" );
        }

        if( ( m_topBlock == nullptr ) or ( m_topBlock->remaining() < n ) )
        {
            m_topBlock = allocateNewBlock();
        }

        return m_topBlock->allocate( n );
    }

    /**
     * Resets the stack top position to the given address \a addr.
     *
     * @note Use this method only if you use this allocator as a stack
     * allocator!
     */
    void reset( void* addr )
    {
        const auto currentBlock = blockFor( addr );
        currentBlock->reset( addr );

        // free subsequent blocks
        for( auto block = m_topBlock; block != currentBlock; )
        {
            const auto b = block;
            block = block->previous();
            MemoryPool< BlockSize >::instance().release( b );
        }

        m_topBlock = currentBlock;
    }

    void freeAll()
    {
        for( auto block = m_topBlock; block != nullptr; )
        {
            const auto b = block;
            block = block->previous();
            MemoryPool< BlockSize >::instance().release( b );
        }

        m_topBlock = nullptr;
    }

  private:
    BlockAllocator( const BlockAllocator& ) = delete;
    BlockAllocator& operator=( const BlockAllocator& ) = delete;

    Block* allocateNewBlock() const
    {
        const auto memory = MemoryPool< BlockSize >::instance().get();
        const auto block = new( memory ) Block( m_topBlock );
        return block;
    }

    /**
     * Uses the fact that all blocks are BlockSize-aligned and the BlockSize is
     * 2^n
     */
    static Block* blockFor( void* addr )
    {
        return reinterpret_cast< Block* >(
            reinterpret_cast< uintptr_t >( addr ) &
            ~reinterpret_cast< uintptr_t >( BlockSize - 1 ) );
    }

  private:
    Block* m_topBlock = nullptr;
};

#endif  // BLOCK_ALLOCATOR_H

//
//  Local variables:
//  mode: c++
//  indent-tabs-mode: nil
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//
