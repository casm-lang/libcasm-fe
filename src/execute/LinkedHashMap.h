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

#ifndef _LIB_CASMFE_LINKEDHASHMAP_H_
#define _LIB_CASMFE_LINKEDHASHMAP_H_

#include <unordered_map>

/**
 * A single-linked-hash-map
 */
template <typename Key, typename Value, typename Hash = std::hash<Key>, typename Pred = std::equal_to<Key>>
class LinkedHashMap
{
    struct Node
    {
        Node* prev = nullptr;
        std::pair<Key, Value> value;
    };

public:
    class iterator
    {
    public:
        using difference_type = std::ptrdiff_t;
        using value_type = std::pair<Key, Value>;
        using reference = value_type&;
        using pointer = value_type*;
        using iterator_category = std::forward_iterator_tag;

        explicit iterator(Node* node) :
            m_node(node)
        {

        }

        iterator(const iterator& rhs) :
            m_node(rhs.m_node)
        {

        }

        iterator& operator=(const iterator& rhs) noexcept
        {
            this->m_node = rhs.m_node;
            return *this;
        }

        bool operator==(const iterator& rhs) const noexcept
        {
            return this->m_node == rhs.m_node;
        }

        bool operator!=(const iterator& rhs) const noexcept
        {
            return this->m_node != rhs.m_node;
        }

        iterator& operator++() noexcept
        {
            m_node = m_node->prev;
            return *this;
        }

        iterator& operator++(int) noexcept
        {
            auto i = *this;
            m_node = m_node->prev;
            return i;
        }

        reference operator*() const noexcept
        {
            return m_node->value;
        }

        pointer operator->() const noexcept
        {
            return &(m_node->value);
        }

    private:
        Node* m_node;
    };

    class const_iterator
    {
    public:
        using difference_type = std::ptrdiff_t;
        using value_type = std::pair<Key, Value>;
        using const_reference = const value_type&;
        using const_pointer = const value_type*;
        using iterator_category = std::forward_iterator_tag;

        explicit const_iterator(const Node* node) :
            m_node(node)
        {

        }

        const_iterator(const const_iterator& rhs) :
            m_node(rhs.m_node)
        {

        }

        const_iterator& operator=(const const_iterator& rhs) noexcept
        {
            this->m_node = rhs.m_node;
            return *this;
        }

        bool operator==(const const_iterator& rhs) const noexcept
        {
            return this->m_node == rhs.m_node;
        }

        bool operator!=(const const_iterator& rhs) const noexcept
        {
            return this->m_node != rhs.m_node;
        }

        const_iterator& operator++() noexcept
        {
            m_node = m_node->prev;
            return *this;
        }

        const_iterator& operator++(int) noexcept
        {
            auto i = *this;
            m_node = m_node->prev;
            return i;
        }

        const_reference operator*() const noexcept
        {
            return m_node->value;
        }

        const_pointer operator->() const noexcept
        {
            return &(m_node->value);
        }

    private:
        const Node* m_node;
    };

public:
    using value_type = std::pair<Key, Value>;
    using size_type = size_t;

    explicit LinkedHashMap(size_type n) :
        m_map(n)
    {

    }

    bool empty() const noexcept
    {
        return m_map.empty();
    }

    size_type size() const noexcept
    {
        return m_map.size();
    }

    iterator begin() noexcept
    {
        return iterator(m_lastNode);
    }

    const_iterator begin() const noexcept
    {
        return const_iterator(m_lastNode);
    }

    const_iterator cbegin() const noexcept
    {
        return const_iterator(m_lastNode);
    }

    iterator end() noexcept
    {
        return iterator(nullptr);
    }

    const_iterator end() const noexcept
    {
        return const_iterator(nullptr);
    }

    const_iterator cend() const noexcept
    {
        return const_iterator(nullptr);
    }

    std::pair<iterator, bool> insert(const value_type& pair)
    {
        auto node = new Node; // TODO PE allocate with block allocator?!
        node->prev = m_lastNode;
        node->value = pair;

        const auto result = m_map.insert(std::make_pair(pair.first, node));
        if (result.second) {
            m_lastNode = node;
        }

        const auto it = result.first;
        return std::make_pair(iterator(it->second), result.second);
    }

    std::pair<iterator, bool> insert(const Key& key, const Value& value)
    {
        return insert(std::make_pair(key, value));
    }

    Value& operator[](const Key& key) {
        return (*((insert(std::make_pair(key, Value()))).first)).second;
    }

    Value& at(const Key& key)
    {
        return m_map.at(key)->value.second;
    }

    const Value& at(const Key& key) const
    {
        return m_map.at(key)->value.second;
    }

    iterator find(const Key& key)
    {
        const auto it = m_map.find(key);
        if (it == m_map.end()) {
            return end();
        }

        return iterator(it->second);
    }

    const_iterator find(const Key& key) const
    {
        const auto it = m_map.find(key);
        if (it == m_map.cend()) {
            return cend();
        }

        return const_iterator(it->second);
    }

    void clear()
    {
        const auto end = m_map.end();
        for (auto it = m_map.begin(); it != end; ++it) {
            delete it->second;
        }

        m_map.clear();
        m_lastNode = nullptr;
    }

    void reserve(size_type n)
    {
        m_map.reserve(n);
    }

private:
    std::unordered_map<Key, Node*, Hash, Pred> m_map;
    Node* m_lastNode = nullptr;
};

#endif // _LIB_CASMFE_LINKEDHASHMAP_H_

//
//  Local variables:
//  mode: c++
//  indent-tabs-mode: nil
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//
