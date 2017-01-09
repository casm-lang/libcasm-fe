//
//  Copyright (c) 2014-2017 CASM Organization
//  All rights reserved.
//
//  Developed by: Florian Hahn
//                Philipp Paulweber
//                Emmanuel Pescosta
//                https://github.com/casm-lang/libcasm-fe
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

#ifndef _LIB_CASMFE_H_
#define _LIB_CASMFE_H_

#include "src/Ast.h"
#include "src/CasmFE.h"
#include "src/Codes.h"
#include "src/Driver.h"
#include "src/Exceptions.h"
#include "src/FunctionCycleVisitor.h"
#include "src/LexerHelpers.h"
#include "src/Macros.h"
#include "src/Symbolic.h"
#include "src/Symbols.h"
#include "src/Types.h"
#include "src/Value.h"
#include "src/Visitor.h"

#include "src/various/GrammarParser.tab.h"
#include "src/various/location.hh"
#include "src/various/position.hh"
#include "src/various/stack.hh"

#include "src/allocator/BlockAllocator.h"

#include "src/analyze/AstDumpPass.h"
#include "src/analyze/TypeCheckPass.h"

#include "src/execute/ChainedHashMap.h"
#include "src/execute/ExecutionPassBase.h"
#include "src/execute/HashMapBase.h"
#include "src/execute/NumericExecutionPass.h"
#include "src/execute/ProbingHashMap.h"
#include "src/execute/RobinHoodHashMap.h"
#include "src/execute/SymbolicExecutionPass.h"
#include "src/execute/UpdateSet.h"

#include "src/transform/AstToCasmIRPass.h"
#include "src/transform/SourceToAstPass.h"

namespace libcasm_fe
{
}

#endif /* _LIB_CASMFE_H_ */

//
//  Local variables:
//  mode: c++
//  indent-tabs-mode: nil
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//
