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

#ifndef CASMI_LIBINTERPRETER_VALUE_H
#define CASMI_LIBINTERPRETER_VALUE_H

#include "Macros.h"
#include "Types.h"

struct enum_value_t;

class RuleNode;
class BinaryExpression;

class HeadList;
class TailList;
class BottomList;
class List;

class NumberRange;

struct symbolic_condition_t;
struct symbol_t;
struct rational_t;

class value_t
{
  public:
    TypeType type;
    union {
        INTEGER_T integer;
        FLOATING_T float_;
        bool boolean;
        RuleNode* rule;
        std::string* string;
        List* list;
        const enum_value_t* enum_val;
        const rational_t* rat;
        symbol_t* sym;
        NumberRange* numberRange;
    } value;

    value_t();
    value_t( INTEGER_T integer );
    value_t( uint64_t integer );
    value_t( FLOATING_T float_ );
    value_t( bool boolean );
    value_t( RuleNode* rule );
    value_t( std::string* string );
    value_t( const Type& t, List* list );
    value_t( const enum_value_t* enum_val );
    value_t( const rational_t* val );
    value_t( symbol_t* sym );
    value_t( NumberRange* numberRange );
    value_t( const value_t& other );
    value_t( value_t&& other ) noexcept;

    value_t& operator=( const value_t& other );
    bool operator==( const value_t& other ) const;
    bool operator!=( const value_t& other ) const;

    bool is_undef() const;
    bool is_symbolic() const;

    const std::string to_str( bool symbolic = false ) const;
};

value_t operator or( const value_t& lhs, const value_t& rhs );
value_t operator and( const value_t& lhs, const value_t& rhs );
value_t operator^( const value_t& lhs, const value_t& rhs );

value_t operator+( const value_t& lhs, const value_t& rhs );
value_t operator-( const value_t& lhs, const value_t& rhs );
value_t operator*( const value_t& lhs, const value_t& rhs );
value_t operator/( const value_t& lhs, const value_t& rhs );
value_t operator%( const value_t& lhs, const value_t& rhs );

value_t operator<( const value_t& lhs, const value_t& rhs );
value_t operator>( const value_t& lhs, const value_t& rhs );
value_t operator<=( const value_t& lhs, const value_t& rhs );
value_t operator>=( const value_t& lhs, const value_t& rhs );

struct rational_t
{
    int64_t numerator;
    int64_t denominator;

    rational_t();
    rational_t( int64_t num, int64_t denom );
    rational_t( const rational_t& other );

    bool operator==( const rational_t& other ) const;
    const rational_t& operator+( const rational_t& other ) const;
    const rational_t& operator-( const rational_t& other ) const;
    const rational_t& operator*( const rational_t& other ) const;
    const rational_t& operator/( const rational_t& other ) const;
    const rational_t& operator%( const rational_t& other ) const;

    const std::string to_str() const;
};

class NumberRange
{
  private:
    INTEGER_T m_bottom;
    INTEGER_T m_top;

  public:
    NumberRange();
    NumberRange( INTEGER_T bottom, INTEGER_T top );
    NumberRange( const NumberRange& other );

    class const_iterator
    {
      public:
        using difference_type = INTEGER_T;
        using value_type = INTEGER_T;
        using const_reference = const value_type&;
        using const_pointer = const value_type*;
        using iterator_category = std::forward_iterator_tag;

        const_iterator( INTEGER_T number );
        const_iterator( const const_iterator& rhs );

        const_iterator& operator=( const const_iterator& rhs ) noexcept;

        bool operator==( const const_iterator& rhs ) const noexcept;
        bool operator!=( const const_iterator& rhs ) const noexcept;

        const_iterator& operator++() noexcept;
        const_iterator operator++(int)noexcept;

        const_reference operator*() const noexcept;

      private:
        INTEGER_T m_number;
    };

    INTEGER_T bottom() const noexcept;
    INTEGER_T top() const noexcept;

    bool operator==( const NumberRange& other ) const;
    bool operator!=( const NumberRange& other ) const;

    const_iterator begin() const;
    const_iterator end() const;

    const std::string to_str() const;
};

class List
{
  public:
    enum class ListType
    {
        HEAD,
        BOTTOM,
        SKIP,
        TAIL,
    };

    class const_iterator
    {
      public:
        typedef const_iterator self_type;
        typedef value_t value_type;
        typedef value_t& reference;
        typedef int difference_type;
        typedef std::forward_iterator_tag iterator_category;

        const_iterator( const List* ptr );
        const_iterator( const self_type& other );
        self_type operator++();
        self_type operator++( int );
        void next();
        const value_t& operator*();
        // const pointer operator->() { return ptr_; }
        bool operator==( const self_type& rhs ) const;
        bool operator!=( const self_type& rhs ) const;

      private:
        const BottomList* bottom;
        const HeadList* head;
        const TailList* tail;
        uint32_t pos;

        void do_init( const List* other );
    };

    ListType list_type;

    List( ListType t );
    virtual ~List()
    {
    }

    bool operator==( const List& other ) const;
    bool operator!=( const List& other ) const;

    bool is_bottom() const;
    bool is_head() const;
    bool is_skip() const;
    bool is_tail() const;

    const_iterator begin() const;
    const_iterator end() const;

    const std::string to_str() const;

    void bump_usage();
    void decrease_usage();

    BottomList* collect();
};

class HeadList : public List
{
  public:
    List* right;
    const value_t current_head;

    HeadList( List* right, const value_t& val );
};

class TailList : public List
{
  public:
    TailList* right;
    const value_t current_tail;

    TailList( TailList* right, const value_t& val );

    void collect( std::vector< value_t >& collect_to );
};

class BottomList : public List
{
    friend class List;

  private:
    uint32_t usage_count;
    bool allocated_in_collect;

  public:
    std::vector< value_t > values;

    TailList* tail;

    BottomList();
    BottomList( const std::vector< value_t >& vals );

    virtual ~BottomList();

    bool is_used() const;
    bool check_allocated_and_set_to_false();
};

class SkipList : public List
{
  public:
    size_t skip;
    BottomList* bottom;

    SkipList( size_t skip, BottomList* btm );
};

namespace std
{

    template <>
    struct hash< HeadList >;

    template <>
    struct hash< value_t >
    {
        size_t operator()( const value_t& key ) const;
    };

    template <>
    struct hash< std::vector< value_t > >
    {
        static std::hash< value_t > hasher;

        size_t operator()( const std::vector< value_t >& key ) const;
    };

    template <>
    struct hash< HeadList >
    {
        static std::hash< value_t > hasher;

        size_t operator()( const HeadList& key ) const;
    };

    template <>
    struct hash< BottomList >
    {
        static std::hash< std::vector< value_t > > list_hasher;

        size_t operator()( const BottomList& key ) const;
    };
}

std::string to_string( const std::vector< value_t >& values );

#endif
