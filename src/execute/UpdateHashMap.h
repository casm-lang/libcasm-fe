//
//  Copyright (c) 2014-2016 CASM Organization
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

#ifndef _LIB_CASMFE_UPDATEHASHMAP_H_
#define _LIB_CASMFE_UPDATEHASHMAP_H_

#include <functional>
#include <cstring>

#include "Update.h"
#include "../allocator/BlockAllocator.h"

template <typename Key, typename Value,
          typename Hash = std::hash<Key>,
          typename Pred = std::equal_to<Key>>
class UpdateHashMap
{
private:
    struct Entry
    {
        Key key;
        Value value;
        Entry* prev; // linked-list
    };

    struct Bucket
    {
        std::size_t hash;
        Entry* entry;
    };

public:
    class const_iterator
    {
    public:
        using difference_type = std::ptrdiff_t;
        using iterator_category = std::forward_iterator_tag;

        explicit const_iterator(const Entry* entry) :
            m_entry(entry)
        {

        }

        const_iterator(const const_iterator& rhs) :
            m_entry(rhs.m_entry)
        {

        }

        const_iterator& operator=(const const_iterator& rhs) noexcept
        {
            m_entry = rhs.m_entry;
            return *this;
        }

        bool operator==(const const_iterator& rhs) const noexcept
        {
            return m_entry == rhs.m_entry;
        }

        bool operator!=(const const_iterator& rhs) const noexcept
        {
            return m_entry != rhs.m_entry;
        }

        const_iterator& operator++() noexcept
        {
            m_entry = m_entry->prev;
            return *this;
        }

        const Key& key() const noexcept
        {
            return m_entry->key;
        }

        const Value& value() const noexcept
        {
            return m_entry->value;
        }

    private:
        const Entry* m_entry;
    };

public:
    using size_type = size_t;

    explicit UpdateHashMap(size_type initialCapacity) :
        m_buckets(nullptr),
        m_lastEntry(nullptr),
        m_size(0),
        m_capacity(0)
    {
        resize(nextPowerOfTwo(initialCapacity));
    }

    UpdateHashMap(UpdateHashMap&& other) :
        m_buckets(nullptr),
        m_lastEntry(other.m_lastEntry),
        m_size(other.m_size),
        m_capacity(other.m_capacity)
    {
        std::swap(m_buckets, other.m_buckets);
        std::swap(m_entryAllocator, other.m_entryAllocator);
    }

    UpdateHashMap& operator=(UpdateHashMap&& other) noexcept
    {
        std::swap(m_buckets, other.m_buckets);
        m_lastEntry = other.m_lastEntry;
        m_size = other.m_size;
        m_capacity = other.m_capacity;
        std::swap(m_entryAllocator, other.m_entryAllocator);
        return *this;
    }

    ~UpdateHashMap()
    {
        delete[] m_buckets;
    }

    constexpr bool empty() const
    {
        return m_size == 0;
    }

    constexpr size_type size() const
    {
        return m_size;
    }

    constexpr size_type capacity() const
    {
        return m_capacity;
    }

    constexpr const_iterator begin() const noexcept
    {
        return const_iterator(m_lastEntry);
    }

    constexpr const_iterator end() const noexcept
    {
        return const_iterator(nullptr);
    }

    std::pair<const_iterator, bool> insert(const Key& key, const Value& value)
    {
        if (needsResizing(m_size)) {
            resize(nextPowerOfTwo(m_capacity + 1));
        }
        assert(m_size < m_capacity);

        const auto bucket = searchBucketForInsertion(key);
        assert(bucket != nullptr);

        if (bucket->entry == nullptr) {
            const auto entry = createEntry(key, value);
            bucket->entry = entry;
            return std::make_pair(const_iterator(entry), true);
        } else {
            return std::make_pair(const_iterator(bucket->entry), false);
        }
    }

    void insertOrAssign(const Key& key, const Value& value)
    {
        if (needsResizing(m_size)) {
            resize(nextPowerOfTwo(m_capacity + 1));
        }
        assert(m_size < m_capacity);

        const auto bucket = searchBucketForInsertion(key);
        assert(bucket != nullptr);

        if (bucket->entry == nullptr) {
            bucket->entry = createEntry(key, value);
        } else {
            bucket->entry->value = value;
        }
    }

    const Value& get(const Key& key) const
    {
        const auto bucket = searchBucket(key);
        if (bucket) {
            return bucket->entry->value;
        } else {
            throw std::out_of_range("key not found");
        }
    }

    const_iterator find(const Key& key) const noexcept
    {
        const auto bucket = searchBucket(key);
        return const_iterator(bucket ? bucket->entry : nullptr);
    }

    void reserve(size_type n)
    {
        if (needsResizing(n)) {
            resize(nextPowerOfTwo(std::max(n, m_capacity + 1)));
        }
    }

private:
    inline Bucket* searchBucketForInsertion(const Key& key) const noexcept
    {
        const size_type hash = hasher(key);
        const size_type capacity = m_capacity;

        for (size_type round = 0; round < capacity; round++) {
            const size_type index = (hash + round) & (capacity - 1);
            Bucket* bucket = m_buckets + index;
            if (bucket->entry == nullptr) { // empty bucket
                bucket->hash = hash;
                return bucket;
            }
            if ((bucket->hash == hash) and equals(bucket->entry->key, key)) {
                return bucket;
            }
        }

        return nullptr;
    }

    inline Bucket* searchBucket(const Key& key) const noexcept
    {
        const size_type hash = hasher(key);
        const size_type capacity = m_capacity;

        for (size_type round = 0; round < capacity; round++) {
            const size_type index = (hash + round) & (capacity - 1);
            Bucket* bucket = m_buckets + index;
            if (bucket->entry == nullptr) { // empty bucket
                return nullptr;
            }
            if ((bucket->hash == hash) and equals(bucket->entry->key, key)) {
                return bucket;
            }
        }

        return nullptr;
    }

    constexpr bool needsResizing(size_type size) const noexcept
    {
        return size > (0.75f * m_capacity);
    }

    void resize(size_type newCapacity)
    {
        m_capacity = newCapacity;

        if (m_buckets) {
            delete[] m_buckets;
        }
        m_buckets = new Bucket[newCapacity]; // TODO EP: reallocate?
        std::memset(m_buckets, 0, sizeof(Bucket) * newCapacity);

        for (auto entry = m_lastEntry; entry != nullptr; entry = entry->prev) {
            const auto bucket = searchBucketForInsertion(entry->key); // TODO avoid rehashing
            assert(bucket != nullptr);
            bucket->entry = entry;
        }
    }

    inline size_type nextPowerOfTwo(size_type n) const noexcept
    {
        n -= 1;
        n |= (n >> 1);
        n |= (n >> 2);
        n |= (n >> 4);
        n |= (n >> 8);
        n |= (n >> 16);
        n |= (n >> 32);
        return n + 1;
    }

    Entry* createEntry(const Key& key, const Value& value)
    {
        Entry* entry = (Entry *)m_entryAllocator.allocate(sizeof(Entry));
        entry->key = key;
        entry->value = value;

        entry->prev = m_lastEntry;
        m_lastEntry = entry;

        ++m_size;

        return entry;
    }

private:
    static const Hash hasher;
    static const Pred equals;

    Bucket* m_buckets;
    Entry* m_lastEntry;

    size_type m_size;
    size_type m_capacity;

    BlockAllocator<4096> m_entryAllocator;
};

#endif // _LIB_CASMFE_UPDATEHASHMAP_H_

//
//  Local variables:
//  mode: c++
//  indent-tabs-mode: nil
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//
