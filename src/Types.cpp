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

#include "Types.h"

#include "Ast.h"
#include "Driver.h"

extern Driver* global_driver;

using namespace libcasm_fe;

Type::Type( const std::string& type_name, std::vector< Type* >& st )
: unify_with_left( nullptr )
, unify_with_right( nullptr )
, constraints()
, subtypes( st )
, enum_name()
{

    if( type_name == "List" )
    {
        t = TypeType::LIST;

        if( subtypes.size() == 0 )
        {
            subtypes.push_back( new Type( TypeType::UNKNOWN ) );
        }
        else if( subtypes.size() > 1 )
        {
            t = TypeType::INVALID;
        }
    }
    else if( type_name == "Tuple" )
    {
        if( subtypes.size() > 0 )
        {
            t = TypeType::TUPLE;
        }
        else
        {
            t = TypeType::INVALID;
        }
    }
}

Type::Type( TypeType typ, std::vector< Type* >& st )
: t( typ )
, unify_with_left( nullptr )
, unify_with_right( nullptr )
, constraints()
, subtypes( st )
, enum_name()
{

    if( t == TypeType::LIST )
    {
        t = TypeType::LIST;
        if( subtypes.size() == 0 )
        {
            subtypes.push_back( new Type( TypeType::UNKNOWN ) );
        }
        else if( subtypes.size() > 1 )
        {
            t = TypeType::INVALID;
        }
    }
    else if( t != TypeType::TUPLE_OR_LIST && t != TypeType::TUPLE )
    {
        t = TypeType::INVALID;
    }
}

Type::Type( TypeType typ, Type* subtype )
: t( typ )
, unify_with_left( nullptr )
, unify_with_right( nullptr )
, constraints()
, subtypes()
, enum_name()
{
    if( t != TypeType::LIST && t != TypeType::TUPLE_OR_LIST )
    {
        t = TypeType::INVALID;
    }
    subtypes.push_back( subtype );
}

Type::Type()
: t( TypeType::INVALID )
, unify_with_left( nullptr )
, unify_with_right( nullptr )
, constraints()
, subtypes()
, enum_name()
{
}

Type::Type( TypeType t )
: t( t )
, unify_with_left( nullptr )
, unify_with_right( nullptr )
, constraints()
, subtypes()
, enum_name()
{
    if( t == TypeType::LIST || t == TypeType::TUPLE )
    {
        t = TypeType::INVALID;
    }
}

Type::Type( Type* other )
: t( other->t )
, unify_with_left( nullptr )
, unify_with_right( nullptr )
, constraints()
, subtypes()
, enum_name( other->enum_name )
, subrange_start( other->subrange_start )
, subrange_end( other->subrange_end )
, bitsize( other->bitsize )
{
    for( Type* t : other->subtypes )
    {
        subtypes.push_back( new Type( t ) );
    }
}

Type::Type( const Type& other )
: t( other.t )
, unify_with_left( nullptr )
, unify_with_right( nullptr )
, constraints()
, subtypes( other.subtypes )
, enum_name( other.enum_name )
, subrange_start( other.subrange_start )
, subrange_end( other.subrange_end )
, bitsize( other.bitsize )
{
}

Type::Type( TypeType enum_type, const std::string& name )
: unify_with_left( nullptr )
, unify_with_right( nullptr )
, constraints()
, subtypes()
, enum_name( std::move( name ) )
{
    if( enum_type == TypeType::ENUM )
    {
        t = enum_type;
    }
    else
    {
        t = TypeType::INVALID;
    }
}

Type::Type( const std::string& type_name )
: unify_with_left( nullptr )
, unify_with_right( nullptr )
, constraints()
, subtypes()
{
    if( type_name == "Integer" )
    {
        t = TypeType::INTEGER;
    }
    else if( type_name == "Bit" )
    {
        t = TypeType::BIT;
    }
    else if( type_name == "Floating" )
    {
        t = TypeType::FLOATING;
    }
    else if( type_name == "Rational" )
    {
        t = TypeType::RATIONAL;
    }
    else if( type_name == "Undef" )
    {
        t = TypeType::UNDEF;
    }
    else if( type_name == "Boolean" )
    {
        t = TypeType::BOOLEAN;
    }
    else if( type_name == "RuleRef" )
    {
        t = TypeType::RULEREF;
    }
    else if( type_name == "String" )
    {
        t = TypeType::STRING;
    }
    else
    {
        // if the string does not match any known type assume enum;
        // make sure enum exists during typechecking
        t = TypeType::ENUM;
        enum_name = type_name;
    }
}

bool Type::eq( const Type& other ) const
{
    if( t != other.t )
    {
        return false;
    }

    if( subtypes.size() != other.subtypes.size() )
    {
        return false;
    }

    for( uint32_t i = 0; i < subtypes.size(); i++ )
    {
        if( *( subtypes[ i ] ) != *( other.subtypes[ i ] ) )
        {
            return false;
        }
    }

    return true;
}

bool Type::operator==( const Type& other ) const
{
    return eq( other );
}

bool Type::operator==( const TypeType other ) const
{
    return t == other;
}

bool Type::operator!=( const Type& other ) const
{
    return !eq( other );
}

const std::string Type::to_str() const
{
    switch( t )
    {
        case TypeType::INTEGER:
            if( has_range_restriction() )
            {
                return "Integer(" + std::to_string( subrange_start ) + ".."
                       + std::to_string( subrange_end ) + ")";
            }
            else
            {
                return "Integer";
            }
        case TypeType::BIT:
        {
            if( bitsize > 0 )
            {
                return "Bit(" + std::to_string( bitsize ) + ")";
            }
            else
            {
                return "Bit";
            }
        }
        case TypeType::FLOATING:
            return "Floating";
        case TypeType::RATIONAL:
            return "Rational";
        case TypeType::UNDEF:
            return "Undef";
        case TypeType::BOOLEAN:
            return "Boolean";
        case TypeType::RULEREF:
            return "RuleRef";
        case TypeType::STRING:
            return "String";
        case TypeType::LIST:
            if( subtypes.size() == 0 )
            {
                return "List(Undefined)";
            }
            else
            {
                return "List(" + subtypes[ 0 ]->to_str() + ")";
            }
        case TypeType::UNKNOWN:
            return "Undefined";
        case TypeType::SELF:
            return "Self";
        case TypeType::TUPLE_OR_LIST: /*{
          std::string res = "TupleOrList (";
          for (Type* t:subtypes) {
            res += t->to_str() + ",";
          }
          return res + ")";
        } */
        case TypeType::TUPLE:
        {
            std::string res = "Tuple (";
            for( Type* t : subtypes )
            {
                res += t->to_str() + ",";
            }
            return res + ")";
        }
        case TypeType::ENUM:
            return enum_name;
        case TypeType::INVALID:
            return "Invalid";
        case TypeType::NUMBER_RANGE:
            return "NumberRange";
        default:
            FAILURE();
    }
}

std::string Type::unify_links_to_str() const
{
    return unify_links_to_str_left() + " " + unify_links_to_str_right();
}

std::string Type::unify_links_to_str_left() const
{
    std::stringstream stream;
    stream << std::hex << this;
    std::string res = stream.str();

    if( unify_with_left )
    {
        res = unify_with_left->unify_links_to_str_left() + "<-" + res;
    }
    return res;
}
std::string Type::unify_links_to_str_right() const
{
    std::stringstream stream;
    stream << std::hex << this;
    std::string res = stream.str();

    if( unify_with_right )
    {
        res += "->" + unify_with_right->unify_links_to_str_right();
    }
    return res;
}

const Type* Type::get_most_general_type( AstNode* node ) const
{
    if( not is_complete() )
    {
        global_driver->warning( node->location, "type unification issue" );
    }

    //   std::cout << this << " THIS: " << this->to_str() << (is_complete() ?
    //   "COMPLETE" : "NOTCOMPLETE") << std::endl;
    //
    //   for (auto right = unify_with_right; right != nullptr; right =
    //   right->unify_with_right) {
    //     std::cout << this << " RIGHT: " << right->to_str() << std::endl;
    //   }
    //
    //   for (auto left = unify_with_left; left != nullptr; left =
    //   left->unify_with_left) {
    //     std::cout << this << " LEFT: " << left->to_str() << std::endl;
    //   }

    return this;
}

bool Type::unify( Type other )
{
    if( t == TypeType::UNKNOWN )
    {
        t = other.t;
        return true;
    }
    else if( other.t == TypeType::UNKNOWN )
    {
        other.t = t;
        return true;
    }

    return t == other.t;
}

bool Type::unify_list( Type* other )
{
    bool result = true;
    if( other->t == TypeType::LIST )
    {
        return subtypes[ 0 ]->unify( other->subtypes[ 0 ] );
    }
    else if( other->t == TypeType::TUPLE_OR_LIST )
    {
        bool internal_complete = subtypes[ 0 ]->is_complete();
        if( other->subtypes.size() > 0
            && other->subtypes[ 0 ]->t != TypeType::UNKNOWN )
        {
            for( Type* typ : other->subtypes )
            {
                result = result && typ->unify( subtypes[ 0 ] );
            }
        }
        if( result )
        {
            other->t = TypeType::LIST;
            other->subtypes = { new Type( subtypes[ 0 ] ) };
        }
        else
        {
            if( !internal_complete )
            {
                subtypes[ 0 ]->t = TypeType::UNKNOWN;
            }
        }
        return result;
    }
    else if( other->t == TypeType::TUPLE )
    {
        if( !is_complete() )
        {
            return false;
        }
        for( Type* typ : other->subtypes )
        {
            result = result && typ->unify( subtypes[ 0 ] );
        }
        if( result )
        {
            t = TypeType::TUPLE;
            subtypes = other->subtypes;
        }
        return result;
    }
    else if( other->t == TypeType::UNKNOWN )
    {
        if( other->constraints.size() > 0 )
        {
            // constraints cover only basic types at the moment
            return false;
        }
        other->subtypes = { new Type( TypeType::UNKNOWN ) };
        other->t = TypeType::LIST;
        return subtypes[ 0 ]->unify( other->subtypes[ 0 ] );
    }
    return false;
}

bool Type::unify_tuple( Type* other )
{
    if( other->t == TypeType::TUPLE_OR_LIST || other->t == TypeType::TUPLE )
    {
        bool result = true;
        other->t = TypeType::TUPLE;
        if( subtypes.size() == 0
            || ( subtypes.size() == 1
                   && subtypes[ 0 ]->t == TypeType::UNKNOWN ) )
        {
            subtypes = other->subtypes;
            return true;
        }
        else if( other->subtypes.size() == 0
                 || ( other->subtypes.size() == 1
                        && other->subtypes[ 0 ]->t == TypeType::UNKNOWN ) )
        {
            other->subtypes = subtypes;
            return true;
        }
        else if( subtypes.size() == other->subtypes.size() )
        {
            for( size_t i = 0; i < subtypes.size(); i++ )
            {
                result = result && subtypes[ i ]->unify( other->subtypes[ i ] );
            }
            return result;
        }
    }
    else if( other->t == TypeType::UNKNOWN )
    {
        if( other->constraints.size() > 0 )
        {
            // constraints cover only basic types at the moment
            return false;
        }
        other->t = t;
        other->subtypes = subtypes;
        return true;
    }

    // the case that other->t == TypeType::LIST should be covered prevoiusly by
    // unify_list
    return false;
}

bool Type::unify_tuple_or_list( Type* other )
{
    if( other->t == TypeType::TUPLE_OR_LIST )
    {
        if( subtypes.size() == 0
            || ( subtypes.size() == 1
                   && subtypes[ 0 ]->t == TypeType::UNKNOWN ) )
        {
            subtypes = other->subtypes;
            return true;
        }
        else if( other->subtypes.size() == 0
                 || ( other->subtypes.size() == 1
                        && other->subtypes[ 0 ]->t == TypeType::UNKNOWN ) )
        {
            other->subtypes = subtypes;
            return true;
        }
        else if( subtypes.size() == other->subtypes.size() )
        {
            bool result = true;
            for( size_t i = 0; i < subtypes.size(); i++ )
            {
                result = result && subtypes[ i ]->unify( other->subtypes[ i ] );
            }
            return result;
        }
        else
        {
            return false;
        }
    }
    else if( other->t == TypeType::UNKNOWN )
    {
        if( other->constraints.size() > 0 )
        {
            // constraints cover only basic types at the moment
            return false;
        }
        other->t = t;
        other->subtypes = subtypes;
        return true;
    }
    return false;
}

bool Type::unify_enum( Type* other )
{
    if( other->t == TypeType::ENUM )
    {
        if( enum_name.size() == 0 && other->enum_name.size() > 0 )
        {
            enum_name = other->enum_name;
        }
        else if( enum_name.size() > 0 && other->enum_name.size() == 0 )
        {
            other->enum_name = enum_name;
        }
        return enum_name == other->enum_name;
    }
    else if( other->t == TypeType::UNKNOWN )
    {
        if( other->constraints.size() > 0 )
        {
            // constraints cover only basic types at the moment
            return false;
        }
        other->t = TypeType::ENUM;
        other->enum_name = enum_name;
        return true;
    }
    return false;
}

bool Type::unify_nofollow( Type* other )
{
    if( t == TypeType::LIST )
    {
        return unify_list( other );
    }
    else if( other->t == TypeType::LIST )
    {
        return other->unify_list( this );
    }
    else if( t == TypeType::TUPLE )
    {
        return unify_tuple( other );
    }
    else if( other->t == TypeType::TUPLE )
    {
        return other->unify_tuple( this );
    }
    else if( t == TypeType::TUPLE_OR_LIST )
    {
        return unify_tuple_or_list( other );
    }
    else if( other->t == TypeType::TUPLE_OR_LIST )
    {
        return other->unify_tuple_or_list( this );
    }
    else if( t == TypeType::ENUM )
    {
        return unify_enum( other );
    }
    else if( other->t == TypeType::ENUM )
    {
        return other->unify_enum( this );
    }

    if( t != TypeType::UNKNOWN and other->t != TypeType::UNKNOWN )
    {
        return t == other->t;
    }

    if( other->t != TypeType::UNKNOWN )
    {
        t = other->t;
        if( t == TypeType::BIT )
        {
            bitsize = other->bitsize;
        }
        else if( t == TypeType::INTEGER )
        {
            subrange_start = other->subrange_start;
            subrange_end = other->subrange_end;
        }

        bool matched_constraint = true;
        for( Type constraint : constraints )
        {
            if( unify( constraint ) )
            {
                matched_constraint = true;
                break;
            }
            else
            {
                matched_constraint = false;
            }
        }

        if( !matched_constraint )
        {
            DEBUG( "Did not match any constriants" );
            return false;
        }
        return true;
    }

    if( t != TypeType::UNKNOWN )
    {
        other->t = t;
        if( t == TypeType::BIT )
        {
            other->bitsize = bitsize;
        }
        else if( t == TypeType::INTEGER )
        {
            other->subrange_start = subrange_start;
            other->subrange_end = subrange_end;
        }

        bool matched_constraint = true;
        for( Type constraint : other->constraints )
        {
            if( unify( constraint ) )
            {
                matched_constraint = true;
                break;
            }
            else
            {
                matched_constraint = false;
            }
        }

        if( !matched_constraint )
        {
            DEBUG( "Did not match any constriants" );
            return false;
        }
        return true;
    }

    return true;
}

bool Type::unify_left( Type* other )
{
    if( other == nullptr )
    {
        return true;
    }

    if( other->unify_with_left != nullptr )
    {
        return unify_nofollow( other ) and unify_left( other->unify_with_left );
    }
    else
    {
        return unify_nofollow( other );
    }
}

bool Type::unify_right( Type* other )
{
    if( other == nullptr )
    {
        return true;
    }

    if( other->unify_with_right != nullptr )
    {
        return unify_nofollow( other )
               and unify_right( other->unify_with_right );
    }
    else
    {
        return unify_nofollow( other );
    }
}

bool Type::is_unknown() const
{
    if( t == TypeType::UNKNOWN )
    {
        return true;
    }
    else if( t == TypeType::TUPLE || t == TypeType::TUPLE_OR_LIST )
    {
        if( subtypes.empty() or ( subtypes.size() == 1
                                    && subtypes[ 0 ]->t == TypeType::UNKNOWN ) )
        {
            return true;
        }
    }
    return false;
}

bool Type::unify( Type* other )
{
    if( is_unknown() and other->is_unknown() )
    {
        Type* left_link = this;
        while( left_link->unify_with_left != nullptr )
        {
            if( left_link == other )
            {
                return true;
            }
            left_link = left_link->unify_with_left;
        }

        Type* right_link = other;
        while( right_link->unify_with_right != nullptr )
        {
            if( right_link == this )
            {
                return true;
            }
            right_link = right_link->unify_with_right;
        }

        left_link = other;
        while( left_link->unify_with_left != nullptr )
        {
            if( left_link == this )
            {
                return true;
            }
            left_link = left_link->unify_with_left;
        }

        right_link = this;
        while( right_link->unify_with_right != nullptr )
        {
            if( right_link == other )
            {
                return true;
            }
            right_link = right_link->unify_with_right;
        }

        left_link->unify_with_left = right_link;
        right_link->unify_with_right = left_link;
        return true;
    }

    if( unify_nofollow( other ) )
    {
        return unify_left( other->unify_with_left )
               and unify_left( unify_with_left )
               and unify_right( other->unify_with_right )
               and unify_right( unify_with_right );
    }

    return false;
}

bool Type::is_complete() const
{
    switch( t )
    {
        case TypeType::UNKNOWN:
            return false;
        case TypeType::LIST:
        case TypeType::TUPLE:
        case TypeType::TUPLE_OR_LIST:
            if( subtypes.empty() )
            {
                assert( !"internal error: syntax issue" );
                return false;
            }
            else
            {
                for( Type* type : subtypes )
                {
                    if( not type->is_complete() )
                    {
                        return false;
                    }
                }
                return true;
            }
        default:
            return true;
    }
}

bool Type::has_range_restriction() const
{
    return subrange_start < subrange_end;
}
