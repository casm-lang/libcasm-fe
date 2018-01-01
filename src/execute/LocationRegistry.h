//
//  Copyright (C) 2014-2018 CASM Organization <https://casm-lang.org>
//  All rights reserved.
//
//  Developed by: Philipp Paulweber
//                Emmanuel Pescosta
//                Florian Hahn
//                <https://github.com/casm-lang/libcasm-fe>
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

#ifndef _LIBCASM_FE_LOCATION_REGISTRY_H_
#define _LIBCASM_FE_LOCATION_REGISTRY_H_

#include <experimental/optional>
#include <unordered_set>

/*struct LocationRegistryDetails
 * {
 *    using Function = ;
 *    using FunctionHash = std::hash< Function >;
 *    using FunctionEquals = std::equal_to< Function >;
 *    using Arguments = ;
 *    using ArgumentsHash = std::hash< Arguments >;
 *    using ArgumentsEquals = std::equal_to< Arguments >;
 * };*/

/**
 * @brief
 */
template < typename Details >
class LocationRegistry
{
  private:
    using Function = typename Details::Function;
    using FunctionHash = typename Details::FunctionHash;
    using FunctionEquals = typename Details::FunctionEquals;
    using Arguments = typename Details::Arguments;
    using ArgumentsHash = typename Details::ArgumentsHash;
    using ArgumentsEquals = typename Details::ArgumentsEquals;

    using LocationData = std::pair< Function, Arguments >;

    struct LocationDataHash
    {
        std::size_t operator()( const LocationData& location ) const
        {
            return libstdhl::Hash::combine(
                FunctionHash{}( location.first ), ArgumentsHash{}( location.second ) );
        }
    };

    struct LocationDataEquals
    : public std::binary_function< const LocationData&, const LocationData&, bool >
    {
        bool operator()( const LocationData& lhs, const LocationData& rhs ) const
        {
            return FunctionEquals{}( lhs.first, rhs.first ) and
                   ArgumentsEquals{}( lhs.second, rhs.second );
        }
    };

    using LocationDataSet =
        std::unordered_set< LocationData, LocationDataHash, LocationDataEquals >;

  public:
    struct LocationHash;
    struct LocationEquals;

    class Location
    {
      public:
        explicit Location( const LocationData* data )
        : m_data( data )
        {
            assert( m_data != nullptr );
        }

        const Function& function() const
        {
            return m_data->first;
        }

        const Arguments& arguments() const
        {
            return m_data->second;
        }

        friend struct LocationHash;
        friend struct LocationEquals;

      private:
        const LocationData* m_data;
    };

    struct LocationHash
    {
        std::size_t operator()( const Location& ref ) const
        {
            return ( reinterpret_cast< std::uintptr_t >( ref.m_data ) >> 4 ) ^
                   ( reinterpret_cast< std::uintptr_t >( ref.m_data ) >> 9 );
        }
    };

    struct LocationEquals : public std::binary_function< const Location&, const Location&, bool >
    {
        bool operator()( const Location& lhs, const Location& rhs ) const
        {
            return lhs.m_data == rhs.m_data;
        }
    };

  public:
    /**
     * Constructs an empty location registry
     *
     * @param initialSize The number of locations the registry should be able to
     *                    handle without resizing
     */
    explicit LocationRegistry( std::size_t initialSize = 100UL )
    : m_locations()
    {
        m_locations.reserve( initialSize );
    }

    /**
     * @return A boolean value indicating wheter the location registry is empty,
     *         i.e. wheter it doesn't contain locations
     */
    bool empty() const noexcept
    {
        return m_locations.empty();
    }

    /**
     * @return The number of locations in the location registry
     */
    std::size_t size() const noexcept
    {
        return m_locations.size();
    }

    /**
     * Retrieves the location for the given \a function \a arguments pair.
     *
     * If the location is not already registered, a new location will be added.
     * Otherwise the already existing location will be used.
     *
     * @param function The function of the location
     * @param arguments The arguments of the location
     *
     * @return The location for the given function-arguments pair.
     */
    Location get( const Function& function, const Arguments& arguments )
    {
        const auto result = m_locations.insert( { function, arguments } );
        return Location( &*result.first );
    }

    /**
     * Searches for an existing location for the given \a function \a arguments
     * pair.
     *
     * If a location does not already exist, no location will be added.
     *
     * @param function The function of the location
     * @param arguments The arguments of the location
     *
     * @return The location for the given function-arguments pair, if the
     *         location exists.
     */
    std::experimental::optional< Location > lookup(
        const Function& function, const Arguments& arguments ) const noexcept
    {
        const auto it = m_locations.find( { function, arguments } );
        if( it != m_locations.cend() )
        {
            return Location( &*it );
        }

        return std::experimental::nullopt;
    }

  protected:
    LocationDataSet m_locations;
};

#endif  // _LIBCASM_FE_LOCATION_REGISTRY_H_

//
//  Local variables:
//  mode: c++
//  indent-tabs-mode: nil
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//
