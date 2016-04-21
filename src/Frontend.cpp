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
//  along with this program. If not, see <http://www.gnu.org/licenses/>.
//  

#include "Frontend.h"

#include "Driver.h"
#include "AstDumpVisitor.h"
#include "TypeCheckVisitor.h"

extern Driver *global_driver;

void casm_frontend_init() {
  global_driver = new Driver;
}

void casm_frontend_destroy() {
  delete global_driver;
}

AstNode* casm_frontend_pass_1_parse(const std::string& filename) {
  return global_driver->parse(filename);
}

bool casm_frontend_pass_2_typecheck(AstNode *root) {
  TypecheckVisitor typecheck_visitor(*global_driver);
  AstWalker<TypecheckVisitor, Type*> typecheck_walker(typecheck_visitor);
  typecheck_walker.walk_specification(root);
  return global_driver->ok();
}

std::string casm_dump_ast(AstNode *root) {
  AstDumpVisitor dump_visitor;
  AstWalker<AstDumpVisitor, bool> dump_walker(dump_visitor);
  dump_walker.suppress_calls = true;
  dump_walker.walk_specification(root);
  return dump_visitor.get_dump();
}
