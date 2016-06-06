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

#include "Symbolic.h"

#include <cassert>
#include <sstream>

#include "Operators.h"
#include "ExecutionContext.h"
#include "../Value.h"
#include "../Symbols.h"
#include "../Ast.h"

namespace symbolic {
  static uint32_t last_symbol_id = 1;

  uint32_t next_symbol_id() {
    last_symbol_id += 1;
    return last_symbol_id;
  }

  static uint32_t current_time = 2;
  void advance_timestamp() {
    current_time += 1;
  }

  uint32_t get_timestamp() {
    return current_time;
  }

  std::string arguments_to_string(uint32_t num_arguments, const value_t arguments[], bool strip=false) {
    std::stringstream ss;
    ss << ',';

    for (uint32_t i = 0; i < num_arguments; i++) {
      if (arguments[i].is_symbolic()) {
        ss << "sym" << arguments[i].value.integer;
      } else {
        switch (arguments[i].type) {
          case TypeType::INTEGER:
            ss << arguments[i].value.integer;
            break;
          default: assert(0);
        }
      }
      ss << ',';
    }
    // Strip leading and trailing comma if requested
    if (strip) {
      return ss.str().substr(1, ss.str().size()-2);
    } else {
      return ss.str();
    }
  }


  std::string location_to_string(const Function *func, uint32_t num_arguments,
                                 const value_t arguments[], const value_t& val,
                                 uint32_t time) {
    std::stringstream ss;
    if (func->is_static) {
      ss << "cs";
    } else {
      ss << "st";
    }

    ss << func->name << "(" << time
       << arguments_to_string(num_arguments, arguments) << val.to_str(true)
       << ")";
    return ss.str();
  }


  static void dump_type(std::stringstream& ss, const value_t& v) {
    if (v.is_symbolic() && !v.value.sym->type_dumped) {
      ss << "tff(symbolNext, type, " << v.to_str() << ": $int)."
         << std::endl;
      v.value.sym->type_dumped = true;
    }
  }

  void dump_create(std::vector<std::string>& trace, const Function *func,
                   uint32_t num_arguments, const value_t arguments[], const value_t& v) {
    std::stringstream ss;
    dump_type(ss, v);
    ss << "fof(id%u,hypothesis,"
       << location_to_string(func, num_arguments, arguments, v, symbolic::get_timestamp()-1)
       << ").%%CREATE: " << func->name;

    if (num_arguments == 0) {
      ss << arguments_to_string(num_arguments, arguments, true);
    } else {
      ss << '(' << arguments_to_string(num_arguments, arguments, true) << ')';
    }

    ss << std::endl;
    trace.push_back(ss.str());

    if (symbolic::get_timestamp() > 2) {
      for (uint32_t i=1; i < symbolic::get_timestamp()-1; i++) {
        std::stringstream ss;
        ss << "fof(id%u,hypothesis,"
           << location_to_string(func, num_arguments, arguments, v, i)
           << ").%%CATCHUP: " << func->name;

        if (num_arguments == 0) {
          ss << arguments_to_string(num_arguments, arguments, true);
        } else {
          ss << '(' << arguments_to_string(num_arguments, arguments, true) << ')';
        }

        ss << std::endl;
        trace.push_back(ss.str());
      }
    }
  }

  void dump_symbolic(std::vector<std::string>& trace, const Function *func,
                     uint32_t num_arguments, const value_t arguments[], const value_t& v) {
     std::stringstream ss;
    ss << "fof(id%u,hypothesis,"
       << location_to_string(func, num_arguments, arguments, v, get_timestamp())
       << ").%%SYMBOLIC: " << func->name;

    if (num_arguments == 0) {
      ss << arguments_to_string(num_arguments, arguments, true);
    } else {
      ss << '(' << arguments_to_string(num_arguments, arguments, true) << ')';
    }
    ss << std::endl;
    trace.push_back(ss.str());
  }

  void dump_update(std::vector<std::string>& trace, const Function *func,
                   uint32_t num_arguments, const value_t arguments[], const value_t& v) {
    std::stringstream ss;
    dump_type(ss, v);
    ss << "fof(id%u,hypothesis,"
       << location_to_string(func, num_arguments, arguments, v, get_timestamp())
       << ").%%UPDATE: " << func->name;

    if (num_arguments == 0) {
      ss << arguments_to_string(num_arguments, arguments, true);
    } else {
      ss << '(' << arguments_to_string(num_arguments, arguments, true) << ')';
    }
    ss << std::endl;
    trace.push_back(ss.str());
  }

  void dump_pathcond_match(std::vector<std::string>& trace, const std::string &filename,
      size_t lineno, const symbolic_condition_t *cond, bool status) {
    std::stringstream ss;
    ss << "% " << filename << ":" << lineno << " PC-LOOKUP ("
       << cond->to_str() << ") = " << status << std::endl;
    trace.push_back(ss.str());
 
  }

  void dump_if(std::vector<std::string>& trace, const std::string &filename,
      size_t lineno, const symbolic_condition_t *cond) {
    std::stringstream ss;
    ss << "fof('id" << filename <<  ":" << lineno << "',hypothesis,"
       << cond->to_str() << ")." << std::endl;
    trace.push_back(ss.str());
  }

  void dump_final(std::vector<std::string>& trace, const std::vector<const Function*> symbols,
                  const std::vector<std::unordered_map<ArgumentsKey, value_t>>& states) {
    std::stringstream ss;
    uint32_t i = 0;
    for (uint32_t j=0; j < symbols.size(); j++) {
      if (!symbols[j]->is_symbolic) {
        continue;
      }
      for (auto& value_pair : states[j]) {
        ss << "fof(final" << i << ",hypothesis,"
           << location_to_string(symbols[j], value_pair.first.size, value_pair.first.p, value_pair.second, 0)
           << ").%FINAL: " << symbols[j]->name;
        if (symbols[j]->arguments_.size() == 0) {
          ss << arguments_to_string(value_pair.first.size, value_pair.first.p, true);
        } else {
          ss << '(' << arguments_to_string(value_pair.first.size, value_pair.first.p, true) << ')' ;
        }
        ss << std::endl;
        i += 1;
      }
    }
    trace.push_back(ss.str());
  }

  check_status_t check_inclusion(const symbolic_condition_t& known,
                                 const symbolic_condition_t& check) {
    switch (check.op) {
      case ExpressionOperation::EQ:
        if (known.op == ExpressionOperation::EQ) {
          if (*known.rhs == *check.rhs) {
            return check_status_t::TRUE;
          } else {
            return check_status_t::FALSE;
          }
        } else if (known.op == ExpressionOperation::NEQ) {
          if(*known.rhs == *check.rhs) {
            return check_status_t::FALSE;
          }
        }
        return check_status_t::NOT_FOUND;
      case ExpressionOperation::NEQ:
        if (known.op == ExpressionOperation::NEQ) {
          if(*known.rhs == *check.rhs) {
            return check_status_t::TRUE;
          }
        } else if (known.op == ExpressionOperation::EQ) {
          if (*known.rhs == *check.rhs) {
            return check_status_t::FALSE;
          } else {
            return check_status_t::TRUE;
          }
        }
        return check_status_t::NOT_FOUND;
      case ExpressionOperation::LESSEREQ:
        if (known.op == ExpressionOperation::EQ) {
          value_t res = operators::lessereq(*known.rhs, *check.rhs);
          if (res.value.boolean) {
            return check_status_t::TRUE;
          } else {
            return check_status_t::FALSE;
          }
        } else if (known.op == ExpressionOperation::LESSEREQ) {
          value_t res = operators::lessereq(*check.rhs, *known.rhs);
          if (res.value.boolean) {
            return check_status_t::TRUE;
          }
        } else if (known.op == ExpressionOperation::GREATER) {
          value_t res = operators::lessereq(*check.rhs, *known.rhs);
          if (res.value.boolean) {
            return check_status_t::FALSE;
          }
        }
        return check_status_t::NOT_FOUND;
      case ExpressionOperation::GREATER:
        if (known.op == ExpressionOperation::EQ) {
          value_t res = operators::greater(*known.rhs, *check.rhs);
          if (res.value.boolean) {
            return check_status_t::TRUE;
          } else {
            return check_status_t::FALSE;
          }
        } else if (known.op == ExpressionOperation::LESSEREQ) {
          value_t res = operators::lessereq(*known.rhs, *check.rhs);
          if (res.value.boolean) {
            return check_status_t::FALSE;
          }
        } else if (known.op == ExpressionOperation::GREATER) {
          value_t res = operators::greater(*check.rhs, *known.rhs);
          if (res.value.boolean) {
            return check_status_t::TRUE;
          }
        }
        return check_status_t::NOT_FOUND;

      default:
        assert(0);
    }
    return check_status_t::NOT_FOUND;
  }

  check_status_t check_condition(std::vector<symbolic_condition_t*> known_conditions,
      const symbolic_condition_t *check) {

    symbolic_condition_t cond(check->lhs, check->rhs, check->op);

    if (check->lhs->type != TypeType::SYMBOL) {
      if (check->rhs->type == TypeType::SYMBOL) {
        cond = symbolic_condition_t(check->rhs, check->lhs, check->op);
      } else {
        throw RuntimeException("Invalid condition passed");
      }
    }

    for (symbolic_condition_t *known_cond : known_conditions) {
     check_status_t s = check_status_t::NOT_FOUND;
      if (*(known_cond->lhs) == *(cond.lhs)) {
        s = check_inclusion(*known_cond, cond);
      } else if (*(known_cond->rhs) == *(cond.lhs)) {
        s = check_inclusion(
            symbolic_condition_t(known_cond->rhs, known_cond->lhs, known_cond->op),
            cond);
      }
      if (s != check_status_t::NOT_FOUND) {
        return s;
      }
    }
    return check_status_t::NOT_FOUND;
  }

  uint32_t dump_listconst(std::vector<std::string>& trace, List *l) {
    auto iter = l->begin();
    auto end = l->end();
    uint32_t sym_id = 0;
    if (iter != end) {
      sym_id = symbolic::next_symbol_id();
      std::stringstream ss;
      ss << "tff(symbolNext, type, sym" << sym_id << ": $int)."
         << std::endl;
      ss << "fof(id%u,hypothesis,fcons(eEmptyList," << (*iter).to_str(true)
         << ",sym" << sym_id << "))." << std::endl;
      iter++;
      trace.push_back(ss.str());

      for (;iter != end; iter++) {
        std::stringstream ss;
        uint32_t next_id = symbolic::next_symbol_id();
        ss << "tff(symbolNext, type, sym" << next_id << ": $int)."
           << std::endl;
        ss << "fof(id%u,hypothesis,fcons(sym" << sym_id << "," << (*iter).to_str(true)
           << ",sym" << next_id << "))." << std::endl;
        sym_id = next_id;
        trace.push_back(ss.str());
      }
    }
    return sym_id;
  }

  void dump_builtin(std::vector<std::string>& trace, const char *name,
                    const value_t arguments[], uint16_t num_arguments,
                    const value_t& ret) {
    std::stringstream ss;

    for (uint16_t i=0; i < num_arguments; i++) {
      dump_type(ss, arguments[i]);
    }
    dump_type(ss, ret);

    ss << "fof(id%u,hypothesis,f" << name << "(";

    for (uint16_t i=0; i < num_arguments; i++) {
      ss << arguments[i].to_str() << ", ";
    }
    ss << ret.to_str() << "))." << std::endl;
    trace.push_back(ss.str());
  }
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
