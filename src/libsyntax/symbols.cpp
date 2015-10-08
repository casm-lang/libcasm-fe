
#include <cmath>

#include "libsyntax/ast.h"
#include "libsyntax/driver.h"
#include "libsyntax/symbols.h"

std::map< Builtin::Id, Builtin* > Builtin::id2obj;
std::map< std::string, Builtin* > Builtin::str2obj;


//  { "builtinName"
//  , Builtin::Id::BUILTIN_ID
//  , { ... } possible return types
//  , { { ... possible 0. argument types
//      }
//    , { ... possible 1. argument types
//      }
//    }
//  , [] ( Type* ret, std::vector< Type* >& arg )
//    {
//        unification procedure for this builtin
//    }
//  , [] ( Driver& driver, BuiltinAtom* atom, Type* arguments[], uint16_t length )
//    {
//        typecheck & type-patch procedure for this builtin
//    }
//  }

Builtin built_ins[] =
{ { "symbolic"
  , Builtin::Id::SYMBOLIC
  , { TypeType::BOOLEAN }
  , { { TypeType::UNKNOWN
      }
    }
  }

, { "nth"
  , Builtin::Id::NTH
  , { TypeType::UNKNOWN }
  , { { TypeType::TUPLE_OR_LIST
      , TypeType::UNKNOWN
      }
    , { TypeType::INTEGER
      }
    }
  , [] ( Type* ret, std::vector< Type* >& arg )
    {
        arg[0]->subtypes[0]->unify( ret );
    }
  }

// {"cons", true},
, { "cons"
  , Builtin::Id::CONS
  , { TypeType::LIST }
  , { { TypeType::UNKNOWN
      }
    , { TypeType::LIST
      }
    }
  , [] ( Type* ret, std::vector< Type* >& arg )
    {
        arg[0]->unify( arg[1]->subtypes[0] );
        arg[1]->unify( ret );
    }
  }

// {"app", true},
, { "app"
  , Builtin::Id::APP
  , { TypeType::LIST }
  , { { TypeType::UNKNOWN
      }
    , { TypeType::LIST
      }
    }
  , [] ( Type* ret, std::vector< Type* >& arg )
    {
        arg[0]->unify( arg[1]->subtypes[0] );
        arg[1]->unify( ret );
        // TODO: PPA: FIXME: maybe swap arg 0 and 1, wha? @fhahn ?
    }
  }


// {"len", true},
, { "len"
  , Builtin::Id::LEN
  , { TypeType::INTEGER }
  , { { TypeType::LIST
      }
    }
  }

  
// {"tail", true},
, { "tail"
  , Builtin::Id::TAIL
  , { TypeType::UNKNOWN }
  , { { TypeType::LIST
      }
    }
  , [] ( Type* ret, std::vector< Type* >& arg )
    {
        arg[0]->unify( ret );
    }
  }

  
// {"peek", true},
, { "peek"
  , Builtin::Id::PEEK
  , { TypeType::UNKNOWN }
  , { { TypeType::LIST
      }
    }
  , [] ( Type* ret, std::vector< Type* >& arg )
    {
        arg[0]->subtypes[0]->unify( ret );
    }
  }




  
    // //===--- CASTING BUILT-INS ---====
    // // asInteger : Boolean  -> Integer // false -> 0, true -> 1, undef -> undef
    // // asInteger : Floating -> Integer // cut of comma value to integer, undef -> undef
    // // asInteger : Bit( n ) -> Integer // n is a integer constant, always use unsigned semantics
    // // asInteger : e        -> Integer // e -> index(e), e !in index(e) -> undef, undef -> undef
    // //                                 // 'e' is a enumeration value of type 'e'
    // {"asInteger", true},
, { "asInteger"
  , Builtin::Id::AS_INTEGER
  , { TypeType::INTEGER }
  , { { TypeType::UNKNOWN
      , TypeType::BOOLEAN
      , TypeType::FLOAT
      , TypeType::BIT
      , TypeType::ENUM
      }
    }
  }
  
    // // asBoolean : Integer  -> Boolean // 0 -> false, other -> true
    // // asBoolean : Floating -> Boolean // SHALL NOT BE POSSIBLE !!! ERROR
    // // asBoolean : Bit( n ) -> Boolean // SHALL NOT BE POSSIBLE where n != 1 !!! ERROR
    // // asBoolean : Bit( 1 ) -> Boolean // 0b0 -> false, 0b1 -> true
    // // asBoolean : e        -> Boolean // SHALL NOT BE POSSIBLE !!! ERROR
    // //                                 // 'e' is a enumeration value of type 'e'
    // {"asBoolean", true},
, { "asBoolean"
  , Builtin::Id::AS_BOOLEAN
  , { TypeType::BOOLEAN }
  , { { TypeType::UNKNOWN
      , TypeType::INTEGER
      , TypeType::BIT
      , TypeType::ENUM
      }
    }
    // PPA: TODO: FIXME: the Bit(1) check !!! see above!
  }

    // // asFloating : Integer  -> Floating // int to float converstion!
    // // asFloating : Boolean  -> Floating // false -> 0.0, true -> 1.0
    // // asFloating : Bit( n ) -> Floating // SHALL NOT BE POSSIBLE
    // // asFloating : e        -> Floating // e -> index(e).0, e !in index(e) -> undef, undef -> undef
    // //                                   // 'e' is a enumeration value of type 'e'
    // {"asFloating", true},
, { "asFloating"
  , Builtin::Id::AS_FLOATING
  , { TypeType::FLOAT }
  , { { TypeType::UNKNOWN
      , TypeType::INTEGER
      , TypeType::BOOLEAN
      , TypeType::BIT
      , TypeType::ENUM
      }
    }
  }

  
  // // asBit : Integer  * Integer (const, n) -> Bit( n ) // only possible if integer fits into bit-width,
  // //                                                   // unsigned semantic only which means e.g.:
  // //                                                   // -1 is a 64-bit integer value and has to fit in at least Bit( 64 )
  // // asBit : Boolean  * Integer (const, n) -> Bit( n ) // false -> 0b0, true -> 0b1
  // // asBit : Floating * Integer (const, n) -> Bit( n ) // SHALL NOT BE POSSIBLE (YET! maybe later!)
  // // asBit : e        * Integer (const, n) -> Bit( n ) // only possible if enum value 'e' fits into bit-width!

, { "asBit"
  , Builtin::Id::AS_BIT
  , { TypeType::BIT }
  , { { TypeType::UNKNOWN
      , TypeType::INTEGER
      , TypeType::BOOLEAN
      , TypeType::FLOAT
      , TypeType::ENUM
      }
    , { TypeType::INTEGER }
    }
  , [] ( Type* ret, std::vector< Type* >& arg )
    {
        ret->unify( arg[1] );
    }
  , [] ( Driver& driver, BuiltinAtom* atom, Type* arguments[], uint16_t length )
    {
        assert( length == 2 && "invalid argument length for builtin" );
        
        ExpressionBase *expr_bitsize = atom->arguments->at( 1 );
        if( expr_bitsize->node_type_ != NodeType::INTEGER_ATOM )
        {
            driver.error
            ( atom->arguments->at(1)->location
            , "second argument of 'asBit' builtin must be a Integer constant"
            );
            
            return;
        }
        
        INTEGER_T bitsize = static_cast< IntegerAtom* >( expr_bitsize )->val_;
        if( bitsize <= 0 or bitsize > 256 )
        {
            driver.error
            ( atom->arguments->at(1)->location
            , "second argument of 'asBit' builtin must be in the range from 1 to 256"
            );
            
            return;
        }
        
        atom->return_type->bitsize = bitsize;        
        
        
        INTEGER_T value = -1;
        INTEGER_T value_bitsize = -1;
        
        ExpressionBase* expr_value = atom->arguments->at( 0 );
        if( expr_value->node_type_ == NodeType::INTEGER_ATOM )
        {
            value = static_cast< IntegerAtom* >( expr_value )->val_;
            double v = (double)value;
            v = log2( v );
            v = std::ceil( v );
            value_bitsize = (INTEGER_T)v;
        }
        else if( expr_value->node_type_ == NodeType::FUNCTION_ATOM )
        {
            driver.warning
            ( atom->arguments->at(0)->location
            , "first argument of 'asBit' builtin will be truncated to bitsize '" + std::to_string( bitsize ) + "'"
            );
            
            return;
        }
        else
        {
            assert( !"unimplemented value type for 'asBit' builtin to check value bitsize fitting!" );
        }
        
        printf( "%s: %i, %i\n", atom->name.c_str(), value, value_bitsize );
        
        if( value_bitsize > bitsize )
        {
            driver.error
            ( atom->arguments->at(0)->location
            , "first argument of 'asBit' builtin does not fit into the bitsize of '" + std::to_string( bitsize ) + "'"
            );            
        }
    }
  }

    // // asEnum : Integer  -> e // iff Integer value is in { indexes of e }
    // // asEnum : Boolean  -> e // SHALL NOT BE POSSIBLE
    // // asEnum : Floating -> e // SHALL NOT BE POSSIBLE
    // // asEnum : Bit( n ) -> e // iff Bit(n) value is in { indexes of e }
    // // // 'e' is a enumeration value of type 'e'
    // {"asEnum", true},
, { "asEnum"
  , Builtin::Id::AS_ENUM
  , { TypeType::ENUM }
  , { { TypeType::UNKNOWN
      , TypeType::INTEGER
      , TypeType::BOOLEAN
      , TypeType::FLOAT
      , TypeType::BIT
      }
    }
  }

    // // asString : Integer  -> String // SHALL NOT BE POSSIBLE !!! ERROR  --> use 'dec'
    // // asString : Boolean  -> String // false -> "false", true -> "true"
    // // asString : Floating -> String // SHALL NOT BE POSSIBLE !!! ERROR  --> use 'dec'
    // // asString : Bit( n ) -> String // SHALL NOT BE POSSIBLE !!! ERROR  --> use 'dec'
    // // asString : e        -> String // string represenation of enum value 'e'
    // {"asString", true},
, { "asString"
  , Builtin::Id::AS_STRING
  , { TypeType::STRING }
  , { { TypeType::UNKNOWN
      , TypeType::INTEGER
      , TypeType::FLOAT
      , TypeType::BIT
      , TypeType::ENUM
//    , TypeType::RATIONAL
      }
    }
  }

  
// // TODO: PPA: define a clear semantic for this type cast!
// {"asRational", true},
, { "asRational"
  , Builtin::Id::AS_RATIONAL
  , { TypeType::RATIONAL }
  , { { TypeType::UNKNOWN
      , TypeType::INTEGER
      , TypeType::FLOAT
      , TypeType::RATIONAL
      }
    }
  }

  
    // //===--- STRINGIFY BUILT-INS ---====
    // // dec  : Integer  -> String  // decimal representation of integer
    // // dec  : Boolean  -> String  // decimal representation of boolean
    // // dec  : Floating -> String  // decimal representation of floating point value
    // // dec  : Bit( n ) -> String  // decimal representation of bit-vector
    // // dec  : e        -> String  // decimal representation of enumeration value of type 'e'
    // {"dec", true},
, { "dec"
  , Builtin::Id::DEC
  , { TypeType::STRING }
  , { { TypeType::UNKNOWN
      , TypeType::INTEGER
      , TypeType::BOOLEAN
      , TypeType::FLOAT
      , TypeType::BIT
      , TypeType::ENUM
//    , TypeType::RATIONAL
      }
    }
  }

    // // hex  : Integer  -> String  // hexadecimal representation of integer WITHOUT prefix '0x'
    // // hex  : Boolean  -> String  // hexadecimal representation of boolean WITHOUT prefix '0x'
    // // hex  : Floating -> String  // hexadecimal representation of floating point value WITHOUT prefix '0x'
    // // hex  : Bit( n ) -> String  // hexadecimal representation of bit-vector WITHOUT prefix '0x'
    // // hex  : e        -> String  // hexadecimal representation of enumeration value of type 'e' WITHOUT prefix '0x'
    // {"hex", true},
, { "hex"
  , Builtin::Id::HEX
  , { TypeType::STRING }
  , { { TypeType::UNKNOWN
      , TypeType::INTEGER
      , TypeType::BOOLEAN
      , TypeType::FLOAT
      , TypeType::BIT
      , TypeType::ENUM
//    , TypeType::RATIONAL
      }
    }
  }

    // // bin  : Integer  -> String  // binary representation of integer WITHOUT prefix '0b'
    // // bin  : Boolean  -> String  // binary representation of boolean WITHOUT prefix '0b'
    // // bin  : Floating -> String  // binary representation of floating point value WITHOUT prefix '0b'
    // // bin  : Bit( n ) -> String  // binary representation of bit-vector WITHOUT prefix '0b'
    // // bin  : e        -> String  // binary representation of enumeration value of type 'e' WITHOUT prefix '0b'
    // {"bin", true},
, { "bin"
  , Builtin::Id::BIN
  , { TypeType::STRING }
  , { { TypeType::UNKNOWN
      , TypeType::INTEGER
      , TypeType::BOOLEAN
      , TypeType::FLOAT
      , TypeType::BIT
      , TypeType::ENUM
//    , TypeType::RATIONAL
      }
    }
  }


    // //===--- INTEGER MATH BUILT-INS ---====
    // // pow  : Integer * Integer -> Integer
    // // //     base      exponent
    // {"pow", true},
, { "pow"
  , Builtin::Id::POW
  , { TypeType::INTEGER }
  , { { TypeType::INTEGER
      }
    , { TypeType::INTEGER
      }
    }
  }

    // // rand : Integer * Integer -> Integer
    // // //     start     end
    // {"rand", true},
, { "rand"
  , Builtin::Id::RAND
  , { TypeType::INTEGER }
  , { { TypeType::INTEGER
      }
    , { TypeType::INTEGER
      }
    }
  }

  
    // //===--- BIT OPERATION BUILT-INS ---====
    // // zext  : Bit( n ) * Integer (const, m) -> Bit( m ) // zero extend to new size, if m < n then error!
    // {"zext", true},

    // // sext  : Bit( n ) * Integer (const, m) -> Bit( m ) // sign extend to new size, if m < n then error!
    // {"sext", true},

    // // trunc : Bit( n ) * Integer (const, m) -> Bit( m ) // truncate to new size, if m > n then error!
    // {"trunc", true},

    // // shl   : Bit( n ) * Integer  -> Bit( n ) // logic shift left of Integer value positions
    // // shl   : Bit( n ) * Bit( n ) -> Bit( n ) // logic shift left of Bit(n) value positions
    // {"shl", true},

    // // shr   : Bit( n ) * Integer  -> Bit( n ) // logic shift right of Integer value positions
    // // shr   : Bit( n ) * Bit( n ) -> Bit( n ) // logic shift right of Bit(n) value positions
    // {"shr", true},

    // // ashr  : Bit( n ) * Integer  -> Bit( n ) // arithmetic shift right of Integer value positions
    // // ashr  : Bit( n ) * Bit( n ) -> Bit( n ) // arithmetic shift right of Bit(n) value positions
    // {"ashr", true},
  
    // // clz   : Bit( n ) -> Bit( n ) // count leading zeros
    // {"clz", true},
  
    // // clo   : Bit( n ) -> Bit( n ) // count leading ones
    // {"clo", true},

    // // cls   : Bit( n ) -> Bit( n ) // count leading sign bits
    // {"cls", true},


};




Symbol::Symbol(const std::string& name, SymbolType type) : name(std::move(name)), type(type) {}

// -------------------------------------------------------------------------
// Implementation of Function
// -------------------------------------------------------------------------

uint64_t Function::counter = 0;

Function::Function(const std::string name, std::vector<Type*>& args,
                  Type* return_type,
                  std::vector<std::pair<ExpressionBase*, ExpressionBase*>> *init) :
    Function(false, false, name, args, return_type, init) {
    
}

Function::Function(bool is_static, bool is_symbolic, const std::string name,
             std::vector<Type*>& args, Type* return_type,
             std::vector<std::pair<ExpressionBase*, ExpressionBase*>> *init) :
                Symbol(name, SymbolType::FUNCTION), arguments_(std::move(args)), intitializers_(init),
                return_type_(return_type), id(counter),
                is_static(is_static), is_symbolic(is_symbolic),
                subrange_arguments(), subrange_return(false) {

  counter += 1;
  if (return_type->subrange_start < return_type->subrange_end) {
    subrange_return = true;
  }
  for (uint32_t i=0; i < arguments_.size(); i++) {
    Type* t = arguments_[i];
    if (t->subrange_start < t->subrange_end) {
      subrange_arguments.push_back(i);
    }
  }
}

Function::Function(const std::string name, std::vector<Type*>& args,
                   ExpressionBase *expr, Type* return_type) :
                Symbol(name, SymbolType::DERIVED), arguments_(std::move(args)), derived(expr),
                return_type_(return_type), id(counter),
                is_static(false), is_symbolic(false) {
  counter += 1;
}

Function::Function(const std::string name,
                   ExpressionBase *expr, Type* return_type) :
                Symbol(name, SymbolType::DERIVED), arguments_(), derived(expr),
                return_type_(return_type), id(counter), is_static(false), is_symbolic(false) {
  counter += 1;
}


Function::~Function() {
  arguments_.clear();
  if (intitializers_ != nullptr) {
    for (std::pair<ExpressionBase*, ExpressionBase*> e : *intitializers_) {
      delete e.first;
      delete e.second;
    }
    delete intitializers_;
  }
}

const std::string Function::to_str() const {
  std::string res = name;

  res = ": (";
  for (Type* t : arguments_) {
    res += t->to_str() + ", ";
  }
  res += ")";
  res += "-> "+return_type_->to_str();
  return res;
}

bool Function::equals(Function *other) const {
  if (name != other->name) {
    return false;
  }

  if (arguments_.size() != other->arguments_.size()) {
    return false;
  }
  for (size_t i=0; i < arguments_.size(); i++) {
    if (arguments_[i] != other->arguments_[i]) {
      return false;
    }
  }
  return return_type_ == other->return_type_;
}

bool Function::is_builtin()
{
    if( Builtin::isBuiltin( name ) )
    {
        type = SymbolType::BUILTIN;
        return true;
    }
    return false;
}

enum_value_t::enum_value_t(const std::string *name, const uint16_t id)
    : name(name), id(id) {}

Enum::Enum(const std::string& name) : Symbol(name, Symbol::SymbolType::ENUM), mapping() {}

bool Enum::add_enum_element(const std::string& name) {
  if (mapping.count(name) == 0) {
    mapping[name] = new enum_value_t(new std::string(name), mapping.size());
    return true;
  } else {
    return false;
  }
}

uint64_t Binding::counter = 0;

Binding::Binding(const std::string& name) : Binding(name, Type(TypeType::UNKNOWN)) {}

Binding::Binding(const std::string& name, Type t) : id(counter), name(name),
    type(t)
{
  counter += 1;
}

SymbolTable::SymbolTable() {}

SymbolTable::~SymbolTable() {

  // cleanup symbol table
  /* TODO: check if element wise cleanup is needed
  for (auto entry : table_) {
    delete entry.second;
  }
  */
}

size_t SymbolTable::size() const {
  return table_.size();
}

bool SymbolTable::add(Symbol *sym) {
  try {
    table_.at(sym->name);
    return false;
  } catch (const std::out_of_range& e) {
    table_[sym->name] = sym;
    return true;
  }
}

bool SymbolTable::remove(const std::string& name) {
  try {
    table_.at(name);
    table_.erase(name);
    return true;
  } catch (const std::out_of_range& e) {
    return false;
  }
}


bool SymbolTable::add_enum_element(const std::string& name, Enum *enum_) {
  try {
    table_.at(name);
    return false;
  } catch (const std::out_of_range& e) {
    table_[name] = enum_;
    return true;
  }
}


Symbol* SymbolTable::get(const std::string& name) const {
  try {
    return table_.at(name);
  } catch (const std::out_of_range& e) {
    return nullptr;
  }
}

 Function* SymbolTable::get_function(const std::string& name) const {
  try {
    Symbol* sym = table_.at(name);
    // TODO split Function and Derived symbols?
    if (sym->type == Symbol::SymbolType::FUNCTION || sym->type == Symbol::SymbolType::DERIVED) {
      return reinterpret_cast<Function*>(sym);
    } else {
      return nullptr;
    }
  } catch (const std::out_of_range& e) {
    return nullptr;
  }
}

Enum* SymbolTable::get_enum(const std::string& name) const {
  try {
    Symbol* sym = table_.at(name);
    // TODO split Function and Derived symbols?
    if (sym->type == Symbol::SymbolType::ENUM) {
      return reinterpret_cast<Enum*>(sym);
    } else {
      return nullptr;
    }
  } catch (const std::out_of_range& e) {
    return nullptr;
  }
}
