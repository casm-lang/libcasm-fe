#include "frontend.h"

#include "libsyntax/driver.h"
#include "libsyntax/ast_dump_visitor.h"
#include "libmiddle/typecheck_visitor.h"

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
