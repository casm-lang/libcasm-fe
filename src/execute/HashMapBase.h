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

#ifndef _LIB_CASMFE_HASHMAPBASE_H_
#define _LIB_CASMFE_HASHMAPBASE_H_

#include <cstring>
#include <functional>

#include "../allocator/BlockAllocator.h"

//#define HASH_MAP_PERF

namespace details
{
    /**
     * @note From Bit Twiddling Hacks
     * @see
     * https://graphics.stanford.edu/~seander/bithacks.html#RoundUpPowerOf2
     */
    std::size_t nextPowerOfTwo( std::size_t n ) noexcept;

    /**
     * @note From Bit Twiddling Hacks
     * @see
     * https://graphics.stanford.edu/~seander/bithacks.html#DetermineIfPowerOf2
     */
    constexpr bool isPowerOfTwo( std::size_t n ) noexcept
    {
        return ( ( n != 0 ) && !( n & ( n - 1 ) ) );
    }

    /**
     * Returns the next bigger prime number of \a n
     *
     * @note From GCC libstdc++
     *
     * @return Next bigger prime number (greater than \a n)
     */
    std::size_t nextPrime( std::size_t n ) noexcept;

    namespace HashingStrategy
    {
        struct PowerOfTwoHashing
        {
            static std::size_t initialSize( std::size_t size ) noexcept
            {
                return nextPowerOfTwo( size );
            }

            static std::size_t nextSize( std::size_t size ) noexcept
            {
                assert( isPowerOfTwo( size ) );
                return size * 2;
            }

            static constexpr std::size_t compress(
                std::size_t hashCode, std::size_t capacity ) noexcept
            {
                return hashCode & ( capacity - 1 );
            }
        };

        struct PrimeHashing
        {
            static std::size_t initialSize( std::size_t size ) noexcept
            {
                return nextPrime( size );
            }

            static std::size_t nextSize( std::size_t size ) noexcept
            {
                return nextPrime( size * 2 );
            }

            static constexpr std::size_t compress(
                std::size_t hashCode, std::size_t capacity ) noexcept
            {
                return hashCode % capacity;
            }
        };
    }
}

#ifdef HASH_MAP_PERF
/**
 * Collects hash map related information
 *
 * @note Not thread safe!
 */
class HashMapPerformanceStatistics
{
  public:
    void probedOnSearch( std::size_t probeSequenceLength ) const;
    void probedOnInsert( std::size_t probeSequenceLength ) const;

    void searched() const;
    void inserted() const;
    void resized() const;

    void unsuccessfulSearch() const;
    void read() const;
    void write() const;

    std::size_t longestSearchProbeSequenceLength() const;
    std::size_t cumulativeSearchProbeSequenceLength() const;

    std::size_t longestInsertProbeSequenceLength() const;
    std::size_t cumulativeInsertProbeSequenceLength() const;

    std::size_t numberOfSearches() const;
    std::size_t numberOfInsertions() const;
    std::size_t numberOfResizes() const;

    std::size_t numberOfUnsuccessfulSearches() const;
    std::size_t numberOfReads() const;
    std::size_t numberOfWrites() const;

    static HashMapPerformanceStatistics& overallStatistics();

  private:
    mutable std::size_t m_longestSearchProbeSequenceLength = 0UL;
    mutable std::size_t m_cumulativeSearchProbeSequenceLength = 0UL;
    mutable std::size_t m_longestInsertProbeSequenceLength = 0UL;
    mutable std::size_t m_cumulativeInsertProbeSequenceLength = 0UL;
    mutable std::size_t m_numberOfSearches = 0UL;
    mutable std::size_t m_numberOfInsertions = 0UL;
    mutable std::size_t m_numberOfResizes = 0UL;
    mutable std::size_t m_numberOfUnsuccessfulSearches = 0UL;
    mutable std::size_t m_numberOfReads = 0UL;
    mutable std::size_t m_numberOfWrites = 0UL;
};

std::ostream& operator<<(
    std::ostream& stream, const HashMapPerformanceStatistics& statistics );
#endif

template < typename Details >
class HashMapBase
{
    using Key = typename Details::Key;
    using Value = typename Details::Value;
    using Hash = typename Details::Hash;
    using Pred = typename Details::Pred;
    using Entry = typename Details::Entry;
    using Bucket = typename Details::Bucket;
    using HashingStrategy = typename Details::HashingStrategy;

  public:
    class const_iterator
    {
      public:
        using difference_type = std::ptrdiff_t;
        using iterator_category = std::forward_iterator_tag;

        explicit const_iterator( const Entry* entry )
        : m_entry( entry )
        {
        }

        const_iterator( const const_iterator& rhs )
        : m_entry( rhs.m_entry )
        {
        }

        const_iterator& operator=( const const_iterator& rhs ) noexcept
        {
            m_entry = rhs.m_entry;
            return *this;
        }

        bool operator==( const const_iterator& rhs ) const noexcept
        {
            return m_entry == rhs.m_entry;
        }

        bool operator!=( const const_iterator& rhs ) const noexcept
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
    explicit HashMapBase()
    : HashMapBase( 1UL )
    {
    }

    explicit HashMapBase( std::size_t initialCapacity )
    : m_buckets( nullptr )
    , m_size( 0UL )
    , m_capacity( std::max( initialCapacity, 1UL ) )
    , m_lastEntry( nullptr )
#ifdef HASH_MAP_PERF
    , m_performanceStatistics()
#endif
    {
    }

    HashMapBase( HashMapBase&& other )
    : m_buckets( nullptr )
    , m_size( other.m_size )
    , m_capacity( other.m_capacity )
    , m_lastEntry( other.m_lastEntry )
#ifdef HASH_MAP_PERF
    , m_performanceStatistics( other.m_performanceStatistics )
#endif
    {
        std::swap( m_buckets, other.m_buckets );
        std::swap( m_entryAllocator, other.m_entryAllocator );
    }

    HashMapBase& operator=( HashMapBase&& other ) noexcept
    {
        std::swap( m_buckets, other.m_buckets );
        m_size = other.m_size;
        m_capacity = other.m_capacity;
        m_lastEntry = other.m_lastEntry;
#ifdef HASH_MAP_PERF
        m_performanceStatistics = other.m_performanceStatistics;
#endif
        std::swap( m_entryAllocator, other.m_entryAllocator );
        return *this;
    }

    virtual ~HashMapBase()
    {
        if( m_buckets )
        {
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
        return Details::maximumLoadFactor();
    }

    constexpr const_iterator begin() const noexcept
    {
        return const_iterator( m_lastEntry );
    }

    constexpr const_iterator end() const noexcept
    {
        return const_iterator( nullptr );
    }

    /**
     * Inserts the \a value with the \a key into the hash map only if the key is
     * not already part of the hash map.
     *
     * @return A pair with an iterator pointing to the newly inserted or
     * existing
     *         entry and a boolean value indicating if the insertion was
     *         successful (true) or not (false)
     */
    std::pair< const_iterator, bool > insert(
        const Key& key, const Value& value )
    {
#ifdef HASH_MAP_PERF
        m_performanceStatistics.write();
#endif

        growIfNecessary();

        const auto hashCode = hashCodeOf( key );
        auto entry = searchEntry( key, hashCode );
        if( entry )
        {
            return std::make_pair( const_iterator( entry ), false );
        }
        else
        {
            entry = createEntry( key, value );
            insertEntry( entry, hashCode );
            return std::make_pair( const_iterator( entry ), true );
        }
    }

    /**
     * Inserts the \a value with the \a key into the hash map if the key is not
     * already part of the hash map, otherwise it overwrites the existing value.
     */
    void insertOrAssign( const Key& key, const Value& value )
    {
#ifdef HASH_MAP_PERF
        m_performanceStatistics.write();
#endif

        growIfNecessary();

        const auto hashCode = hashCodeOf( key );
        auto entry = searchEntry( key, hashCode );
        if( entry )
        {
            entry->value = value;
        }
        else
        {
            entry = createEntry( key, value );
            insertEntry( entry, hashCode );
        }
    }

    /**
     * Retrieves the value for the \a key.
     *
     * @throws std::out_of_range if no entry with a \a key could be found
     */
    const Value& get( const Key& key ) const
    {
#ifdef HASH_MAP_PERF
        m_performanceStatistics.read();
#endif

        const auto hashCode = hashCodeOf( key );
        const auto entry = searchEntry( key, hashCode );
        if( entry )
        {
            return entry->value;
        }
        else
        {
#ifdef HASH_MAP_PERF
            m_performanceStatistics.unsuccessfulSearch();
#endif
            throw std::out_of_range( "key not found" );
        }
    }

    const_iterator find( const Key& key ) const noexcept
    {
#ifdef HASH_MAP_PERF
        m_performanceStatistics.read();
#endif

        const auto hashCode = hashCodeOf( key );
        const auto entry = searchEntry( key, hashCode );
#ifdef HASH_MAP_PERF
        if( not entry )
        {
            m_performanceStatistics.unsuccessfulSearch();
        }
#endif
        return const_iterator( entry );
    }

    bool hasKey( const Key& key ) const noexcept
    {
        const auto hashCode = hashCodeOf( key );
        const auto entry = searchEntry( key, hashCode );
        return entry != nullptr;
    }

    void reserve( std::size_t n )
    {
        if( m_buckets )
        {
            if( needsResizing( n ) )
            {
                resize( HashingStrategy::initialSize(
                    n / maximumLoadFactor() + 1UL ) );
            }
        }
        else
        {
            m_capacity = std::max( n, m_capacity );
        }
    }

#ifdef HASH_MAP_PERF
    HashMapPerformanceStatistics performanceStatistics() const
    {
        return m_performanceStatistics;
    }
#endif

  protected:
    /**
     * Searches for an entry with the given \a key.
     *
     * @pre m_buckets may be invalid (nullptr) if no entry has been inserted
     *
     * @param key The key of the requested entry
     * @param hashCode The hash code of the \a key
     *
     * @return The entry for the given key or nullptr if no entry could be found
     */
    virtual Entry* searchEntry(
        const Key& key, const std::size_t hashCode ) const noexcept
        = 0;

    /**
     * Inserts the \a entry into the hash map.
     *
     * @pre m_buckets is valid (!= nullptr) and the current size of the hash map
     *      is smaller than its capacity
     * @post The \a entry is part of the hash map
     *
     * @param entry A valid entry
     * @param hashCode The hash code of the key of the \a entry
     */
    virtual void insertEntry( Entry* entry, std::size_t hashCode ) const
        noexcept
        = 0;

    /**
     * Resizes the hash map to a size of \a newCapacity, all old entries will be
     * preserved.
     *
     * @pre m_buckets may be invalid (nullptr) on initial resize
     * @post m_buckets is valid (!= nullptr) and has a size of \a newCapacity
     *       and m_capacity is equal to \a newCapacity
     *
     * @param newCapacity The capacity of the hash map after the resize
     */
    virtual void resize( std::size_t newCapacity ) = 0;

  private:
    std::size_t hashCodeOf( const Key& key ) const noexcept
    {
        static Hash hasher;
        return hasher( key );
    }

    /**
     * Creates a new entry with the given \a key and \a value pair.
     *
     * All entries are linked together using a single-linked list to optimize
     * the iterating performance in sparse hash map scenarios.
     *
     * @return An entry containing the given key-value pair
     */
    Entry* createEntry( const Key& key, const Value& value )
    {
        const auto memory = m_entryAllocator.allocate( sizeof( Entry ) );
        const auto entry = new( memory ) Entry( key, value, m_lastEntry );

        m_lastEntry = entry;
        ++m_size;

        return entry;
    }

    constexpr bool needsResizing( std::size_t size ) const noexcept
    {
        return size >= ( m_capacity * maximumLoadFactor() );
    }

    /**
     * Resizes the hash map if it has not enough capacity to store additional
     * entries, i.e. if the size exceeds the maximum load.
     *
     * @post m_buckets is valid (!= nullptr) and the current size of the hash
     *       map is smaller than its capacity
     */
    void growIfNecessary()
    {
        if( m_buckets == nullptr ) // initial resize
        {
            resize( HashingStrategy::initialSize( m_capacity ) );
        }
        else if( needsResizing( m_size ) )
        {
            resize( HashingStrategy::nextSize( m_capacity ) );
        }
        assert( m_size < m_capacity );
        assert( m_buckets != nullptr );
    }

  protected:
    Bucket* m_buckets; /**< Array of buckets */

    std::size_t m_size;     /**< The current size of the hash map */
    std::size_t m_capacity; /**< The capacity of the hash map */

    Entry*
        m_lastEntry; /**< Used to build a single-linked list in createEntry() */

#ifdef HASH_MAP_PERF
    HashMapPerformanceStatistics m_performanceStatistics;
#endif

  private:
    BlockAllocator< 4096 > m_entryAllocator;
};

#endif // _LIB_CASMFE_HASHMAPBASE_H_

//
//  Local variables:
//  mode: c++
//  indent-tabs-mode: nil
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//
