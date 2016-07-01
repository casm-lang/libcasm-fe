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

struct ArgumentsKey {
  const value_t* p;
  uint32_t size;
  bool dynamic;

  // size must be equal to the size specified in the function type
  ArgumentsKey(const value_t args[], uint32_t size, bool dyn);
  ArgumentsKey(const ArgumentsKey& other);
  ArgumentsKey(ArgumentsKey&& other) noexcept;
  ~ArgumentsKey();
};



namespace std {

  template <> struct hash<ArgumentsKey> {
    size_t operator()(const ArgumentsKey &key) const {
      size_t h = 0;
      for (uint32_t i = 0; i < key.size; i++) {
        if (key.p[i].is_symbolic()) {
          h ^= reinterpret_cast<size_t>(key.p[i].value.sym);
        } else {
          static std::hash<value_t> value_hasher;
          h ^= value_hasher(key.p[i]);
        }
      }
      return h;
    }
  };

  template <> struct equal_to<ArgumentsKey> {
    bool operator()(const ArgumentsKey &lhs, const ArgumentsKey &rhs) const {
      for (uint32_t i = 0; i < lhs.size; i++) {
        if (lhs.p[i] != rhs.p[i]) {
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
    BlockAllocator<TEMP_STACK_SIZE> pp_stack;
    std::map<const std::string, bool> debuginfo_filters;

  public:
    std::vector<std::unordered_map<ArgumentsKey, value_t>> function_states;
    std::vector<const Function*> function_symbols;
    const SymbolTable symbol_table;
    UpdateSetManager updateSetManager;
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

    Update* add_update(const value_t& val, size_t sym_id, uint32_t num_arguments, value_t arguments[], uint64_t line);
    void apply_updates();

    void fork(const UpdateSet::Type updateSetType);
    void merge();

    const value_t get_function_value(Function *sym, uint32_t num_arguments, const value_t arguments[]);

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
