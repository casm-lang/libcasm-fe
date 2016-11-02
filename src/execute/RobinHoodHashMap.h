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

#ifndef _LIB_CASMFE_ROBINHOODHASHMAP_H_
#define _LIB_CASMFE_ROBINHOODHASHMAP_H_

#include <functional>
#include <cstring>

#include "../allocator/BlockAllocator.h"

template <typename Key, typename Value,
          typename Hash = std::hash<Key>,
          typename Pred = std::equal_to<Key>>
class RobinHoodHashMap
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
        std::size_t distance;
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
    explicit RobinHoodHashMap() :
        RobinHoodHashMap(1UL)
    {

    }

    explicit RobinHoodHashMap(std::size_t initialCapacity) :
        m_buckets(nullptr),
        m_lastEntry(nullptr),
        m_size(0UL),
        m_capacity(std::max(initialCapacity, 1UL))
    {

    }

    RobinHoodHashMap(RobinHoodHashMap&& other) :
        m_buckets(nullptr),
        m_lastEntry(other.m_lastEntry),
        m_size(other.m_size),
        m_capacity(other.m_capacity)
    {
        std::swap(m_buckets, other.m_buckets);
        std::swap(m_entryAllocator, other.m_entryAllocator);
    }

    RobinHoodHashMap& operator=(RobinHoodHashMap&& other) noexcept
    {
        std::swap(m_buckets, other.m_buckets);
        m_lastEntry = other.m_lastEntry;
        m_size = other.m_size;
        m_capacity = other.m_capacity;
        std::swap(m_entryAllocator, other.m_entryAllocator);
        return *this;
    }

    ~RobinHoodHashMap()
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
        return 0.75f;
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

        const auto hashCode = hashCodeOf(key);
        auto entry = searchEntry(key, hashCode);
        if (entry) {
            return std::make_pair(const_iterator(entry), false);
        } else {
            entry = createEntry(key, value);
            insertEntry(entry, hashCode);
            return std::make_pair(const_iterator(entry), true);
        }
    }

    void insertOrAssign(const Key& key, const Value& value)
    {
        growIfNecessary();

        const auto hashCode = hashCodeOf(key);
        auto entry = searchEntry(key, hashCode);
        if (entry) {
            entry->value = value;
        } else {
            entry = createEntry(key, value);
            insertEntry(entry, hashCode);
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
        if (m_buckets) {
            if (needsResizing(n)) {
                resize(nextPowerOfTwo(n / maximumLoadFactor() + 1UL));
            }
        } else {
            m_capacity = std::max(n, m_capacity);
        }
    }

private:
    std::size_t hashCodeOf(const Key& key) const noexcept
    {
        static Hash hasher;
        return hasher(key);
    }

    Entry* searchEntry(const Key& key, const std::size_t hashCode) const noexcept
    {
        static Pred equals;

        const auto buckets = m_buckets;
        const auto capacity = m_capacity;
        const auto initialIndex = hashCode & (capacity - 1);

        if (buckets) {
            for (std::size_t round = 0; round < capacity; round++) {
                const auto index = (initialIndex + round) & (capacity - 1);
                auto bucket = buckets + index;
                if (bucket->empty() or (round > bucket->distance)) {
                    return nullptr;
                }
                if ((bucket->hashCode == hashCode) and equals(bucket->entry->key, key)) {
                    return bucket->entry;
                }
            }
        }

        return nullptr;
    }

    void insertEntry(Entry* entry, std::size_t hashCode) const noexcept
    {
        assert(m_buckets != nullptr);

        const auto buckets = m_buckets;
        const auto capacity = m_capacity;
        const auto initialIndex = hashCode & (capacity - 1);

        std::size_t distance = 0;

        for (std::size_t round = 0; round < capacity; round++) {
            const auto index = (initialIndex + round) & (capacity - 1);
            auto bucket = buckets + index;
            if (bucket->empty()) {
                bucket->hashCode = hashCode;
                bucket->distance = distance;
                bucket->entry = entry;
                break;
            }
            if (distance > bucket->distance) {
                std::swap(hashCode, bucket->hashCode);
                std::swap(distance, bucket->distance);
                std::swap(entry, bucket->entry);
            }
            ++distance;
        }
    }

    Entry* createEntry(const Key& key, const Value& value)
    {
        const auto memory = m_entryAllocator.allocate(sizeof(Entry));
        const auto entry = new(memory) Entry(key, value, m_lastEntry);

        m_lastEntry = entry;
        ++m_size;

        return entry;
    }

    constexpr bool needsResizing(std::size_t size) const noexcept
    {
        return size > (m_capacity * maximumLoadFactor());
    }

    void resize(std::size_t newCapacity)
    {
        const auto oldCapacity = m_capacity;
        const auto oldBuckets = m_buckets;

        assert(isPowerOfTwo(newCapacity));
        m_capacity = newCapacity;

        m_buckets = new Bucket[newCapacity];
        std::memset(m_buckets, 0, sizeof(Bucket) * newCapacity);

        if (oldBuckets) {
            const auto firstOldBucket = oldBuckets;
            const auto lastOldBucket = oldBuckets + oldCapacity;

            for (auto oldBucket = firstOldBucket; oldBucket != lastOldBucket; ++oldBucket) {
                if (not oldBucket->empty()) {
                    insertEntry(oldBucket->entry, oldBucket->hashCode);
                }
            }

            delete oldBuckets;
        }
    }

    void growIfNecessary()
    {
        if (m_buckets == nullptr) {
            resize(nextPowerOfTwo(m_capacity)); // initial resize
        } else if (needsResizing(m_size)) {
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
        n |= (n >> 32);
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

#endif // _LIB_CASMFE_ROBINHOODHASHMAP_H_

//
//  Local variables:
//  mode: c++
//  indent-tabs-mode: nil
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//
