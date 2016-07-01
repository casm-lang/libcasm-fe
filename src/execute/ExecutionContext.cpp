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
#include <cstring>

#include "Symbolic.h"
#include "../Driver.h"
#include "../Ast.h"

ArgumentsKey::ArgumentsKey(const value_t args[], uint32_t size, bool dyn) : size(size), dynamic(dyn) {
  if (dynamic) {
    auto argsDup = new value_t[size];
    memcpy(argsDup, args, sizeof(value_t) * size);
    p = argsDup;
  } else {
    p = args;
  }
}

ArgumentsKey::ArgumentsKey(const ArgumentsKey& other) : p(other.p), size(other.size),
    dynamic(other.dynamic) {
}

ArgumentsKey::ArgumentsKey(ArgumentsKey&& other) noexcept {
  p = other.p;
  dynamic = other.dynamic;
  size = other.size;
  other.dynamic = false;
}

ArgumentsKey::~ArgumentsKey() {
  if (dynamic) {
    delete[] p;
  }
}

static std::string arguments_to_string(uint32_t num_arguments, const value_t arguments[]) {
  std::stringstream ss;
  if (num_arguments == 0) {
    return "";
  }
  for (uint32_t i = 0; i < num_arguments; i++) {
    ss << arguments[i].to_str();
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

Update* ExecutionContext::add_update(const value_t& val, size_t sym_id, uint32_t num_arguments, value_t arguments[], uint64_t line) {
  auto& function_map = function_states[sym_id];
  auto it = function_map.find(ArgumentsKey(arguments, num_arguments, false)); // TODO EP: use emplace only
  if (it == function_map.cend()) {
    const auto pair = function_map.emplace(ArgumentsKey(arguments, num_arguments, true), value_t());
    it = pair.first;
  }

  Update* up = reinterpret_cast<Update*>(pp_stack.allocate(sizeof(Update))); // FIXME make it nicer!!
  up->value = val;
  up->func = sym_id;
  up->args = const_cast<value_t*>(it->first.p);
  up->num_args = num_arguments;
  up->line = line;

  try {
    const value_t& ref = it->second;
    updateSetManager.add(reinterpret_cast<uint64_t>(&ref), up);
  } catch (const UpdateSet::Conflict& e) {
    const auto conflictingUpdate = e.conflictingUpdate();
    const auto existingUpdate = e.existingUpdate();

    const auto function = function_symbols[conflictingUpdate->func];
    std::string locationText = function->name;
    if (conflictingUpdate->num_args > 0) {
        locationText += "(" + conflictingUpdate->args[0].to_str();
        for (uint16_t i = 1; i < conflictingUpdate->num_args; i++) {
            locationText += ", " + conflictingUpdate->args[i].to_str();
        }
        locationText += ")";
    }

    auto info = "Conflict while adding update " + locationText + " = " + val.to_str()
              + " at line " + std::to_string(line) + ", conflicting with line "
              + std::to_string(existingUpdate->line) + ", value: " + existingUpdate->value.to_str();
    throw RuntimeException(info);
  }

  return up;
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
    value_t* location = reinterpret_cast<value_t*>(it->first);
    Update* u = it->second;

    // TODO handle tuples
    if (u->value.type == TypeType::LIST) {
      if (u->value.is_symbolic()){
        *location = u->value;
      } else {
        auto& function_map = function_states[u->func];
        value_t& list = function_map[ArgumentsKey(u->args, u->num_args, false)];
        if (u->value.is_undef()) {
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
      }
    } else {
      // we could erase keys that store an undef value in concrete mode,
      // but we need to know if a key was set to undef explicitly in symbolic
      // mode
      *location = u->value;
    }

    if (symbolic || dump_updates) {
      updated_functions[u->func].push_back(
            ArgumentsKey(u->args, u->num_args, true));
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

      std::equal_to<ArgumentsKey> eq;
      for (const auto& pair : function_map) {
        bool found = false;
        for (const auto& k : updated_keys) {
          if (eq(k, pair.first)) {
            found = true;
            break;
          }
        }
        if (!found) {
          symbolic::dump_symbolic(trace, function_symbol, pair.first.size, pair.first.p, pair.second);
        }
      }
      for (const auto& k : updated_keys) {
        symbolic::dump_update(trace, function_symbol, k.size, k.p, function_map[k]);
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
            arguments_to_string(k.size, k.p)+" = "+
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

void ExecutionContext::fork(const UpdateSet::Type updateSetType)
{
    updateSetManager.fork(updateSetType);
}

void ExecutionContext::merge()
{
    try {
        updateSetManager.merge();
    } catch (const UpdateSet::Conflict& e) {
        const auto conflictingUpdate = e.conflictingUpdate();
        const auto existingUpdate = e.existingUpdate();

        const auto function = function_symbols[conflictingUpdate->func];
        std::string locationText = function->name;
        if (conflictingUpdate->num_args > 0) {
            locationText += "(" + conflictingUpdate->args[0].to_str();
            for (uint16_t i = 1; i < conflictingUpdate->num_args; i++) {
                locationText += ", " + conflictingUpdate->args[i].to_str();
            }
            locationText += ")";
        }

        auto info = "Conflict while merging updateset " + locationText + "\n"
                  + "at line " + std::to_string(conflictingUpdate->line)
                  + " with value: " + conflictingUpdate->value.to_str() + "\n"
                  + "and at line " + std::to_string(existingUpdate->line)
                  + " with value: " + existingUpdate->value.to_str();
        throw RuntimeException(info);
    }
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

const value_t ExecutionContext::get_function_value(Function *sym, uint32_t num_arguments, const value_t arguments[]) {
  auto& function_map = function_states[sym->id];
  try {
    const value_t &v = function_map.at(ArgumentsKey(arguments, num_arguments, false));
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
          ArgumentsKey(ArgumentsKey(arguments, num_arguments, false)),
          value_t(new symbol_t(symbolic::next_symbol_id())));
      value_t& v = function_map[ArgumentsKey(arguments, num_arguments, false)];
      symbolic::dump_create(trace_creates, sym, num_arguments, arguments, v);
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
