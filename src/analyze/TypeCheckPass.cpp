//  
//  Copyright (c) 2014-2016 CASM Organization
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

#include "TypeCheckPass.h"

#include "../Driver.h"
#include "../TypeCheckVisitor.h"

using namespace libcasm_fe;

extern Driver *global_driver;

char TypeCheckPass::id = 0;

static libpass::PassRegistration< TypeCheckPass > PASS
( "Type Check Pass"
, "type check the AST and translate it to a typed AST"
, 0
, 'T'
);


bool TypeCheckPass::run( libpass::PassResult& pr )
{
    Ast* node = (Ast*)pr.getResult< SourceToAstPass >();

    TypecheckVisitor typecheck_visitor(*global_driver);
    AstWalker<TypecheckVisitor, Type*> typecheck_walker(typecheck_visitor);
    typecheck_walker.walk_specification(node);

    if( global_driver->rules_map_.count(node->getInitRule()->identifier) == 0 )
    {
        global_driver->error
        ( node->getInitRule()->location
        , "init rule `" + node->getInitRule()->identifier + "` doesn't exist"
        , libcasm_fe::Codes::AgentInitRuleDoesNotExist
        );
    }

    pr.setResult< TypeCheckPass >( node );

    return global_driver->ok();
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
