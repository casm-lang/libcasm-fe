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

#include "UpdateSet.h"

#include <algorithm>
#include <cassert>

UpdateSet::Conflict::Conflict(const std::string& msg,
                              Update* conflictingUpdate,
                              Update* existingUpdate) :
    std::logic_error(msg),
    m_conflictingUpdate(conflictingUpdate),
    m_existingUpdate(existingUpdate)
{

}

Update* UpdateSet::Conflict::conflictingUpdate() const noexcept
{
    return m_conflictingUpdate;
}

Update* UpdateSet::Conflict::existingUpdate() const noexcept
{
    return m_existingUpdate;
}

UpdateSet::UpdateSet(Type type, UpdateSet* parent) :
    m_parent(parent),
    m_type(type),
    m_set(100)
{

}

UpdateSet::~UpdateSet()
{
    clear();
}

UpdateSet::Type UpdateSet::type() const noexcept
{
    return m_type;
}

bool UpdateSet::empty() const noexcept
{
    return m_set.empty();
}

size_t UpdateSet::size() const noexcept
{
    return m_set.size();
}

void UpdateSet::add(const uint64_t key, Update* update)
{
    if (m_type == Type::Parallel) {
        const auto result = m_set.insert(key, update);
        if (!result.second) {
            const auto existingPair = *(result.first);
            const auto existingUpdate = existingPair.second;

            if (update->value != existingUpdate->value) {
                throw Conflict("Conflict in updateset", update, existingUpdate);
            }
        }
    } else {
        m_set[key] = update;
    }
}

Update* UpdateSet::lookup(const uint64_t key) const
{
    if (m_type == Type::Sequential) {
        const auto it = m_set.find(key);
        if (it != m_set.cend()) {
            return it->second;
        }
    }

    if (m_parent) {
        return m_parent->lookup(key);
    }

    return nullptr;
}

UpdateSet *UpdateSet::fork(const UpdateSet::Type updateSetType)
{
    return new UpdateSet(updateSetType, this);
}

void UpdateSet::merge()
{
    if (m_parent->m_set.empty()) {
        std::swap(m_parent->m_set, m_set);
    } else {
        m_parent->m_set.reserve(m_parent->m_set.size() + m_set.size());
        for(const auto& pair : m_set) {
            m_parent->add(pair.first, pair.second);
        }
        clear();
    }
}

void UpdateSet::clear()
{
    m_set.clear();
}

typename UpdateSet::const_iterator UpdateSet::cbegin() const noexcept
{
    return m_set.cbegin();
}

typename UpdateSet::const_iterator UpdateSet::cend() const noexcept
{
    return m_set.cend();
}

Update* UpdateSet::get(const uint64_t key) const noexcept
{
    const auto it = m_set.find(key);
    return (it != m_set.cend()) ? it->second : nullptr;
}

UpdateSetManager::UpdateSetManager() :
    m_updateSets()
{

}

UpdateSetManager::~UpdateSetManager()
{
    clear();
}

void UpdateSetManager::add(const uint64_t key, Update* update)
{
    assert(!m_updateSets.empty());
    m_updateSets.top()->add(key, update);
}

Update* UpdateSetManager::lookup(const uint64_t key) const
{
    if (m_updateSets.empty()) {
      return nullptr;
    } else {
      return m_updateSets.top()->lookup(key);
    }
}

void UpdateSetManager::fork(const UpdateSet::Type updateSetType)
{
    if (m_updateSets.empty()) {
        m_updateSets.push(new UpdateSet(updateSetType));
    } else {
        auto currentUpdateSet = m_updateSets.top();
        auto forkedUpdateSet = currentUpdateSet->fork(updateSetType);
        m_updateSets.push(forkedUpdateSet);
    }
}

void UpdateSetManager::merge()
{
    if (m_updateSets.size() > 1) {
        auto currentUpdateSet = m_updateSets.top();
        currentUpdateSet->merge();
        m_updateSets.pop();
        delete currentUpdateSet;
    }
}

void UpdateSetManager::clear()
{
    while (!m_updateSets.empty()) {
        delete m_updateSets.top();
        m_updateSets.pop();
    }
}

UpdateSet* UpdateSetManager::currentUpdateSet() const
{
    return m_updateSets.top();
}

size_t UpdateSetManager::size() const
{
    return m_updateSets.size();
}

//
//  Local variables:
//  mode: c++
//  indent-tabs-mode: nil
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//
