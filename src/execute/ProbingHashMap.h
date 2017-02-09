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

#ifndef _LIB_CASMFE_PROBINGHASHMAP_H_
#define _LIB_CASMFE_PROBINGHASHMAP_H_

#include "HashMapBase.h"

namespace details
{
    namespace ProbingStrategy
    {
        // h(i, k) = h1(k) + i
        struct LinearProbing
        {
            static constexpr std::size_t probe(
                const std::size_t index, const std::size_t round )
            {
                return index + round;
            }
        };

        // h(i, k) = h1(k) + i / 2 + i^2 / 2
        struct QuadraticProbing
        {
            static constexpr std::size_t probe(
                const std::size_t index, const std::size_t round )
            {
                return index + ( round + round * round ) / 2;
            }
        };
    }

    template < typename _Key, typename _Value, typename _Hash, typename _Pred >
    struct ProbingHashMap
    {
        using Key = _Key;
        using Value = _Value;
        using Hash = _Hash;
        using Pred = _Pred;
        using HashingStrategy = HashingStrategy::PowerOfTwoHashing;
        using ProbingStrategy = ProbingStrategy::QuadraticProbing;

        struct Entry
        {
            Key key;
            Value value;
            Entry* prev; // linked-list

            Entry( const Key& key, const Value& value, Entry* prev )
            : key( key )
            , value( value )
            , prev( prev )
            {
            }
        };

        struct Bucket
        {
            Entry* entry;
            std::size_t hashCode;

            constexpr bool empty() const
            {
                return entry == nullptr;
            }
        };

        static constexpr float maximumLoadFactor() noexcept
        {
            return 0.5f;
        }
    };
}

template < typename Key,
    typename Value,
    typename Hash = std::hash< Key >,
    typename Pred = std::equal_to< Key >,
    typename Details = details::ProbingHashMap< Key, Value, Hash, Pred > >
class ProbingHashMap final : public HashMapBase< Details >
{
    using HashMap = HashMapBase< Details >;
    using Entry = typename Details::Entry;
    using Bucket = typename Details::Bucket;
    using HashingStrategy = typename Details::HashingStrategy;
    using ProbingStrategy = typename Details::ProbingStrategy;

  public:
    using HashMapBase< Details >::HashMapBase;

  protected:
    Entry* searchEntry( const Key& key, const std::size_t hashCode ) const
        noexcept override
    {
#ifdef HASH_MAP_PERF
        HashMap::m_performanceStatistics.searched();
#endif

        static Pred equals;

        const auto buckets = HashMap::m_buckets;
        if( buckets == nullptr )
        {
            return nullptr;
        }

        const auto capacity = HashMap::m_capacity;
        const auto initialIndex
            = HashingStrategy::compress( hashCode, capacity );

        for( std::size_t round = 0;; round++ )
        {
            assert( round < capacity );

            const auto probedIndex
                = ProbingStrategy::probe( initialIndex, round );
            const auto index
                = HashingStrategy::compress( probedIndex, capacity );
            const auto bucket = buckets + index;

            if( bucket->empty() )
            {
#ifdef HASH_MAP_PERF
                HashMap::m_performanceStatistics.probedOnSearch( round );
#endif
                return nullptr;
            }

            if( ( bucket->hashCode == hashCode )
                and equals( bucket->entry->key, key ) )
            {
#ifdef HASH_MAP_PERF
                HashMap::m_performanceStatistics.probedOnSearch( round );
#endif
                return bucket->entry;
            }
        }

        return nullptr;
    }

    void insertEntry( Entry* entry, std::size_t hashCode ) const
        noexcept override
    {
        assert( HashMap::m_buckets != nullptr );

#ifdef HASH_MAP_PERF
        HashMap::m_performanceStatistics.inserted();
#endif

        const auto buckets = HashMap::m_buckets;
        const auto capacity = HashMap::m_capacity;
        const auto initialIndex
            = HashingStrategy::compress( hashCode, capacity );

        for( std::size_t round = 0;; round++ )
        {
            assert( round < capacity );

            const auto probedIndex
                = ProbingStrategy::probe( initialIndex, round );
            const auto index
                = HashingStrategy::compress( probedIndex, capacity );
            const auto bucket = buckets + index;

            if( bucket->empty() )
            {
#ifdef HASH_MAP_PERF
                HashMap::m_performanceStatistics.probedOnInsert( round );
#endif

                bucket->hashCode = hashCode;
                bucket->entry = entry;

                break;
            }
        }
    }

    void resize( std::size_t newCapacity ) override
    {
        const auto oldCapacity = HashMap::m_capacity;
        const auto oldBuckets = HashMap::m_buckets;

        HashMap::m_capacity = newCapacity;
        HashMap::m_buckets = new Bucket[ newCapacity ];
        std::memset( HashMap::m_buckets, 0, sizeof( Bucket ) * newCapacity );

        if( oldBuckets )
        {
            const auto firstBucket = oldBuckets;
            const auto lastBucket = oldBuckets + oldCapacity;

            for( auto bucket = firstBucket; bucket != lastBucket; ++bucket )
            {
                if( not bucket->empty() )
                {
                    insertEntry( bucket->entry, bucket->hashCode );
                }
            }

            delete oldBuckets;

#ifdef HASH_MAP_PERF
            HashMap::m_performanceStatistics.resized();
#endif
        }
    }
};

#endif // _LIB_CASMFE_PROBINGHASHMAP_H_

//
//  Local variables:
//  mode: c++
//  indent-tabs-mode: nil
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//
