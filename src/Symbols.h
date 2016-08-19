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

#ifndef CASMI_LIBPARSE_SYMBOLS_H
#define CASMI_LIBPARSE_SYMBOLS_H

#include <assert.h>

#include <string>
#include <map>
#include <vector>
#include <functional>

#include <iostream>
#include "Types.h"
#include "Value.h"
#include "Exceptions.h"
#include "various/location.hh" // reuse bison's location class

class ExpressionBase;
class Expression;
class FunctionAtom;
class BuiltinAtom;
class Driver;

struct Builtin
{    
public:
    std::string name;
    
    enum class Id
    // general built-ins
    { SYMBOLIC

    // tuple and list built-ins
    , NTH
    , CONS
    , APP
    , LEN
    , TAIL
    , PEEK

    // casting built-ins
    , AS_INTEGER
    , AS_BOOLEAN
    , AS_FLOATING
    , AS_BIT
    , AS_ENUM
    , AS_STRING
    , AS_RATIONAL
    
    // stringify built-ins
    , DEC
    , HEX
    , BIN
    
    // math built-ins
    , POW
    , RAND

    // bit-vector built-ins
    // TODO: PPA: CONTINUE HERE!!!
    , ZEXT
    , SEXT
    , TRUNC
    , SHL
    , SHR
    , ASHR

    , ADDU
    , SUBU
    , MULU
    , DIVU
    , MODU
    , GREU
    , GEQU
    , LESU
    , LEQU
    , EQUU
    , NEQU
    
    , ADDS
    , SUBS
    , MULS
    , DIVS
    , MODS
    , GRES
    , GEQS
    , LESS
    , LEQS
    , EQUS
    , NEQS
   
    } id;
    
    
    std::vector< TypeType > ret_type;
    std::vector< std::vector< TypeType > > arg_type;
    
    std::function< void( Type*, std::vector< Type* >& )> unify_lambda;
    std::function< void( Builtin&, Driver&, BuiltinAtom*, Type*[], uint16_t )> typecheck_lambda;
    
private:
    static std::map< Id, Builtin* > id2obj;
    static std::map< std::string, Builtin* > str2obj;
    static std::vector< Builtin > list;
    
public:
    Builtin( const std::string name
           , Id id
           , std::vector< TypeType > ret_type
           , std::vector< std::vector< TypeType >> arg_type
           , std::function< void( Type*, std::vector< Type* >& )> unify
             = [] ( Type* ret, std::vector< Type* >& arg )
             {
             }
           , std::function< void( Builtin&, Driver&, BuiltinAtom*, Type*[], uint16_t )> typecheck
             = [] ( Builtin& self, Driver& driver, BuiltinAtom* atom, Type* arguments[], uint16_t length )
             {
             }
           )
    : name( name )
    , id( id )
    , ret_type( ret_type )
    , arg_type( arg_type )
    , unify_lambda( unify )
    , typecheck_lambda( typecheck )
    {
        assert( !isBuiltin( id ) && "multiple IDs for built-ins symbol table" );
        id2obj[ id ] = this;
        
        assert( ! isBuiltin( name ) && "multiple names for built-ins symbol table" );
        str2obj[ name ] = this;
    }
    
    void unify( Type* ret, std::vector< Type* >& arg )
    {
        assert( ret && "invalid return Type pointer" );

        unify_lambda( ret, arg );
    }
    
    void typecheck( Driver& driver, BuiltinAtom* atom, Type* arguments[], uint16_t length )
    {
        assert( atom && "invalid BUILTIN AST atom pointer" );
        assert( arguments && "invalid argument Type array pointer" );
        
        typecheck_lambda( *this, driver, atom, arguments, length );
    }
    
    static bool isBuiltin( const std::string& name )
    {
        if( str2obj.count( name ) != 0 )
        {
            return true;
        }
        return false;
    }
    
    static bool isBuiltin( Id id )
    {
        if( id2obj.count( id ) != 0 )
        {
            return true;
        }
        return false;
    }
    
    static Builtin* get( const std::string& name )
    {
        //std::cout << std::string(__FUNCTION__) << ": lookup of '" << name << "'\n";
        auto result = str2obj.find( name );
        if( result != str2obj.end() )
        {
            //std::cout << std::string(__FUNCTION__) << ": lookup of '" << name << "' @ '" << result->second << "'\n";
            return result->second;
        }
        else
        {
            return 0;
        }
    }

    static Builtin* get( Id id )
    {
        auto result = id2obj.find( id );
        if( result != id2obj.end() )
        {
            return result->second;
        }
        else
        {
            return 0;
        }
    }
};



class Symbol {
  public:
    const std::string name;
    const yy::location location;

    enum class SymbolType {
      FUNCTION,
      DERIVED,
      BUILTIN,
      ENUM,
      LET,
    };
    
    SymbolType type;

    Symbol(const std::string& name, const yy::location& location, SymbolType type);
};

class Function : public Symbol {
  private:
    static uint64_t counter;

  public:
    std::vector<Type*> arguments_;

    union {
      std::vector<std::pair<ExpressionBase*, ExpressionBase*>> *intitializers_;
      ExpressionBase *derived;
    };

    Type *return_type_;
    const uint64_t id;

    std::map<std::string, size_t> binding_offsets;
    std::vector< const char* > parameter;
    
    const bool is_static;
    const bool is_symbolic;

    std::vector<uint32_t> subrange_arguments;
    bool subrange_return;

    Function(const std::string name, const yy::location& location, std::vector<Type*>& args, Type* return_type,
           std::vector<std::pair<ExpressionBase*, ExpressionBase*>> *init);
    Function(bool is_static, bool is_symbolic, const std::string name, const yy::location& location,
             std::vector<Type*>& args, Type* return_type,
             std::vector<std::pair<ExpressionBase*, ExpressionBase*>> *init);
    Function(const std::string name, const yy::location& location, std::vector<Type*>& args, ExpressionBase *expr, Type* return_type);
    Function(const std::string name, const yy::location& location, ExpressionBase *expr, Type *return_type);
    ~Function();

    /**
       @throws std::domain_error if any argument is out of range
    */
    void validateArguments(uint32_t num_arguments, const value_t arguments[]) const;

    /**
       @throws std::domain_error if value is out of range
    */
    void validateValue(const value_t &value) const;
    
    bool equals(Function *other) const;
    const std::string to_str() const;
    inline size_t argument_count() const {
      return arguments_.size();
    }

    bool is_builtin();
};

struct enum_value_t {
  const std::string *name;
  const uint16_t id;

  enum_value_t(const std::string *name, const uint16_t id);
};

class Enum : public Symbol {
  public:
    // TODO use unordered_map here, but ordering cannot be garantueed in 
    // forall
    std::map<std::string, enum_value_t*> mapping;

    Enum(const std::string& name, const yy::location& location);
    bool add_enum_element(const std::string& name);
};

class Binding {
  private:
    static uint64_t counter;

  public:
    const uint64_t id;
    const std::string name;
    Type type;

    Binding(const std::string& name);
    Binding(const std::string& name, Type t);
};

class SymbolTable {
  public:
    std::map<std::string, Symbol*> table_;

    SymbolTable();

    ~SymbolTable();

    size_t size() const;

    /**
     * @throws SymbolAlreadyExists when the symbol table contains a symbol with
     *         the same name as the name of \a sym.
     */
    void add(Symbol *sym);

    bool remove(const std::string &name);

    /**
     * @throws SymbolAlreadyExists when the symbol table contains a symbol with
     *         the same name as \a name.
     */
    void add_enum_element(const std::string& name, Enum *enum_);

    Symbol* get(const std::string& name) const;

    Function* get_function(const std::string& name) const;

    Enum* get_enum(const std::string& name) const;

  private:
    void add_or_throw(const std::string& name, Symbol *sym);
};

#endif
