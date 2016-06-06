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

#ifndef _LIB_CASMFE_SYMBOLIC_H_
#define _LIB_CASMFE_SYMBOLIC_H_

struct symbolic_condition_t;
struct ArgumentsKey;

class value_t;
class Function;
class List;

#include <cstdint>
#include <vector>
#include <unordered_map>

namespace symbolic {
  uint32_t next_symbol_id();
  void advance_timestamp();
  uint32_t get_timestamp();

  void dump_create(std::vector<std::string>& trace, const Function *func,
                   uint32_t num_arguments, const value_t arguments[], const value_t& v);

  void dump_symbolic(std::vector<std::string>& trace, const Function *func,
                     uint32_t num_arguments, const value_t arguments[], const value_t& v);

  void dump_update(std::vector<std::string>& trace, const Function *func,
                   uint32_t num_arguments, const value_t arguments[], const value_t& v);

  void dump_if(std::vector<std::string>& trace, const std::string &filename,
      size_t lineno, const symbolic_condition_t *cond);

  void dump_pathcond_match(std::vector<std::string>& trace, const std::string &filename,
      size_t lineno, const symbolic_condition_t *cond, bool status);

  void dump_final(std::vector<std::string>& trace, const std::vector<const Function*> symbols,
                  const std::vector<std::unordered_map<ArgumentsKey, value_t>>& states);

  uint32_t dump_listconst(std::vector<std::string>& trace, List *l);

  void dump_builtin(std::vector<std::string>& trace, const char *name,
      const value_t arguments[], uint16_t num_arguments, const value_t& ret);

  enum class check_status_t {
    NOT_FOUND,
    TRUE,
    FALSE
  };

  check_status_t check_condition(std::vector<symbolic_condition_t*> known_condition,
      const symbolic_condition_t *check);
};

#endif // _LIB_CASMFE_SYMBOLIC_H_

//
//  Local variables:
//  mode: c++
//  indent-tabs-mode: t
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//
