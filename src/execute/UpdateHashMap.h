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
        std::size_t hash;
        Entry* next; // conflict chain
        Entry* prev; // linked-list for iterating
    };

    struct Bucket
    {
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

        const auto result = searchOrInsertEntry(key, value);
        const Entry* entry = std::get<0>(result);
        const bool inserted = std::get<1>(result);
        assert(entry != nullptr);

        return std::make_pair(const_iterator(entry), inserted);
    }

    void insertOrAssign(const Key& key, const Value& value)
    {
        if (needsResizing(m_size)) {
            resize(nextPowerOfTwo(m_capacity + 1));
        }
        assert(m_size < m_capacity);

        const auto result = searchOrInsertEntry(key, value);
        Entry* entry = std::get<0>(result);
        assert(entry != nullptr);

        entry->value = value;
    }

    const Value& get(const Key& key) const
    {
        const auto entry = searchEntry(key);
        if (entry) {
            return entry->value;
        } else {
            throw std::out_of_range("key not found");
        }
    }

    const_iterator find(const Key& key) const noexcept
    {
        const auto entry = searchEntry(key);
        return const_iterator(entry ? entry : nullptr);
    }

    void reserve(size_type n)
    {
        if (needsResizing(n)) {
            resize(nextPowerOfTwo(std::max(n, m_capacity + 1)));
        }
    }

private:
    constexpr Bucket* bucketAt(size_type hash) const noexcept
    {
        return m_buckets + (hash & (m_capacity - 1));
    }

    inline std::pair<Entry*, bool> searchOrInsertEntry(const Key& key, const Value& value)
    {
        const size_type hash = hasher(key);
        Bucket* bucket = bucketAt(hash);

        for (Entry* entry = bucket->entry; entry != nullptr; entry = entry->next) {
            if ((entry->hash == hash) and equals(entry->key, key)) {
                return std::make_pair(entry, false);
            }
        }

        // entry not found, create a new one
        Entry* entry = createEntry(key, value);
        entry->hash = hash;

        entry->next = bucket->entry;
        bucket->entry = entry;

        return std::make_pair(entry, true);
    }

    inline Entry* searchEntry(const Key& key) const
    {
        const size_type hash = hasher(key);
        const Bucket* bucket = bucketAt(hash);

        for (Entry* entry = bucket->entry; entry != nullptr; entry = entry->next) {
            if ((entry->hash == hash) and equals(entry->key, key)) {
                return entry;
            }
        }

        return nullptr;
    }

    inline void insertEntry(Entry* entry) noexcept
    {
        Bucket* bucket = bucketAt(entry->hash);
        entry->next = bucket->entry;
        bucket->entry = entry;
    }

    constexpr bool needsResizing(size_type size) const noexcept
    {
        return size > m_capacity;
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
            insertEntry(entry);
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
        entry->next = nullptr;

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
