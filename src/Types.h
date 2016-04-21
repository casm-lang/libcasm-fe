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
//  along with this program. If not, see <http://www.gnu.org/licenses/>.
//  

#ifndef CASMI_LIBPARSE_TYPES_H
#define CASMI_LIBPARSE_TYPES_H

#include <assert.h>
#include <cstdint>
#include <vector>
#include <string>
#include <map>
#include <sstream>

#include "Macros.h"

#define INTEGER_T int64_t
#define FLOAT_T double

class CompoundType;

enum class TypeType {
  STRING,
  RULEREF,
  INTEGER,
  BIT,
  FLOAT,
  BOOLEAN,
  SELF,
  UNKNOWN,
  INVALID,
  NO_TYPE,
  LIST,
  TUPLE,
  TUPLE_OR_LIST,
  ENUM,
  RATIONAL,
  UNDEF,    // only possible during execution in value_t.type
  SYMBOL,   // only possible during execution in value_t.type
};

class Type;


class Type {
  private:
    bool eq(const Type& other) const;
    bool unify_list(Type *other);
    bool unify_tuple(Type *other);
    bool unify_tuple_or_list(Type *other);
    bool unify_enum(Type *other);

  public:
    TypeType t;
    Type *unify_with_left;
    Type *unify_with_right;

    std::vector<Type*> constraints;
    std::vector<Type*> subtypes;

    std::string enum_name;

    INTEGER_T subrange_start = 0;
    INTEGER_T subrange_end = -1;

    INTEGER_T bitsize = -1;
    
    Type();
    Type(TypeType t);
    Type(const Type& other);
    Type(const std::string &type_name, std::vector<Type*>& internal_types);
    Type(TypeType t, std::vector<Type*>& internal_types);
    Type(TypeType t, Type *int_typ);
    Type(const std::string& type_name);
    Type(TypeType enum_type, const std::string& type_name);
    Type(Type *other);


    bool operator==(const Type& other) const;
    bool operator==(const TypeType other) const;

    bool operator!=(const Type& other) const;

    virtual const std::string to_str() const;
    virtual std::string unify_links_to_str() const;
    virtual std::string unify_links_to_str_left() const;
    virtual std::string unify_links_to_str_right() const;

    // unify with temporary type
    bool unify(Type other);

    // unify types of ast nodes
    bool unify(Type *other);

    bool unify_right(Type *other);

    bool unify_left(Type *other);

    bool unify_nofollow(Type *other);


    const Type* get_most_general_type() const;
    bool is_complete() const;
    bool is_unknown() const;
};


#endif
