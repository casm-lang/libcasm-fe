#ifndef CASMI_LIBPARSE_SYMBOLS_H
#define CASMI_LIBPARSE_SYMBOLS_H

#include <string>
#include <stdexcept>
#include <map>
#include <vector>

#include "libsyntax/types.h"
#include "libsyntax/location.hh" // reuse bison's location class

class ExpressionBase;
class Expression;
class FunctionAtom;


bool is_builtin_name(const std::string& name);

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
