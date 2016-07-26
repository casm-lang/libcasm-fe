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

#include "Builtins.h"

#include <cmath>
#include <cassert>
#include <sstream>

#include "ExecutionContext.h"
#include "../Value.h"

const value_t builtins::dispatch(Builtin::Id atom_id,  ExecutionContext& ctxt,
                               const value_t arguments[], uint16_t num_arguments) {
  switch (atom_id) {
    case Builtin::Id::POW:
      return builtins::pow(arguments[0], arguments[1]);

    case Builtin::Id::HEX:
      return builtins::hex(arguments[0]);

    case Builtin::Id::NTH:
      return builtins::nth(arguments[0], arguments[1]);

    case Builtin::Id::APP:
      return builtins::app(ctxt, arguments[0], arguments[1]);

    case Builtin::Id::CONS:
      return builtins::cons(ctxt, arguments[0], arguments[1]);

    case Builtin::Id::TAIL:
      return builtins::tail(ctxt, arguments[0]);

    case Builtin::Id::LEN:
      return builtins::len(arguments[0]);

    case Builtin::Id::PEEK:
      return builtins::peek(arguments[0]);

    case Builtin::Id::AS_BOOLEAN:
      return builtins::asboolean(arguments[0]);

    case Builtin::Id::AS_INTEGER:
      return builtins::asinteger(arguments[0]);

    case Builtin::Id::AS_FLOATING:
      return builtins::asfloating(arguments[0]);

    case Builtin::Id::AS_RATIONAL:
      return builtins::asrational(arguments[0]);

    case Builtin::Id::SYMBOLIC:
      return builtins::symbolic(arguments[0]);

    default:
      return shared::dispatch(atom_id, ctxt, arguments, num_arguments);
  }
}

const value_t builtins::pow(const value_t& base, const value_t& power) {
  switch (base.type) {
    case TypeType::INTEGER:
      return value_t((INTEGER_T)std::pow(base.value.integer, power.value.integer));

    case TypeType::FLOATING:
      return value_t((FLOATING_T)std::pow(base.value.float_, power.value.float_));
    default: FAILURE();
  }
}

const value_t builtins::hex(const value_t& arg) {
  // TODO LEAK!
  if (arg.is_undef()) {
    return value_t(new std::string("undef"));
  }

  std::stringstream ss;
  if (arg.value.integer < 0) {
    ss << "-" << std::hex << (-1) * arg.value.integer;
  } else {
    ss << std::hex << arg.value.integer;
  }
  return value_t(new std::string(ss.str()));
}

const value_t builtins::nth(const value_t& list_arg, const value_t& index ) {
  if (list_arg.is_undef() || index.is_undef()) {
    return value_t();
  }

  List *list = list_arg.value.list;
  List::const_iterator iter = list->begin();
  INTEGER_T i = 1;

  while (iter != list->end() && i < index.value.integer) {
    i++;
    iter++;
  }
  if (i == index.value.integer && iter != list->end()) {
    return value_t(*iter);
  } else {
    return value_t();
  }
}

const value_t builtins::app(ExecutionContext& ctxt, const value_t& list, const value_t& val) {
  // TODO LEAK
  if (list.is_undef()) {
    return value_t();
  }

  List *current = list.value.list;

  while (true) {
    if (current->list_type == List::ListType::HEAD) {
      current = reinterpret_cast<HeadList*>(current)->right;
    }
    if (current->list_type == List::ListType::SKIP) {
      current = reinterpret_cast<SkipList*>(current)->bottom;
    }
    if (current->list_type == List::ListType::BOTTOM) {
      BottomList *bottom = reinterpret_cast<BottomList*>(current);
      if (bottom->tail) {
        current = bottom->tail;
      } else {
        break;
      }
    }
    if (current->list_type == List::ListType::TAIL) {
      TailList *tail = reinterpret_cast<TailList*>(current);
      if (tail->right) {
        current = tail->right;
      } else {
        break;
      }
    }
  }


  TailList *tail = new TailList(nullptr, val);
  ctxt.temp_lists.push_back(tail);

  if (current->list_type == List::ListType::TAIL) {
    reinterpret_cast<TailList*>(current)->right = tail;
  } else if (current->list_type == List::ListType::BOTTOM) {
    reinterpret_cast<BottomList*>(current)->tail = tail;
  } else {
    FAILURE();
  }
  return value_t(list.type, list.value.list);
}

const value_t builtins::cons(ExecutionContext& ctxt, const value_t& val, const value_t& list) {
  // TODO LEAK
  if (list.is_undef()) {
    return value_t();
  }

  HeadList *consed_list = new HeadList(list.value.list, val);
  ctxt.temp_lists.push_back(consed_list);
  return value_t(list.type, consed_list);
}

const value_t builtins::tail(ExecutionContext& ctxt, const value_t& arg_list) {
  if (arg_list.is_undef()) {
    return value_t();
  }

  List *list = arg_list.value.list;

  if (list->is_head()) {
    return value_t(arg_list.type, reinterpret_cast<HeadList*>(list)->right);
  } else if (list->is_bottom()) {
    BottomList *btm = reinterpret_cast<BottomList*>(list);
    SkipList *skip = new SkipList(1, btm);
    ctxt.temp_lists.push_back(skip);
    return value_t(arg_list.type, skip);
  } else {
    SkipList *old_skip = reinterpret_cast<SkipList*>(list);
    SkipList *skip = new SkipList(old_skip->skip+1, old_skip->bottom);
    ctxt.temp_lists.push_back(skip);
    return value_t(arg_list.type, skip);
  }
}

const value_t builtins::len(const value_t& list_arg) {
  // TODO len is really slow right now, it itertes over complete list
  if (list_arg.is_undef()) {
    return value_t();
  }

  List *list = list_arg.value.list;
  List::const_iterator iter = list->begin();

  size_t count = 0;

  while (iter != list->end()) {
    count++;
    iter++;
  }
  return value_t((INTEGER_T) count);
}

const value_t builtins::peek(const value_t& arg_list) {
  if (arg_list.is_undef()) {
    return value_t();
  }

  List *list = arg_list.value.list;

  if (list->begin() != list->end()) {
    return value_t(*(list->begin()));
  } else {
    return value_t();
  }
}

const value_t builtins::asboolean(const value_t& arg) {
  if (arg.is_undef()) {
    return std::move(arg);
  }

  return value_t((bool)arg.value.integer);
}

const value_t builtins::asinteger(const value_t& arg) {
  if (arg.is_undef()) {
    return std::move(arg);
  }

  switch (arg.type) {
    case TypeType::INTEGER:
      return value_t(arg.value.integer);
    case TypeType::FLOATING:
      return value_t((INTEGER_T)arg.value.float_);
    case TypeType::RATIONAL:
      return value_t((INTEGER_T)(arg.value.rat->numerator / arg.value.rat->denominator));
    case TypeType::ENUM:
      return value_t((INTEGER_T)arg.value.enum_val->id);
    default: FAILURE();
  }
}

const value_t builtins::asfloating(const value_t& arg) {
  if (arg.is_undef()) {
    return std::move(arg);
  }

  switch (arg.type) {
    case TypeType::INTEGER:
      return value_t((FLOATING_T) arg.value.integer);
    case TypeType::FLOATING:
      return value_t(arg.value.float_);
    case TypeType::RATIONAL:
      return value_t(((FLOATING_T)arg.value.rat->numerator) / arg.value.rat->denominator);
    default: FAILURE();
  }
}

static void get_numerator_denominator(double x, int64_t *num, int64_t *denom) {
  // thanks to
  // http://stackoverflow.com/a/96035/781502
  uint64_t m[2][2];
  double startx = x;
  uint64_t maxden = 10000000000;
  int64_t ai;

  /* initialize matrix */
  m[0][0] = m[1][1] = 1;
  m[0][1] = m[1][0] = 0;

  /* loop finding terms until denom gets too big */
  while (m[1][0] *  ( ai = (int64_t)x ) + m[1][1] <= maxden) {
      long t;
      t = m[0][0] * ai + m[0][1];
      m[0][1] = m[0][0];
      m[0][0] = t;
      t = m[1][0] * ai + m[1][1];
      m[1][1] = m[1][0];
      m[1][0] = t;
      if(x==(double)ai) break;     // AF: division by zero
      x = 1/(x - (double) ai);
      if(x>(double)0x7FFFFFFF) break;  // AF: representation failure
  }

  /* now remaining x is between 0 and 1/ai */
  /* approx as either 0 or 1/m where m is max that will fit in maxden */
  /* first try zero */

  double error1 = startx - ((double) m[0][0] / (double) m[1][0]);

  *num = m[0][0];
  *denom =  m[1][0];

  /* now try other possibility */
  ai = (maxden - m[1][1]) / m[1][0];
  m[0][0] = m[0][0] * ai + m[0][1];
  m[1][0] = m[1][0] * ai + m[1][1];
  double error2 = startx - ((double) m[0][0] / (double) m[1][0]);

  if (fabs(error1) > fabs(error2)) {
    *num = m[0][0];
    *denom =  m[1][0];
  }
}

const value_t builtins::asrational(const value_t& arg) {
  if (arg.is_undef()) {
    return std::move(arg);
  }

  auto result = reinterpret_cast<rational_t*>(ExecutionContext::value_stack.allocate(sizeof(rational_t)));
  switch (arg.type) {
    case TypeType::INTEGER:
      result->numerator = arg.value.integer;
      result->denominator = 1;
      return value_t(result);
    case TypeType::FLOATING:
      get_numerator_denominator(arg.value.float_, &result->numerator, &result->denominator);
      return value_t(result);
    case TypeType::RATIONAL:
      return value_t(arg.value.rat);
    default: FAILURE();
  }
}

const value_t builtins::symbolic(const value_t& arg) {
  if (arg.is_symbolic() && !arg.value.sym->list) {
    return value_t(true);
  } else {
    return value_t(false);
  }
}

namespace builtins {
namespace shared {
  //#include "shared_glue.h" FIXME

  IGNORE_VARIADIC_WARNINGS
  #pragma GCC diagnostic ignored "-Wmissing-field-initializers"
  #pragma GCC diagnostic ignored "-Wunused-parameter"

  // the CASM runtime heavily depens on macros, whatever you think of it ... 
  // here we need to provide all definitions ...
  #define TRUE                    1
  #define FALSE                   0
  #define ARG(TYPE, NAME)             TYPE* NAME
  #define SARG(VAR) #VAR              " {0x%lx,%u}"
  #define PARG(TYPE, VAR)             (uint64_t)VAR->value, VAR->defined
  #define CASM_RT(FORMAT, ARGS...)        /* printf-able */

  // create concrete variants of the shareds
  #define CASM_CALL_SHARED(NAME, VALUE, ARGS...)  NAME(VALUE, ##ARGS)
  #define DEFINE_CASM_SHARED(NAME, VALUE, ARGS...) void NAME(VALUE, ##ARGS)
  //#include "libcasmrt/pp_casm_shared.h" FIXME


  namespace symbolic {
    // create symbolic variants of shareds
    namespace BV {
      // mock BV namespace as expected by the pp_casm_shared builtins
      struct helper_t {
        bool next() { return true; }
      };
      static helper_t symbolic_nopointer;
      helper_t *symbolic_ = &symbolic_nopointer;
    }

    #undef CASM_CALL_SHARED
    #undef DEFINE_CASM_SHARED
    #define SYMBOLIC
    #define CASM_CALL_SHARED(NAME, VALUE, ARGS...)  symbolic_##NAME(VALUE, ##ARGS)
    #define DEFINE_CASM_SHARED(NAME, VALUE, ARGS...) void symbolic_##NAME(VALUE, ##ARGS)
    //#include "libcasmrt/pp_casm_shared.h" FIXME
  }

  #pragma GCC diagnostic warning "-Wmissing-field-initializers"
  #pragma GCC diagnostic warning "-Wunused-parameter"
  REENABLE_VARIADIC_WARNINGS

  const value_t dispatch(Builtin::Id builtin_id,  ExecutionContext& ctxt,
                       const value_t arguments[], uint16_t num_arguments) {
    const char *sym_name;
    Int ret;
    Int arg0;
    Int arg1;
    Int arg2;
    Int arg3;
    Int arg4;
    switch (builtin_id) {
        //SHARED_DISPATCH FIXME
      default: FAILURE();
    }

    if (ret.defined == TRUE) {
      return value_t((INTEGER_T)ret.value);
    } else if (ctxt.symbolic && ret.sym) {
      /*value_t v(new symbol_t(::symbolic::next_symbol_id()));
      ::symbolic::dump_builtin(ctxt.trace, sym_name, arguments, num_arguments, v);
      return std::move(v);*/
      assert(0);
      return value_t(); // FIXME
    } else {
      return value_t();
    }
  }
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
