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

#include "ExecutionContext.h"

#include <sstream>
#include <utility>

#include "Symbolic.h"
#include "../Driver.h"
#include "../Ast.h"

ArgumentsKey::ArgumentsKey(uint64_t *args, uint16_t size, bool dyn,
    uint16_t syms) : dynamic(dyn), sym_args(syms) {
  if (dynamic) {
    p = new uint64_t[size];
    for (uint16_t i = 0; i < size; i++) {
      p[i] = args[i];
    }
  } else {
    p = args;
  }
}

ArgumentsKey::ArgumentsKey(const ArgumentsKey& other) : p(other.p),
    dynamic(other.dynamic), sym_args(other.sym_args) {
}

ArgumentsKey::ArgumentsKey(ArgumentsKey&& other) noexcept {
  p = other.p;
  dynamic = other.dynamic;
  other.dynamic = false;
  sym_args = other.sym_args;
}

ArgumentsKey::~ArgumentsKey() {
  if (dynamic) {
    delete[] p;
  }
}

std::string arguments_to_string(const Function *func, const uint64_t args[]) {
  std::stringstream ss;
  if (func->arguments_.size() == 0) {
    return "";
  }
  for (uint32_t i = 0; i < func->arguments_.size(); i++) {
    Update up = {
        .num_args = 0,
        .value = (void*) args[i],
    };
    ss << up.value.to_str();
    ss << ", ";
  }
  // Strip trailing comma
  return "("+ss.str().substr(0, ss.str().size()-2)+")";
}

BlockAllocator<VALUE_STACK_SIZE> ExecutionContext::value_stack;

ExecutionContext::ExecutionContext(const SymbolTable& st, RuleNode *init,
    const bool symbolic, const bool fileout, const bool dump_updates): debuginfo_filters(),
    symbol_table(std::move(st)), temp_lists(), symbolic(symbolic), fileout(fileout),
    dump_updates(dump_updates), trace_creates(), trace(), update_dump(),
    path_name(""), path_conditions() {

  //pp_mem_new(&updateset_data_, UPDATESET_DATA_SIZE, "mem for updateset hashmap"); FIXME?
  //updateset.set =  pp_hashmap_new(&updateset_data_, UPDATESET_SIZE, "main updateset");

  assert(init->child_ && init->child_->node_type_ == NodeType::PARBLOCK);

  function_states = std::vector<std::unordered_map<ArgumentsKey, value_t>>(symbol_table.size());
  function_symbols = std::vector<const Function*>(symbol_table.size());
  Function *program_sym = symbol_table.get_function("program");
  // TODO location is wrong here
  program_sym->intitializers_ = new std::vector<std::pair<ExpressionBase*, ExpressionBase*>>();
  RuleAtom *init_atom = new RuleAtom(init->location, std::string(init->name));
  init_atom->rule = init;
  program_sym->intitializers_->push_back(std::make_pair(new SelfAtom(init->location), init_atom));

}

ExecutionContext::ExecutionContext(const ExecutionContext& other) : 
     debuginfo_filters(other.debuginfo_filters), symbol_table(other.symbol_table),
     symbolic(other.symbolic), fileout(other.fileout), dump_updates(other.dump_updates),
     trace(other.trace), update_dump(other.update_dump), path_name(other.path_name) {

  // TODO copy updates!
  //pp_mem_new(&updateset_data_, UPDATESET_DATA_SIZE, "mem for updateset hashmap");  FIXME?
  //updateset.set =  pp_hashmap_new(&updateset_data_, UPDATESET_SIZE, "main updateset");
}

void ExecutionContext::apply_updates() {
  std::unordered_map<uint32_t, std::vector<ArgumentsKey>> updated_functions;
  if (symbolic || dump_updates) {
    for (uint32_t i = 0; i < function_states.size(); i++) {
      updated_functions[i] = std::vector<ArgumentsKey>();
    }
  }

  assert(updateSetManager.size() == 1);

  auto updateSet = updateSetManager.currentUpdateSet();
  std::vector<value_t*> to_fold;
  const auto end = updateSet->cend();
  for (auto it = updateSet->cbegin(); it != end; ++it) {
    Update* u = it->second;

    auto& function_map = function_states[u->func];
    // TODO handle tuples
    if (u->value.type == TypeType::LIST) {
      value_t& list = function_map[ArgumentsKey(u->args, u->num_args, false, u->sym_args)];
      if (u->value.is_symbolic()){
        function_map[ArgumentsKey(u->args, u->num_args, true, u->sym_args)] = u->value;
      } else if (u->value.is_undef()) {
        // set list to undef
        if (!list.is_undef()) {
          list.value.list->decrease_usage();
          list.type = TypeType::UNDEF;
        }
      } else {
        if (!list.is_undef() && !list.is_symbolic()) {
          list.value.list->decrease_usage();
        } else {
          list.type = u->value.type;
        }
        list.value.list = u->value.value.list;
        list.value.list->bump_usage();
        to_fold.push_back(&list);
      }
    } else {
      // we could erase keys that store an undef value in concrete mode,
      // but we need to know if a key was set to undef explicitly in symbolic
      // mode
      function_map[ArgumentsKey(u->args, u->num_args, true, u->sym_args)] = u->value;
    }

    if (symbolic || dump_updates) {
      updated_functions[u->func].push_back(
            ArgumentsKey(u->args, u->num_args, true, u->sym_args));
    }
  }
  updateSet->clear();
  assert(updateSet->empty());

  if (symbolic) {
    for (uint32_t i = 1; i < function_states.size(); i++) {
      auto& function_map = function_states[i];
      const Function* function_symbol = function_symbols[i];
      const auto& updated_keys = updated_functions[i];
      if (!function_symbol->is_symbolic || function_symbol->is_static) {
        continue;
      }

      std::equal_to<ArgumentsKey> eq = {function_symbol->arguments_};
      for (const auto& pair : function_map) {
        bool found = false;
        for (const auto& k : updated_keys) {
          if (eq(k, pair.first)) {
            found = true;
            break;
          }
        }
        if (!found) {
          symbolic::dump_symbolic(trace, function_symbol, pair.first.p,
              pair.first.sym_args, pair.second);
        }
      }
      for (const auto& k : updated_keys) {
        symbolic::dump_update(trace, function_symbol, k.p,
         k.sym_args, function_map[k]);
      }
    }
  }

  if (dump_updates) {
    for (uint32_t i = 0; i < function_states.size(); i++) {
      auto& function_map = function_states[i];
      const Function* function_symbol = function_symbols[i];
      const auto& updated_keys = updated_functions[i];

      for (const auto& k : updated_keys) {
        update_dump.push_back(function_symbol->name+
            arguments_to_string(function_symbol, k.p)+" = "+
            function_map[k].to_str());
      }
    }

    std::stringstream ss;
    for (auto s : update_dump) {
      ss << s << ", ";
    }
    std::cout << "{ " << ss.str().substr(0, ss.str().size()-2) << " }" << std::endl;
    update_dump.clear();
  }


  // Handle lists
  // 1. convert chained lists to BottomLists
  for (value_t* v : to_fold) {
    BottomList *new_l = v->value.list->collect();
    if (new_l->check_allocated_and_set_to_false()) {
      temp_lists.push_back(new_l);
    }
    v->value.list = new_l;
  }
  to_fold.clear(); 
  std::vector<size_t> deleted;

  // delete all list objects, except BottomLists that are currently used
  for (size_t i=0; i < temp_lists.size(); i++) {
    if (!(temp_lists[i]->is_bottom() && reinterpret_cast<BottomList*>(temp_lists[i])->is_used())) {
      delete temp_lists[i];
      deleted.push_back(i);
    }
  }

  // remove deleted lists from temp_lists
  for (size_t del : deleted) {
    temp_lists[del] = std::move(temp_lists.back());
    temp_lists.pop_back();
  }
  // list handling done

  // free allocated updateset data
  updateset_data_.freeAll();
  pp_stack.freeAll();
}

static value_t undef = value_t();

static value_t tmp;

bool args_eq(uint64_t args1[], uint64_t args2[], size_t len) {

  for (size_t i=0; i < len; i++) {
    if (args1[i] != args2[i]) {
      return false;
    }
  }
  return true;
}

const value_t ExecutionContext::get_function_value(Function *sym, uint64_t args[], uint16_t sym_args) {
  auto& function_map = function_states[sym->id];
  try {
    const value_t &v = function_map.at(ArgumentsKey(&args[0], sym->arguments_.size(), false, sym_args));
    const auto update = updateSetManager.lookup(reinterpret_cast<uint64_t>(&v));
    if (update) {
        return update->value;
    } else {
        return v;
    }
  } catch (const std::out_of_range &e) {
    if (symbolic && sym->is_symbolic) {
      // TODO cleanup symbol
      function_map.emplace(
          ArgumentsKey(&args[0], sym->arguments_.size(), true, sym_args),
          value_t(new symbol_t(symbolic::next_symbol_id())));
      value_t& v = function_map[ArgumentsKey(&args[0], sym->arguments_.size(), false, sym_args)];
      symbolic::dump_create(trace_creates, sym, &args[0], sym_args, v);
      return v;
    }
    undef.type = TypeType::UNDEF;
    return undef;
  }
}

bool ExecutionContext::set_debuginfo_filter(const std::string& filters) {
  std::string current;
  size_t last_pos = 0;
  size_t match_pos = 0;

  while ((match_pos = filters.find(",", last_pos)) != std::string::npos) {
    current = filters.substr(last_pos, match_pos-last_pos);
    if (current.size() > 0) {
      debuginfo_filters[current] = true;
    }
    last_pos = match_pos+1;
  }

  match_pos = filters.size();
  current = filters.substr(last_pos, match_pos-last_pos);
  if (current.size() > 0) {
    debuginfo_filters[current] = true;
  }

  return true;
}

bool ExecutionContext::filter_enabled(const std::string& filter) {
  return debuginfo_filters.count("all") > 0 || debuginfo_filters.count(filter) > 0;
}

//
//  Local variables:
//  mode: c++
//  indent-tabs-mode: t
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//
