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

#ifndef _LIB_CASMFE_UPDATESET_H_
#define _LIB_CASMFE_UPDATESET_H_

#include <stack>
#include <stdexcept>

#include "../Value.h"
#include "../various/location.hh"

#include "ChainedHashMap.h"
#include "ProbingHashMap.h"
#include "RobinHoodHashMap.h"

struct LocationHash
{
    /**
     * Directly using a value_t pointer as hash value has the problem that the
     * first
     * 4 bits of the hash value are always 0, because the size of value_t is 16
     * bytes.
     * Some bit shifting avoids this problem.
     *
     * Forumla is from LLVM's DenseMapInfo<T*>
     */
    std::size_t operator()( const value_t* location ) const
    {
        return ( reinterpret_cast< std::uintptr_t >( location ) >> 4 )
               ^ ( reinterpret_cast< std::uintptr_t >( location ) >> 9 );
    }
};

/**
 * @brief Represents an update
 */
struct Update
{
    value_t value; /**< The value of the update */
    const std::vector< value_t >*
        args; /**< The function arguments of the update */
    const yy::location*
        location;  /**< The source-code location of the update producer */
    uint32_t func; /**< The function uid of the update */
};

/**
 * @brief Base class for all types of update-sets
 */
class UpdateSet
{
  public:
    /**
     * @brief An exception which will be thrown when updates are in conflict
     */
    class Conflict : public std::logic_error
    {
      public:
        /**
         * Constructs a conflict exception
         *
         * @param msg A problem-description for the user
         * @param conflictingUpdate Update which caused the conflict
         * @param existingUpdate Existing update for the same location as the
         *                       \a conflictingUpdate
         */
        Conflict( const std::string& msg, Update* conflictingUpdate,
            Update* existingUpdate );

        /**
         * @return The update which caused the conflict
         */
        Update* conflictingUpdate() const noexcept;

        /**
         * @return The existing update for the same location as the conflicting
         *         update
         */
        Update* existingUpdate() const noexcept;

      private:
        Update* m_conflictingUpdate;
        Update* m_existingUpdate;
    };

    /**
     * @brief The type of the update-set
     */
    enum class Type
    {
        Sequential, /**< Update-set with sequential execution semantics */
        Parallel    /**< Update-set with parallel execution semantics */
    };

    using UpdateHashMap
        = ChainedHashMap< const value_t*, Update*, LocationHash >;

  public:
    using const_iterator = typename UpdateHashMap::const_iterator;

    /**
     * Constructs an empty update-set
     *
     * @param initialSize The number of updates the update-set should be able to
     *                    handle without resizing
     * @param parent The parent update-set (if there is any)
     */
    explicit UpdateSet( std::size_t initialSize, UpdateSet* parent = nullptr );

    /**
     * Destroys the update-set
     */
    virtual ~UpdateSet() = default;

    /**
     * @see UpdateSet::Type
     *
     * @return The type of the update-set
     */
    virtual Type type() const noexcept = 0;

    /**
     * @return A boolean value indicating wheter the update-set is empty, i.e.
     *         wheter it doesn't contain updates
     */
    bool empty() const noexcept;

    /**
     * @return The number of updates in the update-set
     */
    std::size_t size() const noexcept;

    /**
     * Adds the \a update for the \a location to the update-set
     *
     * The handling of multiple updates for the same location depends on the
     * actual type of the update-set.
     *
     * @note The udpate-set will not take over the ownership of \a update.
     *
     * @param location The location of the update
     * @param update The update which should be added
     *
     * @throws Conflict when the update-set is a parallel update-set, an update
     *         for the \a location exists already and the values of both updates
     *         are different
     */
    virtual void add( const value_t* location, Update* update ) = 0;

    /**
     * Searches for an update for the \a location in the update-set
     *
     * If the current update-set doesn't contain an update for the \a location,
     * the parent update-set will be searched.
     *
     * @param location The location of the update of interest
     *
     * @return The update for the \a location or nullptr if no update for the
     *         \a location could be found.
     */
    virtual Update* lookup( const value_t* location ) const noexcept;

    /**
     * Forks the current update-set
     *
     * @param updateSetType The type of the forked update-set @see
     * UpdateSet::Type
     * @param initialSize The number of updates the update-set should be able to
     *                    handle without resizing
     *
     * @return A new update-set of type \a updateSetType with the current
     *         update-set as parent
     */
    UpdateSet* fork( UpdateSet::Type updateSetType, std::size_t initialSize );

    /**
     * Merges all updates of the current update-set into its parent update-set
     *
     * @pre The update-set must have a parent update-set
     *
     * @throws Conflict when the parent update-set is a parallel update-set, an
     *         update for the \a location exists already in the parent
     * update-set
     *         and the values of both updates are different
     */
    void merge();

    /**
     * @return Iterator to the beginning of the update-set
     */
    const_iterator begin() const noexcept;

    /**
     * @return Iterator to the end of the update-set
     */
    const_iterator end() const noexcept;

    /**
     * Searches for an update for the \a location in the current update-set
     *
     * An existing update will always be returned regardless of the type of
     * the update-set.
     *
     * @note In contrast to lookup() no recursive search will be performed.
     *
     * @param location The location of the update of interest
     *
     * @return The update for the \a location or nullptr if no update for the
     *         \a location could be found.
     */
    Update* get( const value_t* location ) const noexcept;

  protected:
    UpdateHashMap m_set;

  private:
    UpdateSet* const m_parent;
};

/**
 * @brief Update-set with sequential execution semantics
 */
class SequentialUpdateSet final : public UpdateSet
{
  public:
    using UpdateSet::UpdateSet;

    /**
     * @see UpdateSet::Type::Sequential
     *
     * @return The type of the update-set
     */
    Type type() const noexcept override;

    /**
     * Adds the \a update for the \a location to the update-set.
     *
     * If an update for the same location exists already then it will be
     * overwritten.
     *
     * @note The udpate-set will not take over the ownership of \a update.
     *
     * @param location The location of the update
     * @param update The update which should be added
     */
    void add( const value_t* location, Update* update ) override;

    /**
     * Searches for an update for the \a location in the update-set
     *
     * If the current update-set doesn't contain an update for the \a location,
     * the parent update-set will be searched.
     *
     * @param location The location of the update of interest
     *
     * @return The update for the \a location or nullptr if no update for the
     *         \a location could be found.
     */
    Update* lookup( const value_t* location ) const noexcept override;
};

/**
 * @brief Update-set with parallel execution semantics
 */
class ParallelUpdateSet final : public UpdateSet
{
  public:
    using UpdateSet::UpdateSet;

    /**
     * @see UpdateSet::Type::Parallel
     *
     * @return The type of the update-set
     */
    Type type() const noexcept override;

    /**
     * Adds the \a update for the \a location to the update-set
     *
     * @note The udpate-set will not take over the ownership of \a update.
     *
     * @param location The location of the update
     * @param update The update which should be added
     *
     * @throws Conflict when an update for the \a location exists already and
     *         the values of both updates are different
     */
    void add( const value_t* location, Update* update ) override;
};

/**
 * @brief An helper for convenient forking and merging of update-sets
 */
class UpdateSetManager
{
  public:
    /**
     * Constructs an empty update-set manager
     */
    UpdateSetManager();

    /**
     * Destroys the update-set manager and frees all update-sets
     */
    virtual ~UpdateSetManager();

    /**
     * Adds the \a update for the \a location to the current update-set
     *
     * The handling of multiple updates for the same location depends on the
     * actual type of the update-set.
     *
     * @note The udpate-set will not take over the ownership of \a update.
     *
     * @pre The update-set manager must not be empty
     *
     * @param location The location of the update
     * @param update The update which should be added
     *
     * @throws Conflict when the update-set is a parallel update-set, an update
     *         for the \a location exists already and the values of both updates
     *         are different
     */
    void add( const value_t* location, Update* update );

    /**
     * Searches for an update for the \a location in the current update-set
     *
     * If the current update-set doesn't contain an update for the \a location,
     * the parent update-set will be searched.
     *
     * @param location The location of the update of interest
     *
     * @return The update for the \a location or nullptr if no update for the
     *         \a location could be found.
     */
    Update* lookup( const value_t* location ) const noexcept;

    /**
     * Forks the current update-set or creates a new update-set if the
     * update-set manager is empty
     *
     * @post The forked update-set is the new "current update-set" and the size
     *       of the update-set manager is increased by one
     *
     * @param updateSetType The type of the forked update-set @see
     * UpdateSet::Type
     * @param initialSize The number of updates the update-set should be able to
     *                    handle without resizing
     */
    void fork( UpdateSet::Type updateSetType, std::size_t initialSize );

    /**
     * Merges all updates of the current update-set into its parent update-set
     *
     * The merge will only be performed if there is more than one update-set in
     * the update-set manager.
     *
     * @post If an merge has been performed the size of the update-set manager
     *       is decreased by one
     *
     * @throws Conflict when the parent update-set is a parallel update-set, an
     *         update for the \a location exists already in the parent
     * update-set
     *         and the values of both updates are different
     */
    void merge();

    /**
     * Removes all update-sets from the update-set manager
     */
    void clear();

    /**
     * @pre The update-set manager must not be empty
     *
     * @return The current update-set of the update-set manager, i.e. the
     *         update-set on top of the update-set stack.
     */
    UpdateSet* currentUpdateSet() const;

    /**
     * @return The number of update-sets in the update-set manager
     */
    std::size_t size() const noexcept;

  private:
    std::stack< UpdateSet* > m_updateSets;
};

#endif // _LIB_CASMFE_UPDATESET_H_

//
//  Local variables:
//  mode: c++
//  indent-tabs-mode: nil
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//
