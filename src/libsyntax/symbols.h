#ifndef CASMI_LIBPARSE_SYMBOLS_H
#define CASMI_LIBPARSE_SYMBOLS_H

#include <assert.h>

#include <string>
#include <stdexcept>
#include <map>
#include <vector>

#include <iostream>
#include "libsyntax/types.h"
#include "libsyntax/location.hh" // reuse bison's location class

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
    
    } id;
    
    
    std::vector< TypeType > ret_type;
    std::vector< std::vector< TypeType > > arg_type;
    
    std::function< void( Type*, std::vector< Type* >& )> unify_lambda;
    std::function< void( Driver&, BuiltinAtom*, Type*[], uint16_t )> typecheck_lambda;
    
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
           , std::function< void( Driver&, BuiltinAtom*, Type*[], uint16_t )> typecheck
             = [] ( Driver& driver, BuiltinAtom* atom, Type* arguments[], uint16_t length )
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
        
        typecheck_lambda( driver, atom, arguments, length );
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

    enum class SymbolType {
      FUNCTION,
      DERIVED,
      BUILTIN,
      ENUM,
      LET,
    };
    
    SymbolType type;

    Symbol(const std::string& name, SymbolType type);
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

    const bool is_static;
    const bool is_symbolic;

    std::vector<uint32_t> subrange_arguments;
    bool subrange_return;

    Function(const std::string name, std::vector<Type*>& args, Type* return_type,
           std::vector<std::pair<ExpressionBase*, ExpressionBase*>> *init);
    Function(bool is_static, bool is_symbolic, const std::string name,
             std::vector<Type*>& args, Type* return_type,
             std::vector<std::pair<ExpressionBase*, ExpressionBase*>> *init);
    Function(const std::string name, std::vector<Type*>& args, ExpressionBase *expr, Type* return_type);
    Function(const std::string name, ExpressionBase *expr, Type *return_type);
    ~Function();

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

    Enum(const std::string& name);
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

    bool add(Symbol *sym);

    bool remove(const std::string &name);

    bool add_enum_element(const std::string& name, Enum *enum_);

    Symbol* get(const std::string& name) const;

    Function* get_function(const std::string& name) const;

    Enum* get_enum(const std::string& name) const;

};

#endif
