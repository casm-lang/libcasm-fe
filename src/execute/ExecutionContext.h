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

#ifndef _LIB_CASMFE_EXECUTIONCONTEXT_H_
#define _LIB_CASMFE_EXECUTIONCONTEXT_H_

class Driver;

#include <vector>
#include <unordered_map>

#include "UpdateSet.h"
#include "../allocator/BlockAllocator.h"
#include "../Symbols.h"
#include "../Value.h"

#define UPDATESET_SIZE 65536 //* 64
#define UPDATESET_DATA_SIZE UPDATESET_SIZE //* 50
#define TEMP_STACK_SIZE 32768
#define VALUE_STACK_SIZE 32768

static Type symbol_type(TypeType::SYMBOL);

struct ArgumentsKey {
  uint64_t* p;
  bool dynamic;
  uint16_t sym_args;

  // size must be equal to the size specified in the function type
  ArgumentsKey(uint64_t *args, uint16_t size, bool dyn, uint16_t sym_args);
  ArgumentsKey(const ArgumentsKey& other);
  ArgumentsKey(ArgumentsKey&& other) noexcept;
  ~ArgumentsKey();
};



namespace std {

  template <> struct hash<ArgumentsKey> {
    std::vector<Type*> types;

    size_t operator()(const ArgumentsKey &key) const {
      size_t h = 0;
      for(uint16_t i = 0; i < types.size(); i++) {
        if ((key.sym_args & (1 << i)) != 0) {
          h ^= hash_uint64_value(&symbol_type, key.p[i]);
        } else {
          h ^= hash_uint64_value(types[i], key.p[i]);
        }
      }
      return h;
    }
  };

  template <> struct equal_to<ArgumentsKey> {
    std::vector<Type*> types;

    bool operator()(const ArgumentsKey &lhs, const ArgumentsKey &rhs) const {
      for(uint16_t i = 0; i < types.size(); i++) {
        if (!eq_uint64_value(types[i], lhs.p[i], rhs.p[i])) {
          return false;
        }
      }
      return true;
    }
  };
}


class ExecutionContext {
  private:
    BlockAllocator<UPDATESET_DATA_SIZE> updateset_data_;
    std::map<const std::string, bool> debuginfo_filters;

  public:
    std::vector<std::unordered_map<ArgumentsKey, value_t>> function_states;
    std::vector<const Function*> function_symbols;
    const SymbolTable symbol_table;
    UpdateSetManager updateSetManager;
    BlockAllocator<TEMP_STACK_SIZE> pp_stack;
    std::vector<List*> temp_lists;
    static BlockAllocator<VALUE_STACK_SIZE> value_stack;
    const bool symbolic;
    const bool fileout;
    const bool dump_updates;

    std::vector<std::string> trace_creates;
    std::vector<std::string> trace;
    std::vector<std::string> update_dump;
    std::string path_name;
    std::vector<symbolic_condition_t*> path_conditions;

    ExecutionContext(const SymbolTable& st, RuleNode *init, const bool symbolic,
        const bool fileout, const bool dump_updates);
    ExecutionContext(const ExecutionContext& other);

    void apply_updates();

    const value_t get_function_value(Function *sym, uint64_t args[], uint16_t sym_args);

    bool set_debuginfo_filter(const std::string& filters);
    bool filter_enabled(const std::string& filter);
};

#endif // _LIB_CASMFE_EXECUTIONCONTEXT_H_

//
//  Local variables:
//  mode: c++
//  indent-tabs-mode: t
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//
