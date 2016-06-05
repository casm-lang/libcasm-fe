//
//  Copyright (c) 2014-2016 CASM Organization
//  All rights reserved.
//
//  Developed by: Florian Hahn
//                Philipp Paulweber
//                Emmanuel Pescosta
//                https://github.com/ppaulweber/libcasm-fe
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

#include "LinkedHashMap.h"

struct Update
{
    void* value;
    uint64_t* args;
    uint64_t line;
    uint32_t func; // function uid
    uint16_t sym_args;
    uint16_t num_args;
    bool defined; // TODO correct data type
    bool symbolic; // TODO correct data type
};

class UpdateSet
{
public:
    class MergeError : public std::logic_error
    {
    public:
        MergeError(const std::string& msg, Update* conflictingUpdate, Update* existingUpdate);

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
    using const_iterator = typename LinkedHashMap<uint64_t, Update*>::const_iterator;

    explicit UpdateSet(Type type, UpdateSet* parent = nullptr);
    virtual ~UpdateSet();

    Type type() const noexcept;

    bool empty() const noexcept;
    size_t size() const noexcept;

    /**
     *
     * @throws RuntimeException
     */
    void add(const uint64_t key, Update* update);

    Update* lookup(const uint64_t key) const;

    UpdateSet* fork();

    /**
     *
     * @throws MergeError
     */
    void merge();

    void clear();

    const_iterator cbegin() const noexcept;
    const_iterator cend() const noexcept;

private:
    UpdateSet* m_parent;
    const Type m_type;
    LinkedHashMap<uint64_t, Update*> m_set;
};

class UpdateSetManager
{
public:
    UpdateSetManager();
    virtual ~UpdateSetManager();

    /**
     *
     * @throws RuntimeException
     */
    void add(const uint64_t key, Update* update);

    Update* lookup(const uint64_t key) const;

    bool fork(const UpdateSet::Type updateSetType);

    /**
     *
     * @throws MergeError
     */
    void merge();

    UpdateSet* currentUpdateSet() const;

    size_t size() const;

private:
    std::stack<UpdateSet*> m_updateSets;
};

class UpdateSetForkGuard final
{
public:
    UpdateSetForkGuard(const UpdateSet::Type type, UpdateSetManager* manager) :
        m_manager(manager)
    {
        m_wasForked = manager->fork(type);
    }

    ~UpdateSetForkGuard()
    {
        if (m_wasForked) {
            m_manager->merge();
        }
    }

private:
    UpdateSetManager* m_manager;
    bool m_wasForked;
};

#endif // _LIB_CASMFE_UPDATESET_H_

//
//  Local variables:
//  mode: c++
//  indent-tabs-mode: t
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//
