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

void UpdateSet::reserveAdditionally( std::size_t size )
{
    m_set.reserve( m_set.size() + size );
}

boost::optional< Update* > UpdateSet::lookup(
    const libcasm_fe::value_t* location ) const noexcept
{
    if( m_parent )
    {
        return m_parent->lookup( location );
    }

    return boost::none;
}

std::unique_ptr< UpdateSet > UpdateSet::fork(
    UpdateSet::Type updateSetType, std::size_t initialSize )
{
    switch( updateSetType )
    {
        case Type::Sequential:
            return std::unique_ptr< SequentialUpdateSet >(
                new SequentialUpdateSet( initialSize, this ) );
        case Type::Parallel:
            return std::unique_ptr< ParallelUpdateSet >(
                new ParallelUpdateSet( initialSize, this ) );
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

boost::optional< Update* > UpdateSet::get(
    const libcasm_fe::value_t* location ) const noexcept
{
    const auto it = m_set.find( location );
    if( it != m_set.end() )
    {
        return it.value();
    }

    return boost::none;
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

boost::optional< Update* > SequentialUpdateSet::lookup(
    const libcasm_fe::value_t* location ) const noexcept
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
, m_forked()
{
}

void UpdateSetManager::add(
    const libcasm_fe::value_t* location, Update* update )
{
    currentUpdateSet()->add( location, update );
}

boost::optional< Update* > UpdateSetManager::lookup(
    const libcasm_fe::value_t* location ) const noexcept
{
    if( m_updateSets.empty() )
    {
        return boost::none;
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
                m_updateSets.emplace_back(
                    new SequentialUpdateSet( initialSize ) );
                break;
            case UpdateSet::Type::Parallel:
                m_updateSets.emplace_back(
                    new ParallelUpdateSet( initialSize ) );
                break;
        }
    }
    else // only fork if necessary
    {
        const auto updateSet = currentUpdateSet();
        if( updateSet->type() == updateSetType )
        {
            // no need to fork the update set, use the current one
            updateSet->reserveAdditionally( initialSize );
            m_forked.push_back( false );
            return;
        }

        m_updateSets.emplace_back(
            updateSet->fork( updateSetType, initialSize ) );
    }

    m_forked.push_back( true );
}

void UpdateSetManager::merge()
{
    if( size() < 2 )
    {
        return;
    }

    const auto forked = m_forked.back();
    m_forked.pop_back();
    if( not forked )
    {
        // previous fork call didn't actually fork the update set
        return;
    }

    const auto updateSet = currentUpdateSet();
    updateSet->merge();
    m_updateSets.pop_back();
}

void UpdateSetManager::clear()
{
    m_updateSets.clear();
    m_forked.clear();
}

UpdateSet* UpdateSetManager::currentUpdateSet() const
{
    assert( not m_updateSets.empty() );
    return m_updateSets.back().get();
}

std::size_t UpdateSetManager::size() const noexcept
{
    assert( m_forked.size() >= m_updateSets.size() );
    return m_forked.size();
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
