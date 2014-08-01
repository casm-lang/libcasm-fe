#include "frontend.h"

#include "libsyntax/driver.h"
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

bool casm_frontend_pass_1_parse(AstNode *root) {
  TypecheckVisitor typecheck_visitor(*global_driver);
  AstWalker<TypecheckVisitor, Type*> typecheck_walker(typecheck_visitor);
  typecheck_walker.walk_specification(root);
  return global_driver->ok();
}
