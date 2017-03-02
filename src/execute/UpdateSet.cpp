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

#include "UpdateSet.h"

#include "cpp/Default.h"

UpdateSet::Conflict::Conflict(
    const std::string& msg, Update* conflictingUpdate, Update* existingUpdate )
: std::logic_error( msg )
, m_conflictingUpdate( conflictingUpdate )
, m_existingUpdate( existingUpdate )
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

UpdateSet::UpdateSet( std::size_t initialSize, UpdateSet* parent )
: m_set( initialSize )
, m_parent( parent )
{
}

bool UpdateSet::empty() const noexcept
{
    return m_set.empty();
}

std::size_t UpdateSet::size() const noexcept
{
    return m_set.size();
}

void UpdateSet::reserveAdditionally(std::size_t size)
{
    m_set.reserve( m_set.size() + size );
}

Update* UpdateSet::lookup( const libcasm_fe::value_t* location ) const noexcept
{
    if( m_parent )
    {
        return m_parent->lookup( location );
    }

    return nullptr;
}

UpdateSet* UpdateSet::fork(
    UpdateSet::Type updateSetType, std::size_t initialSize )
{
    switch( updateSetType )
    {
        case Type::Sequential:
            return new SequentialUpdateSet( initialSize, this );
        case Type::Parallel:
            return new ParallelUpdateSet( initialSize, this );
    }
}

void UpdateSet::merge()
{
    assert( m_parent != nullptr );

    if( m_parent->m_set.empty() )
    {
        std::swap( m_parent->m_set, m_set );
    }
    else
    {
        m_parent->reserveAdditionally( m_set.size() );
        const auto end = m_set.end();
        for( auto it = m_set.begin(); it != end; ++it )
        {
            m_parent->add( it.key(), it.value() );
        }
    }
}

typename UpdateSet::const_iterator UpdateSet::begin() const noexcept
{
    return m_set.begin();
}

typename UpdateSet::const_iterator UpdateSet::end() const noexcept
{
    return m_set.end();
}

Update* UpdateSet::get( const libcasm_fe::value_t* location ) const noexcept
{
    const auto it = m_set.find( location );
    return ( it != m_set.end() ) ? it.value() : nullptr;
}

UpdateSet::Type SequentialUpdateSet::type() const noexcept
{
    return Type::Sequential;
}

void SequentialUpdateSet::add(
    const libcasm_fe::value_t* location, Update* update )
{
    m_set.insertOrAssign( location, update );
}

Update* SequentialUpdateSet::lookup( const libcasm_fe::value_t* location ) const
    noexcept
{
    const auto it = m_set.find( location );
    if( it != m_set.end() )
    {
        return it.value();
    }

    return UpdateSet::lookup( location );
}

UpdateSet::Type ParallelUpdateSet::type() const noexcept
{
    return Type::Parallel;
}

void ParallelUpdateSet::add(
    const libcasm_fe::value_t* location, Update* update )
{
    const auto result = m_set.insert( location, update );
    if( !result.second )
    {
        const auto it = result.first;
        const auto existingUpdate = it.value();

        if( update->value != existingUpdate->value )
        {
            throw Conflict( "Conflict in updateset", update, existingUpdate );
        }
    }
}

UpdateSetManager::UpdateSetManager()
: m_updateSets()
{
}

UpdateSetManager::~UpdateSetManager()
{
    clear();
}

void UpdateSetManager::add(
    const libcasm_fe::value_t* location, Update* update )
{
    currentUpdateSet()->add( location, update );
}

Update* UpdateSetManager::lookup( const libcasm_fe::value_t* location ) const
    noexcept
{
    if( m_updateSets.empty() )
    {
        return nullptr;
    }
    else
    {
        return currentUpdateSet()->lookup( location );
    }
}

void UpdateSetManager::fork(
    UpdateSet::Type updateSetType, std::size_t initialSize )
{
    if( m_updateSets.empty() )
    {
        switch( updateSetType )
        {
            case UpdateSet::Type::Sequential:
                m_updateSets.push( new SequentialUpdateSet( initialSize ) );
                break;
            case UpdateSet::Type::Parallel:
                m_updateSets.push( new ParallelUpdateSet( initialSize ) );
                break;
        }
    }
    else
    {
        const auto updateSet = currentUpdateSet();
        const auto forkedUpdateSet
            = updateSet->fork( updateSetType, initialSize );
        m_updateSets.push( forkedUpdateSet );
    }
}

void UpdateSetManager::merge()
{
    if( size() > 1 )
    {
        const auto updateSet = currentUpdateSet();
        updateSet->merge();
        m_updateSets.pop();
        delete updateSet;
    }
}

void UpdateSetManager::clear()
{
    while( not m_updateSets.empty() )
    {
        delete m_updateSets.top();
        m_updateSets.pop();
    }
}

UpdateSet* UpdateSetManager::currentUpdateSet() const
{
    assert( not m_updateSets.empty() );
    return m_updateSets.top();
}

std::size_t UpdateSetManager::size() const noexcept
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
