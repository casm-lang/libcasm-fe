//
//  Copyright (c) 2014-2017 CASM Organization
//  All rights reserved.
//
//  Developed by: Philipp Paulweber
//                Emmanuel Pescosta
//                Florian Hahn
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

#include "TypeCheckPass.h"

#include "../pass/src/PassUsage.h"
#include "../pass/src/PassResult.h"
#include "../pass/src/PassRegistry.h"

using namespace libcasm_fe;
using namespace Ast;

char TypeCheckPass::id = 0;

static libpass::PassRegistration< TypeCheckPass > PASS( "ASTTypeInferencePass",
    "type check the AST and translate it to a typed AST", "ast-check", 0 );

void TypeCheckPass::usage( libpass::PassUsage& pu )
{
    pu.require< SourceToAstPass >();
}

u1 TypeCheckPass::run( libpass::PassResult& pr )
{
    const auto sourceToAstPass = pr.result< SourceToAstPass >();
    const auto specification = sourceToAstPass->specification();

    // TypeCheckVisitor visitor;
    // specification->accept( visitor );

    pr.setResult< TypeCheckPass >( libstdhl::make< Data >( specification ) );

    return true; // TODO: return only true if this pass is correct!
}

//
//  Local variables:
//  mode: c++
//  indent-tabs-mode: nil
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//
