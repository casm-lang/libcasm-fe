#include <iostream>

#include "frontend.h"

int main (int argc, char *argv[]) {
  int res = 0;

  // Setup the frontend lib
  casm_frontend_init();

  if (argc != 2) {
    std::cerr << "Error: invalid number of arguments" << std::endl;
      return EXIT_FAILURE;
  }
  AstNode* root = casm_frontend_pass_1_parse(argv[1]);
  if (root == nullptr) {
    std::cerr << "Error parsing file" << std::endl;
    res = EXIT_FAILURE;
  } else {
    std::cout << casm_dump_ast(root) << std::endl;;
    res = EXIT_SUCCESS;
  }

  casm_frontend_destroy();

  return res;
}
