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

#include "AstDumpPass.h"

using namespace libcasm_fe;


char AstDumpPass::id = 0;

static libpass::PassRegistration< AstDumpPass > PASS
( "AST Dumping Pass"
, "generates a DOT graph of the AST"
, "ast-dump"
, 0
);


bool AstDumpPass::run( libpass::PassResult& pr )
{
	AstListNode* node = (AstListNode*)pr.getResult< AstDumpPass >();
	
	AstWalker< AstDumpVisitor, bool > dump_walker( *this );
	
	dump_walker.suppress_calls = true;
	dump_walker.walk_specification( node );
	
	// std::cout << this->get_dump() << std::endl;
	
	std::ofstream dotfile( "./obj/out.dot" );
	dotfile << this->get_dump() << "\n";
	dotfile.close();
	
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
