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

namespace details
{
    namespace HashingStrategy
    {
        struct PowerOfTwoHashing
        {
            static /*constexpr*/ std::size_t initialSize(
                std::size_t size ) noexcept
            {
                return nextPowerOfTwo( size );
            }

            static /*constexpr*/ std::size_t nextSize(
                std::size_t size ) noexcept
            {
                assert( isPowerOfTwo( size ) );
                return size * 2;
            }

            static constexpr std::size_t hash(
                std::size_t hashCode, std::size_t capacity ) noexcept
            {
                return hashCode & ( capacity - 1 );
            }

          private:
            /**
             * @note From Bit Twiddling Hacks
             * @see
             * https://graphics.stanford.edu/~seander/bithacks.html#RoundUpPowerOf2
             */
            static /*constexpr*/ std::size_t nextPowerOfTwo(
                std::size_t n ) noexcept
            {
                n -= 1;
                n |= ( n >> 1 );
                n |= ( n >> 2 );
                n |= ( n >> 4 );
                n |= ( n >> 8 );
                n |= ( n >> 16 );
#if __SIZEOF_SIZE_T__ > 4
                n |= ( n >> 32 );
#endif
                return n + 1;
            }

            /**
             * @note From Bit Twiddling Hacks
             * @see
             * https://graphics.stanford.edu/~seander/bithacks.html#DetermineIfPowerOf2
             */
            static constexpr bool isPowerOfTwo( std::size_t n ) noexcept
            {
                return ( ( n != 0 ) && !( n & ( n - 1 ) ) );
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

            static constexpr std::size_t hash(
                std::size_t hashCode, std::size_t capacity ) noexcept
            {
                return hashCode % capacity;
            }

          private:
            /**
             * Returns the next bigger prime number of \a n
             *
             * @note From GCC libstdc++
             *
             * @return Next bigger prime number (greater than \a n)
             */
            static std::size_t nextPrime( std::size_t n ) noexcept
            {
                static const unsigned char unfoldedPrimes[]
                    = { 2, 2, 3, 5, 5, 7, 7, 11, 11, 11, 11, 13, 13 };

                static const unsigned long primes[]
                    = { 17UL,
                          19UL,
                          23UL,
                          29UL,
                          31UL,
                          37UL,
                          41UL,
                          43UL,
                          47UL,
                          53UL,
                          59UL,
                          61UL,
                          67UL,
                          71UL,
                          73UL,
                          79UL,
                          83UL,
                          89UL,
                          97UL,
                          103UL,
                          109UL,
                          113UL,
                          127UL,
                          137UL,
                          139UL,
                          149UL,
                          157UL,
                          167UL,
                          179UL,
                          193UL,
                          199UL,
                          211UL,
                          227UL,
                          241UL,
                          257UL,
                          277UL,
                          293UL,
                          313UL,
                          337UL,
                          359UL,
                          383UL,
                          409UL,
                          439UL,
                          467UL,
                          503UL,
                          541UL,
                          577UL,
                          619UL,
                          661UL,
                          709UL,
                          761UL,
                          823UL,
                          887UL,
                          953UL,
                          1031UL,
                          1109UL,
                          1193UL,
                          1289UL,
                          1381UL,
                          1493UL,
                          1613UL,
                          1741UL,
                          1879UL,
                          2029UL,
                          2179UL,
                          2357UL,
                          2549UL,
                          2753UL,
                          2971UL,
                          3209UL,
                          3469UL,
                          3739UL,
                          4027UL,
                          4349UL,
                          4703UL,
                          5087UL,
                          5503UL,
                          5953UL,
                          6427UL,
                          6949UL,
                          7517UL,
                          8123UL,
                          8783UL,
                          9497UL,
                          10273UL,
                          11113UL,
                          12011UL,
                          12983UL,
                          14033UL,
                          15173UL,
                          16411UL,
                          17749UL,
                          19183UL,
                          20753UL,
                          22447UL,
                          24281UL,
                          26267UL,
                          28411UL,
                          30727UL,
                          33223UL,
                          35933UL,
                          38873UL,
                          42043UL,
                          45481UL,
                          49201UL,
                          53201UL,
                          57557UL,
                          62233UL,
                          67307UL,
                          72817UL,
                          78779UL,
                          85229UL,
                          92203UL,
                          99733UL,
                          107897UL,
                          116731UL,
                          126271UL,
                          136607UL,
                          147793UL,
                          159871UL,
                          172933UL,
                          187091UL,
                          202409UL,
                          218971UL,
                          236897UL,
                          256279UL,
                          277261UL,
                          299951UL,
                          324503UL,
                          351061UL,
                          379787UL,
                          410857UL,
                          444487UL,
                          480881UL,
                          520241UL,
                          562841UL,
                          608903UL,
                          658753UL,
                          712697UL,
                          771049UL,
                          834181UL,
                          902483UL,
                          976369UL,
                          1056323UL,
                          1142821UL,
                          1236397UL,
                          1337629UL,
                          1447153UL,
                          1565659UL,
                          1693859UL,
                          1832561UL,
                          1982627UL,
                          2144977UL,
                          2320627UL,
                          2510653UL,
                          2716249UL,
                          2938679UL,
                          3179303UL,
                          3439651UL,
                          3721303UL,
                          4026031UL,
                          4355707UL,
                          4712381UL,
                          5098259UL,
                          5515729UL,
                          5967347UL,
                          6456007UL,
                          6984629UL,
                          7556579UL,
                          8175383UL,
                          8844859UL,
                          9569143UL,
                          10352717UL,
                          11200489UL,
                          12117689UL,
                          13109983UL,
                          14183539UL,
                          15345007UL,
                          16601593UL,
                          17961079UL,
                          19431899UL,
                          21023161UL,
                          22744717UL,
                          24607243UL,
                          26622317UL,
                          28802401UL,
                          31160981UL,
                          33712729UL,
                          36473443UL,
                          39460231UL,
                          42691603UL,
                          46187573UL,
                          49969847UL,
                          54061849UL,
                          58488943UL,
                          63278561UL,
                          68460391UL,
                          74066549UL,
                          80131819UL,
                          86693767UL,
                          93793069UL,
                          101473717UL,
                          109783337UL,
                          118773397UL,
                          128499677UL,
                          139022417UL,
                          150406843UL,
                          162723577UL,
                          176048909UL,
                          190465427UL,
                          206062531UL,
                          222936881UL,
                          241193053UL,
                          260944219UL,
                          282312799UL,
                          305431229UL,
                          330442829UL,
                          357502601UL,
                          386778277UL,
                          418451333UL,
                          452718089UL,
                          489790921UL,
                          529899637UL,
                          573292817UL,
                          620239453UL,
                          671030513UL,
                          725980837UL,
                          785430967UL,
                          849749479UL,
                          919334987UL,
                          994618837UL,
                          1076067617UL,
                          1164186217UL,
                          1259520799UL,
                          1362662261UL,
                          1474249943UL,
                          1594975441UL,
                          1725587117UL,
                          1866894511UL,
                          2019773507UL,
                          2185171673UL,
                          2364114217UL,
                          2557710269UL,
                          2767159799UL,
                          2993761039UL,
                          3238918481UL,
                          3504151727UL,
                          3791104843UL,
                          4101556399UL,
                          4294967291UL,
#if __SIZEOF_SIZE_T__ > 4
                          6442450933UL,
                          8589934583UL,
                          12884901857UL,
                          17179869143UL,
                          25769803693UL,
                          34359738337UL,
                          51539607367UL,
                          68719476731UL,
                          103079215087UL,
                          137438953447UL,
                          206158430123UL,
                          274877906899UL,
                          412316860387UL,
                          549755813881UL,
                          824633720731UL,
                          1099511627689UL,
                          1649267441579UL,
                          2199023255531UL,
                          3298534883309UL,
                          4398046511093UL,
                          6597069766607UL,
                          8796093022151UL,
                          13194139533241UL,
                          17592186044399UL,
                          26388279066581UL,
                          35184372088777UL,
                          52776558133177UL,
                          70368744177643UL,
                          105553116266399UL,
                          140737488355213UL,
                          211106232532861UL,
                          281474976710597UL,
                          562949953421231UL,
                          1125899906842597UL,
                          2251799813685119UL,
                          4503599627370449UL,
                          9007199254740881UL,
                          18014398509481951UL,
                          36028797018963913UL,
                          72057594037927931UL,
                          144115188075855859UL,
                          288230376151711717UL,
                          576460752303423433UL,
                          1152921504606846883UL,
                          2305843009213693951UL,
                          4611686018427387847UL,
                          9223372036854775783UL,
                          18446744073709551557UL,
                          18446744073709551557UL
#endif
                      };

                constexpr auto unfoldedPrimesCount
                    = sizeof( unfoldedPrimes ) / sizeof( char );
                constexpr auto primesCount
                    = sizeof( primes ) / sizeof( unsigned long );

                constexpr auto firstPrime = primes;
                constexpr auto lastPrime = primes + primesCount - 1;

                if( n < unfoldedPrimesCount )
                {
                    return unfoldedPrimes[ n ];
                }
                else
                {
                    return *std::lower_bound( firstPrime, lastPrime, n + 1 );
                }
            }
        };
    }
}

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
    {
    }

    HashMapBase( HashMapBase&& other )
    : m_buckets( nullptr )
    , m_size( other.m_size )
    , m_capacity( other.m_capacity )
    , m_lastEntry( other.m_lastEntry )
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
        const auto hashCode = hashCodeOf( key );
        const auto entry = searchEntry( key, hashCode );
        if( entry )
        {
            return entry->value;
        }
        else
        {
            throw std::out_of_range( "key not found" );
        }
    }

    const_iterator find( const Key& key ) const noexcept
    {
        const auto hashCode = hashCodeOf( key );
        const auto entry = searchEntry( key, hashCode );
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
