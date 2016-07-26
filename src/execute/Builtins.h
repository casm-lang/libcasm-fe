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

#ifndef _LIB_CASMFE_BUILTINS_H_
#define _LIB_CASMFE_BUILTINS_H_

class value_t;
class ExecutionContext;

#include "../Symbols.h"

namespace builtins {
  const value_t dispatch(Builtin::Id atom_id, ExecutionContext& ctxt,
                         const value_t arguments[], uint16_t num_arguments);

  const value_t pow(const value_t& base, const value_t& power);
  const value_t hex(const value_t& arg);
  const value_t nth(const value_t& list_arg, const value_t& index );
  const value_t app(ExecutionContext& ctxt, const value_t& list, const value_t& val);
  const value_t cons(ExecutionContext& ctxt, const value_t& val, const value_t& list);
  const value_t tail(ExecutionContext& ctxt, const value_t& arg_list);
  const value_t len(const value_t& list_arg);
  const value_t peek(const value_t& arg_list);

  const value_t asboolean(const value_t& arg);
  const value_t asinteger(const value_t& arg);
  const value_t asfloating(const value_t& arg);
  const value_t asrational(const value_t& arg);

  const value_t symbolic(const value_t& arg);

  namespace shared {
    struct Int {
      uint64_t value;
      uint8_t defined;
      bool sym;
    };

  const value_t dispatch(Builtin::Id builtin_id, ExecutionContext& ctxt,
                         const value_t arguments[], uint16_t num_arguments);

  }
};

#endif // _LIB_CASMFE_BUILTINS_H_

//
//  Local variables:
//  mode: c++
//  indent-tabs-mode: t
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//
