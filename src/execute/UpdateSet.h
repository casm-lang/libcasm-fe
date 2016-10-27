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

#include <cstdint>
#include <stdexcept>
#include <stack>

#include "Update.h"
#include "ChainedHashMap.h"
#include "OpenHashMap.h"
#include "RobinHoodHashMap.h"

struct LocationHash
{
    /**
     * Directly using a value_t pointer as hash value has the problem that the first
     * 4 bits of the hash value are always 0, because the size of value_t is 16 bytes.
     * Some bit shifting avoids this problem.
     *
     * Forumla is from LLVM's DenseMapInfo<T*>
     */
    std::size_t operator()(const value_t* location) const
    {
        return (reinterpret_cast<std::uintptr_t>(location) >> 4) ^
               (reinterpret_cast<std::uintptr_t>(location) >> 9);
    }
};

class UpdateSet
{
public:
    class Conflict : public std::logic_error
    {
    public:
        Conflict(const std::string& msg, Update* conflictingUpdate, Update* existingUpdate);

        Update* conflictingUpdate() const noexcept;
        Update* existingUpdate() const noexcept;

    private:
        Update* m_conflictingUpdate;
        Update* m_existingUpdate;
    };

    enum class Type
    {
        Sequential,
        Parallel
    };

    using UpdateHashMap = ChainedHashMap<const value_t*, Update*, LocationHash>;

public:
    using const_iterator = typename UpdateHashMap::const_iterator;

    explicit UpdateSet(std::size_t initialSize, UpdateSet* parent = nullptr);
    virtual ~UpdateSet();

    virtual Type type() const noexcept = 0;

    bool empty() const noexcept;
    size_t size() const noexcept;

    /**
     *
     * @throws Conflict
     */
    virtual void add(const value_t* location, Update* update) = 0;

    virtual Update* lookup(const value_t* location) const;

    UpdateSet* fork(const UpdateSet::Type updateSetType, std::size_t initialSize);

    /**
     *
     * @throws Conflict
     */
    void merge();

    const_iterator begin() const noexcept;
    const_iterator end() const noexcept;

    Update* get(const value_t* location) const noexcept;

protected:
    UpdateHashMap m_set;

private:
    UpdateSet* m_parent;
};

/**
 * @brief Update-set with sequential execution semantics
 */
class SequentialUpdateSet final : public UpdateSet
{
public:
    using UpdateSet::UpdateSet;

    Type type() const noexcept override;

    /**
     * Adds the \a udpate for \a location to this update-set
     */
    void add(const value_t* location, Update* update) override;

    Update* lookup(const value_t* location) const override;
};

/**
 * @brief Update-set with parallel execution semantics
 */
class ParallelUpdateSet final : public UpdateSet
{
public:
    using UpdateSet::UpdateSet;

    Type type() const noexcept override;

    /**
     * Adds the \a udpate for \a location to this update-set
     *
     * @throws Conflict when an update for \a location exists already and the
     *         values of both updates are different
     */
    void add(const value_t* location, Update* update) override;
};

class UpdateSetManager
{
public:
    UpdateSetManager();
    virtual ~UpdateSetManager();

    /**
     *
     * @throws Conflict
     */
    void add(const value_t* location, Update* update);

    Update* lookup(const value_t* location) const;

    void fork(const UpdateSet::Type updateSetType, std::size_t initialSize);

    /**
     *
     * @throws Conflict
     */
    void merge();

    void clear();

    UpdateSet* currentUpdateSet() const;

    size_t size() const;

private:
    std::stack<UpdateSet*> m_updateSets;
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
