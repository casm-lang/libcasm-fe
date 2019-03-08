//
//  Copyright (C) 2014-2019 CASM Organization <https://casm-lang.org>
//  All rights reserved.
//
//  Developed by: Philipp Paulweber
//                Emmanuel Pescosta
//                Florian Hahn
//                Ioan Molnar
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

#ifndef _LIBCASM_FE_FUNCTION_STATE_H_
#define _LIBCASM_FE_FUNCTION_STATE_H_

#include <libcasm-fe/execute/ProbingHashMap>

#include <libstdhl/Optional>

/*struct FunctionStateDetails
{
    using Location = ;
    using Value = ;
    using LocationHash = std::hash< Location >;
    using LocationEquals = std::equal_to< Location >;
};*/

/**
 * @brief
 */
template < typename _Details >
class FunctionState
{
  public:
    using Details = _Details;
    using Location = typename Details::Location;
    using Value = typename Details::Value;

  private:
    using StateHashMap = ProbingHashMap<
        Location,
        Value,
        typename Details::LocationHash,
        typename Details::LocationEquals >;

  public:
    using const_iterator = typename StateHashMap::const_iterator;

  public:
    /**
     * Constructs an empty function state
     *
     * @param initialSize The number of locations the function state should be
     *                    able to handle without resizing
     */
    explicit FunctionState( std::size_t initialSize )
    : m_state( initialSize )
    {
    }

    /**
     * Destroys the function state
     */
    virtual ~FunctionState() = default;

    /**
     * @return A boolean value indicating wheter the function state is empty,
     *         i.e. wheter it doesn't contain locations
     */
    bool empty() const noexcept
    {
        return m_state.empty();
    }

    /**
     * @return The number of locations in the function state
     */
    std::size_t size() const noexcept
    {
        return m_state.size();
    }

    /**
     * Adds the \a location with value \a value to the function state, or
     * overwrites the existing value.
     *
     * @param location The location which should be added or changed
     * @param value The value which should be assigned
     */
    void set( const Location& location, const Value& value )
    {
        m_state.insertOrAssign( location, value );
    }

    /**
     * Removes the \a location from the function state.
     *
     * Does nothing if the \a location doesn't exist in the function state.
     *
     * @param location The location which should be remove from the function
     * state
     */
    void remove( const Location& location )
    {
        // TODO
    }

    /**
     * Searches for an value for the \a location in the function state.
     *
     * @param location The location of the function value of interest
     *
     * @return The function value for the \a location if an value exists.
     */
    libstdhl::Optional< Value > get( const Location& location ) const noexcept
    {
        const auto it = m_state.find( location );
        if( it != m_state.end() )
        {
            return it.value();
        }

        return {};
    }

    /**
     * @return Iterator to the beginning of the function state
     */
    const_iterator begin() const noexcept
    {
        return m_state.begin();
    }

    /**
     * @return Iterator to the end of the function state
     */
    const_iterator end() const noexcept
    {
        return m_state.end();
    }

  protected:
    StateHashMap m_state;
};

#endif  // _LIBCASM_FE_FUNCTION_STATE_H_

//
//  Local variables:
//  mode: c++
//  indent-tabs-mode: nil
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//
