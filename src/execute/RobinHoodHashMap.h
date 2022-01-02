//
//  Copyright (C) 2014-2022 CASM Organization <https://casm-lang.org>
//  All rights reserved.
//
//  Developed by: Philipp Paulweber et al.
//                <https://github.com/casm-lang/libcasm-fe/graphs/contributors>
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

#ifndef _LIBCASM_FE_ROBINHOODHASHMAP_H_
#define _LIBCASM_FE_ROBINHOODHASHMAP_H_

#include <libcasm-fe/execute/HashMapBase>

namespace details
{
    template < typename _Key, typename _Value, typename _Hash, typename _Pred >
    struct RobinHoodHashMap
    {
        using Key = _Key;
        using Value = _Value;
        using Hash = _Hash;
        using Pred = _Pred;
        using HashingStrategy = HashingStrategy::PowerOfTwoHashing;

        struct Entry
        {
            Key key;
            Value value;
            Entry* prev;  // linked-list

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
            std::size_t distance;
            std::size_t hashCode;

            constexpr bool empty() const
            {
                return entry == nullptr;
            }
        };

        static constexpr float maximumLoadFactor() noexcept
        {
            return 0.75f;
        }
    };
}

template <
    typename Key,
    typename Value,
    typename Hash = std::hash< Key >,
    typename Pred = std::equal_to< Key >,
    typename Details = details::RobinHoodHashMap< Key, Value, Hash, Pred > >
class RobinHoodHashMap final : public HashMapBase< Details >
{
    using HashMap = HashMapBase< Details >;
    using Entry = typename Details::Entry;
    using Bucket = typename Details::Bucket;
    using HashingStrategy = typename Details::HashingStrategy;

  public:
    using HashMapBase< Details >::HashMapBase;

  protected:
    Entry* searchEntry( const Key& key, const std::size_t hashCode ) const noexcept override
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
        const auto initialIndex = HashingStrategy::compress( hashCode, capacity );

        for( std::size_t distance = 0;; ++distance )
        {
            assert( distance < capacity );

            const auto index = HashingStrategy::compress( initialIndex + distance, capacity );
            const auto bucket = buckets + index;

            if( bucket->empty() or ( distance > bucket->distance ) )
            {
#ifdef HASH_MAP_PERF
                HashMap::m_performanceStatistics.probedOnSearch( distance );
#endif
                return nullptr;
            }

            if( ( bucket->hashCode == hashCode ) and equals( bucket->entry->key, key ) )
            {
#ifdef HASH_MAP_PERF
                HashMap::m_performanceStatistics.probedOnSearch( distance );
#endif
                return bucket->entry;
            }
        }

        return nullptr;
    }

    void insertEntry( Entry* entry, std::size_t hashCode ) const noexcept override
    {
        assert( HashMap::m_buckets != nullptr );

#ifdef HASH_MAP_PERF
        HashMap::m_performanceStatistics.inserted();
#endif

        const auto buckets = HashMap::m_buckets;
        const auto capacity = HashMap::m_capacity;
        auto initialIndex = HashingStrategy::compress( hashCode, capacity );

        for( std::size_t distance = 0;; ++distance )
        {
            assert( distance < capacity );

            const auto index = HashingStrategy::compress( initialIndex + distance, capacity );
            const auto bucket = buckets + index;

            if( bucket->empty() )
            {
#ifdef HASH_MAP_PERF
                HashMap::m_performanceStatistics.probedOnInsert( distance );
#endif

                bucket->hashCode = hashCode;
                bucket->distance = distance;
                bucket->entry = entry;

                break;
            }

            if( distance > bucket->distance )
            {
                std::swap( hashCode, bucket->hashCode );
                std::swap( distance, bucket->distance );
                std::swap( entry, bucket->entry );

                initialIndex = HashingStrategy::compress( hashCode, capacity );
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

            delete[] oldBuckets;

#ifdef HASH_MAP_PERF
            HashMap::m_performanceStatistics.resized();
#endif
        }
    }
};

#endif  // _LIBCASM_FE_ROBINHOODHASHMAP_H_

//
//  Local variables:
//  mode: c++
//  indent-tabs-mode: nil
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//
