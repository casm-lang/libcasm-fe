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

#include "UpdateHashMap.h"

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

public:
    using const_iterator = typename UpdateHashMap<const value_t*, Update*>::const_iterator;

    explicit UpdateSet(Type type, UpdateSet* parent = nullptr);
    virtual ~UpdateSet();

    Type type() const noexcept;

    bool empty() const noexcept;
    size_t size() const noexcept;

    /**
     *
     * @throws Conflict
     */
    void add(const value_t* location, Update* update);

    Update* lookup(const value_t* location) const;

    UpdateSet* fork(const UpdateSet::Type updateSetType);

    /**
     *
     * @throws Conflict
     */
    void merge();

    const_iterator begin() const noexcept;
    const_iterator end() const noexcept;

    Update* get(const value_t* location) const noexcept;

private:
    UpdateSet* m_parent;
    const Type m_type;
    UpdateHashMap<const value_t*, Update*> m_set;
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

    void fork(const UpdateSet::Type updateSetType);

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
