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

#ifndef _LIB_CASMFE_CHAINEDHASHMAP_H_
#define _LIB_CASMFE_CHAINEDHASHMAP_H_

#include <functional>
#include <cstring>

#include "../allocator/BlockAllocator.h"

template <typename Key, typename Value,
          typename Hash = std::hash<Key>,
          typename Pred = std::equal_to<Key>>
class ChainedHashMap
{
private:
    struct Entry
    {
        Key key;
        Value value;
        std::size_t hashCode;
        Entry* next; // conflict chain
        Entry* prev; // linked-list for iterating

        Entry(const Key& key, const Value& value, std::size_t hashCode, Entry* prev) :
            key(key),
            value(value),
            hashCode(hashCode),
            next(nullptr),
            prev(prev)
        {

        }
    };

    struct Bucket
    {
        Entry* entry;

        inline void insert(Entry* newEntry)
        {
            newEntry->next = entry;
            entry = newEntry;
        }
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
    explicit ChainedHashMap() :
        ChainedHashMap(1UL)
    {

    }

    explicit ChainedHashMap(std::size_t initialCapacity) :
        m_buckets(nullptr),
        m_lastEntry(nullptr),
        m_size(0UL),
        m_capacity(std::max(nextPowerOfTwo(initialCapacity), 1UL))
    {

    }

    ChainedHashMap(ChainedHashMap&& other) :
        m_buckets(nullptr),
        m_lastEntry(other.m_lastEntry),
        m_size(other.m_size),
        m_capacity(other.m_capacity)
    {
        std::swap(m_buckets, other.m_buckets);
        std::swap(m_entryAllocator, other.m_entryAllocator);
    }

    ChainedHashMap& operator=(ChainedHashMap&& other) noexcept
    {
        std::swap(m_buckets, other.m_buckets);
        m_lastEntry = other.m_lastEntry;
        m_size = other.m_size;
        m_capacity = other.m_capacity;
        std::swap(m_entryAllocator, other.m_entryAllocator);
        return *this;
    }

    ~ChainedHashMap()
    {
        if (m_buckets) {
            delete[] m_buckets;
        }
    }

    constexpr bool empty() const noexcept
    {
        return m_size == 0UL;
    }

    constexpr std::size_t size() const noexcept
    {
        return m_size;
    }

    constexpr std::size_t capacity() const noexcept
    {
        return m_capacity;
    }

    constexpr float loadFactor() const noexcept
    {
        return (float)size() / (float)capacity();
    }

    constexpr float maximumLoadFactor() const noexcept
    {
        return 1.0f;
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
        const auto hashCode = hashCodeOf(key);
        auto entry = searchEntry(key, hashCode);
        if (entry) {
            return std::make_pair(const_iterator(entry), false);
        } else {
            growIfNecessary();

            entry = createEntry(key, value, hashCode);
            auto bucket = bucketAt(hashCode);
            bucket->insert(entry);

            return std::make_pair(const_iterator(entry), true);
        }
    }

    void insertOrAssign(const Key& key, const Value& value)
    {
        const auto hashCode = hashCodeOf(key);
        auto entry = searchEntry(key, hashCode);
        if (entry) {
            entry->value = value;
        } else {
            growIfNecessary();

            entry = createEntry(key, value, hashCode);
            auto bucket = bucketAt(hashCode);
            bucket->insert(entry);
        }
    }

    const Value& get(const Key& key) const
    {
        const auto hashCode = hashCodeOf(key);
        const auto entry = searchEntry(key, hashCode);
        if (entry) {
            return entry->value;
        } else {
            throw std::out_of_range("key not found");
        }
    }

    const_iterator find(const Key& key) const noexcept
    {
        const auto hashCode = hashCodeOf(key);
        const auto entry = searchEntry(key, hashCode);
        return const_iterator(entry);
    }

    bool hasKey(const Key& key) const noexcept
    {
        const auto hashCode = hashCodeOf(key);
        const auto entry = searchEntry(key, hashCode);
        return entry != nullptr;
    }

    void reserve(std::size_t n)
    {
        if (n > m_capacity) {
            if (m_buckets) {
                resize(nextPowerOfTwo(n));
            } else {
                m_capacity = nextPowerOfTwo(n);
            }
        }
    }

private:
    std::size_t hashCodeOf(const Key& key) const noexcept
    {
        static Hash hasher;
        return hasher(key);
    }

    constexpr Bucket* bucketAt(std::size_t hash) const noexcept
    {
        return m_buckets + (hash & (m_capacity - 1));
    }

    Entry* searchEntry(const Key& key, const std::size_t hashCode) const
    {
        static Pred equals;

        if (m_buckets) {
            const Bucket* bucket = bucketAt(hashCode);

            for (Entry* entry = bucket->entry; entry != nullptr; entry = entry->next) {
                if ((entry->hashCode == hashCode) and equals(entry->key, key)) {
                    return entry;
                }
            }
        }

        return nullptr;
    }

    Entry* createEntry(const Key& key, const Value& value, std::size_t hashCode)
    {
        const auto memory = m_entryAllocator.allocate(sizeof(Entry));
        const auto entry = new(memory) Entry(key, value, hashCode, m_lastEntry);

        m_lastEntry = entry;
        ++m_size;

        return entry;
    }

    void resize(std::size_t newCapacity)
    {
        assert(isPowerOfTwo(newCapacity));
        m_capacity = newCapacity;

        if (m_buckets) {
            delete[] m_buckets;
        }
        m_buckets = new Bucket[newCapacity];
        std::memset(m_buckets, 0, sizeof(Bucket) * newCapacity);

        for (auto entry = m_lastEntry; entry != nullptr; entry = entry->prev) {
            auto bucket = bucketAt(entry->hashCode);
            bucket->insert(entry);
        }
    }

    void growIfNecessary()
    {
        if (m_buckets == nullptr) {
            resize(m_capacity);
        } else if (m_size == m_capacity) {
            resize(m_capacity * 2);
        }
        assert(m_size < m_capacity);
    }

    std::size_t nextPowerOfTwo(std::size_t n) const noexcept
    {
        n -= 1;
        n |= (n >> 1);
        n |= (n >> 2);
        n |= (n >> 4);
        n |= (n >> 8);
        n |= (n >> 16);
#if __SIZEOF_SIZE_T__ > 4
        n |= (n >> 32);
#endif
        return n + 1;
    }

    constexpr bool isPowerOfTwo(std::size_t n) const noexcept
    {
        return ((n != 0) && !(n & (n - 1)));
    }

private:
    Bucket* m_buckets;
    Entry* m_lastEntry;

    std::size_t m_size;
    std::size_t m_capacity;

    BlockAllocator<4096> m_entryAllocator;
};

#endif // _LIB_CASMFE_CHAINEDHASHMAP_H_

//
//  Local variables:
//  mode: c++
//  indent-tabs-mode: nil
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//
