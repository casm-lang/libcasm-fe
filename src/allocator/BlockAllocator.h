//
//  Copyright (c) 2016 CASM Organization
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

#ifndef _BLOCK_ALLOCATOR_H
#define _BLOCK_ALLOCATOR_H

#include <cassert>
#include <memory>
#include <algorithm>
#include <cstdlib>

template<size_t BlockSize>
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
        explicit Block(Block* previous = nullptr) :
            m_freePosition((char*)this + sizeof(Block)),
            m_previous(previous)
        {
            if (previous) {
                previous->m_next = this;
            }
        }

        size_t remaining() const noexcept
        {
            return (char*)this + BlockSize - m_freePosition;
        }

        bool isEmpty() const noexcept
        {
            return m_usage == 0;
        }

        Block* previous() const noexcept
        {
            return m_previous;
        }

        Block* next() const noexcept
        {
            return m_next;
        }

        void *allocate(const size_t n) noexcept
        {
            assert(n <= (BlockSize - sizeof(Block)));

            const auto addr = m_freePosition;
            m_freePosition += n;
            m_usage += n;
            return addr;
        }

        /**
         * Optimized for stack-like allocation/deallocation
         */
        void deallocate(void* addr, const size_t n) noexcept
        {
            assert(n <= m_usage);

            m_usage -= n;
            if (m_usage == 0) {
                free();
            } else if (((char*)addr + n) == m_freePosition) {
                // only decrease the position if deallocation happens in reversed order
                m_freePosition -= n;
            }
        }

        void reset(void* addr) noexcept
        {
            const auto beg = (char*)this + sizeof(Block);

            m_freePosition = addr;
            m_usage = m_freePosition - beg;
        }

        void free() noexcept
        {
            const auto beg = (char*)this + sizeof(Block);

            m_usage = 0;
            m_freePosition = beg;
        }

    private:
        size_t m_usage = 0;
        char* m_freePosition;
        Block* m_next = nullptr;
        Block* m_previous;
    };

public:
    BlockAllocator()
    {
        static_assert(BlockSize > sizeof(Block), "block size must be larger than the management information of the block");
        static_assert((BlockSize & (BlockSize - 1)) == 0, "block size must be a power of two");
    }

    virtual ~BlockAllocator()
    {
        for (auto block = m_topBlock; block != nullptr; block = block->previous()) {
            free(block);
        }
    }

    void* allocate(const size_t n)
    {
        if (n > (BlockSize - sizeof(Block))) {
            throw std::length_error("requested size was larger than the block size");
        }

        if (m_currentBlock == nullptr) {
            m_currentBlock = allocateNewBlock();
        } else if (m_currentBlock->remaining() < n) {
            if (m_currentBlock->next()) {
                m_currentBlock = m_currentBlock->next();
            } else {
                m_currentBlock = allocateNewBlock();
            }
        }

        return m_currentBlock->allocate(n);
    }

    void deallocate(void* addr, const size_t n)
    {
        const auto block = blockFor(addr);
        block->deallocate(addr, n);

        if (block == m_currentBlock) {
            while (m_currentBlock->isEmpty() && m_currentBlock->previous()) {
                m_currentBlock = m_currentBlock->previous();
            }
        }
    }

    /**
     * Resets the stack top position to the given address \a addr.
     *
     * @note Use this method only if you use this allocator as a stack allocator!
     */
    void reset(void* addr)
    {
        m_currentBlock = blockFor(addr);
        m_currentBlock->reset(addr);

        // free subsequent blocks
        for (auto block = m_currentBlock->next(); block != nullptr; block = block->next()) {
            block->free();
        }
    }

    void freeAll()
    {
        for (auto block = m_topBlock; block != nullptr; block = block->previous()) {
            block->free();
        }

        m_currentBlock = m_topBlock;
    }

private:
    Block* allocateNewBlock()
    {
        const auto memory = aligned_alloc(BlockSize, BlockSize);
        const auto block = new(memory) Block(m_topBlock);
        m_topBlock = block;
        return block;
    }

    /**
     * Uses the fact that all blocks are BlockSize-aligned and the BlockSize is 2^n
     */
    static Block* blockFor(void* addr)
    {
        return reinterpret_cast<Block*>(reinterpret_cast<uintptr_t>(addr) & ~reinterpret_cast<uintptr_t>(BlockSize - 1));
    }

private:
    Block* m_topBlock = nullptr; // used in allocateNewBlock to build a linked list
    Block* m_currentBlock = nullptr;
};

#endif // BLOCK_ALLOCATOR_H

//
//  Local variables:
//  mode: c++
//  indent-tabs-mode: nil
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//
