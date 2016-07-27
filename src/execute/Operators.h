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

#ifndef _LIB_CASMFE_OPERATORS_H_
#define _LIB_CASMFE_OPERATORS_H_

class value_t;

enum class ExpressionOperation;

namespace operators {
  const value_t dispatch(ExpressionOperation op, const value_t& lhs, const value_t& rhs);

  const value_t add(const value_t& lhs, const value_t& rhs);
  const value_t sub(const value_t& lhs, const value_t& rhs);
  const value_t mul(const value_t& lhs, const value_t& rhs);
  const value_t div(const value_t& lhs, const value_t& rhs);
  const value_t mod(const value_t& lhs, const value_t& rhs);
  const value_t rat_div(const value_t& lhs, const value_t& rhs);

  const value_t eq(const value_t& lhs, const value_t& rhs);
  const value_t neq(const value_t& lhs, const value_t& rhs);

  const value_t and_(const value_t& lhs, const value_t& rhs);
  const value_t or_(const value_t& lhs, const value_t& rhs);
  const value_t xor_(const value_t& lhs, const value_t& rhs);
  const value_t not_(const value_t& lhs);

  const value_t lesser(const value_t& lhs, const value_t& rhs);
  const value_t greater(const value_t& lhs, const value_t& rhs);
  const value_t lessereq(const value_t& lhs, const value_t& rhs);
  const value_t greatereq(const value_t& lhs, const value_t& rhs);
};

#endif

//
//  Local variables:
//  mode: c++
//  indent-tabs-mode: t
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//
