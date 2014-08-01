#ifndef CASM_FRONTEND_H
#define CASM_FRONTEND_H

#include <utility>

#include "libsyntax/ast.h"

void casm_frontend_init();

void casm_frontend_destroy();

AstNode* casm_frontend_pass_1_parse(const std::string& filename);

bool casm_frontend_pass_2_typecheck(AstNode *root);
#endif
