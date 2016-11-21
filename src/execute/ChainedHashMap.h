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

#include "HashMapBase.h"

namespace details
{
    template < typename _Key, typename _Value, typename _Hash, typename _Pred >
    struct ChainedHashMap
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
            std::size_t hashCode;
            Entry* next; // conflict chain
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

            constexpr bool empty() const
            {
                return entry == nullptr;
            }

            inline void insert( Entry* newEntry )
            {
                newEntry->next = entry;
                entry = newEntry;
            }
        };

        static constexpr float maximumLoadFactor() noexcept
        {
            return 1.0f;
        }
    };
}

template < typename Key,
    typename Value,
    typename Hash = std::hash< Key >,
    typename Pred = std::equal_to< Key >,
    typename Details = details::ChainedHashMap< Key, Value, Hash, Pred > >
class ChainedHashMap final : public HashMapBase< Details >
{
    using HashMap = HashMapBase< Details >;
    using Entry = typename Details::Entry;
    using Bucket = typename Details::Bucket;
    using HashingStrategy = typename Details::HashingStrategy;

  public:
    using HashMapBase< Details >::HashMapBase;

  protected:
    Entry* searchEntry( const Key& key, const std::size_t hashCode ) const
        noexcept override
    {
        static Pred equals;

        if( HashMap::m_buckets == nullptr )
        {
            return nullptr;
        }

        const auto bucket = bucketAt( hashCode );
        for( auto entry = bucket->entry; entry != nullptr; entry = entry->next )
        {
            if( ( entry->hashCode == hashCode ) and equals( entry->key, key ) )
            {
                return entry;
            }
        }

        return nullptr;
    }

    void insertEntry( Entry* entry, std::size_t hashCode ) const
        noexcept override
    {
        assert( HashMap::m_buckets != nullptr );

        entry->hashCode = hashCode;

        auto bucket = bucketAt( hashCode );
        bucket->insert( entry );
    }

    void resize( std::size_t newCapacity ) override
    {
        HashMap::m_capacity = newCapacity;

        if( HashMap::m_buckets )
        {
            delete[] HashMap::m_buckets;
        }
        HashMap::m_buckets = new Bucket[ newCapacity ];
        std::memset( HashMap::m_buckets, 0, sizeof( Bucket ) * newCapacity );

        for( auto entry = HashMap::m_lastEntry; entry != nullptr;
             entry = entry->prev )
        {
            insertEntry( entry, entry->hashCode );
        }
    }

  private:
    constexpr Bucket* bucketAt( std::size_t hashCode ) const noexcept
    {
        return HashMap::m_buckets
               + HashingStrategy::hash( hashCode, HashMap::m_capacity );
    }
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
