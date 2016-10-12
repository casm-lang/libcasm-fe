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

#ifndef _LIB_CASMFE_OPENHASHMAP_H_
#define _LIB_CASMFE_OPENHASHMAP_H_

#include <functional>
#include <cstring>

#include "../allocator/BlockAllocator.h"

template <typename Key, typename Value,
          typename Hash = std::hash<Key>,
          typename Pred = std::equal_to<Key>>
class OpenHashMap
{
private:
    struct Entry
    {
        Key key;
        Value value;
        Entry* prev; // linked-list

        Entry(const Key& key, const Value& value, Entry* prev) :
            key(key),
            value(value),
            prev(prev)
        {

        }
    };

    struct Bucket
    {
        std::size_t hashCode;
        Entry* entry;

        constexpr bool empty() const
        {
            return entry == nullptr;
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
    using size_type = size_t;

    explicit OpenHashMap() :
        OpenHashMap(1UL)
    {

    }

    explicit OpenHashMap(size_type initialCapacity) :
        m_buckets(nullptr),
        m_lastEntry(nullptr),
        m_size(0UL),
        m_capacity(std::max(initialCapacity, 1UL))
    {

    }

    OpenHashMap(OpenHashMap&& other) :
        m_buckets(nullptr),
        m_lastEntry(other.m_lastEntry),
        m_size(other.m_size),
        m_capacity(other.m_capacity)
    {
        std::swap(m_buckets, other.m_buckets);
        std::swap(m_entryAllocator, other.m_entryAllocator);
    }

    OpenHashMap& operator=(OpenHashMap&& other) noexcept
    {
        std::swap(m_buckets, other.m_buckets);
        m_lastEntry = other.m_lastEntry;
        m_size = other.m_size;
        m_capacity = other.m_capacity;
        std::swap(m_entryAllocator, other.m_entryAllocator);
        return *this;
    }

    ~OpenHashMap()
    {
        if (m_buckets) {
            delete[] m_buckets;
        }
    }

    constexpr bool empty() const
    {
        return m_size == 0UL;
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
        growIfNecessary();

        static Hash hasher;
        const auto hashCode = hasher(key);
        const auto bucket = searchBucketWithHashOrEmptyBucket(key, hashCode);
        assert(bucket != nullptr);

        if (bucket->empty()) {
            const auto entry = createEntry(key, value);
            bucket->entry = entry;
            bucket->hashCode = hashCode;
            return std::make_pair(const_iterator(entry), true);
        } else {
            return std::make_pair(const_iterator(bucket->entry), false);
        }
    }

    void insertOrAssign(const Key& key, const Value& value)
    {
        growIfNecessary();

        static Hash hasher;
        const auto hashCode = hasher(key);
        const auto bucket = searchBucketWithHashOrEmptyBucket(key, hashCode);
        assert(bucket != nullptr);

        if (bucket->empty()) {
            bucket->entry = createEntry(key, value);
            bucket->hashCode = hashCode;
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

    size_type count(const Key& key) const noexcept
    {
        const auto bucket = searchBucket(key);
        return bucket ? 1UL : 0UL;
    }

    void reserve(size_type n)
    {
        if (m_buckets) {
            if (needsResizing(n)) {
                const auto newMinCapacity = nextPowerOfTwo(n * 4UL / 3UL + 1UL);
                resize(std::max(newMinCapacity, m_capacity * 2));
            }
        } else {
            m_capacity = std::max(n, m_capacity);
        }
    }

private:
    constexpr inline Bucket* bucketAt(size_type hashCode, size_type probe) const noexcept
    {
        return m_buckets + ((hashCode + probe) & (m_capacity - 1));
    }

    Bucket* searchBucket(const Key& key) const noexcept
    {
        static Hash hasher;

        if (m_buckets) {
            const auto bucket = searchBucketWithHashOrEmptyBucket(key, hasher(key));
            return (bucket and not bucket->empty()) ? bucket : nullptr;
        }

        return nullptr;
    }

    Bucket* searchBucketWithHashOrEmptyBucket(const Key& key, const size_type hashCode) const noexcept
    {
        assert(m_buckets != nullptr);

        static Pred equals;

        for (size_type round = 0; round < m_capacity; round++) {
            auto bucket = bucketAt(hashCode, round);
            if (bucket->empty()) {
                return bucket;
            }
            if ((bucket->hashCode == hashCode) and equals(bucket->entry->key, key)) {
                return bucket;
            }
        }

        return nullptr;
    }

    Bucket* searchEmptyBucket(const size_type hashCode) const noexcept
    {
        assert(m_buckets != nullptr);

        for (size_type round = 0; round < m_capacity; round++) {
            auto bucket = bucketAt(hashCode, round);
            if (bucket->empty()) {
                return bucket;
            }
        }

        return nullptr;
    }

    Entry* createEntry(const Key& key, const Value& value)
    {
        const auto memory = m_entryAllocator.allocate(sizeof(Entry));
        const auto entry = new(memory) Entry(key, value, m_lastEntry);

        m_lastEntry = entry;
        ++m_size;

        return entry;
    }

    constexpr bool needsResizing(size_type size) const noexcept
    {
        return size > (m_capacity * 3UL / 4UL);
    }

    void resize(size_type newCapacity)
    {
        const auto oldCapacity = m_capacity;
        const auto oldBuckets = m_buckets;

        m_capacity = newCapacity;

        m_buckets = new Bucket[newCapacity];
        std::memset(m_buckets, 0, sizeof(Bucket) * newCapacity);

        if (oldBuckets) {
            const auto firstOldBucket = oldBuckets;
            const auto lastOldBucket = oldBuckets + oldCapacity;

            for (auto oldBucket = firstOldBucket; oldBucket != lastOldBucket; ++oldBucket) {
                if (oldBucket->empty()) {
                    continue;
                }

                const auto newBucket = searchEmptyBucket(oldBucket->hashCode);
                assert(newBucket != nullptr);
                assert(newBucket->empty());
                newBucket->entry = oldBucket->entry;
                newBucket->hashCode = oldBucket->hashCode;
            }

            delete oldBuckets;
        }
    }

    inline void growIfNecessary()
    {
        if (m_buckets == nullptr) {
            resize(nextPowerOfTwo(m_capacity * 2)); // initial resize
        } else if (needsResizing(m_size)) {
            resize(m_capacity * 2);
        }
        assert(m_size < m_capacity);
    }

    size_type nextPowerOfTwo(size_type n) const noexcept
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

private:
    Bucket* m_buckets;
    Entry* m_lastEntry;

    size_type m_size;
    size_type m_capacity;

    BlockAllocator<4096> m_entryAllocator;
};

#endif // _LIB_CASMFE_OPENHASHMAP_H_

//
//  Local variables:
//  mode: c++
//  indent-tabs-mode: nil
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//
