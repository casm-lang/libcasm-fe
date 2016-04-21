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

#include "NumericExecutionPass.h"

using namespace libcasm_fe;


char NumericExecutionPass::id = 0;

static libpass::PassRegistration< NumericExecutionPass > PASS
( "Numeric Execution Pass"
, "execute numerically over the AST the input specification"
, "ast-num"
, 0
);


bool NumericExecutionPass::run( libpass::PassResult& pr )
{
	AstNode* node = (AstNode*)pr.getResult< TypeCheckPass >();
    fprintf( stderr, "%s:%i: TODO of %p/n", __FILE__, __LINE__, node );
		
	// TODO: FIXME: 

	// return false if something went wrong!!!
	return true;
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
