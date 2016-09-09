#include "frontend.h"

int main (int argc, char *argv[]) {
  int res = 0;

  // Setup the frontend lib
  casm_frontend_init();

  if (argc != 2) {
    std::cerr << "Error: invalid number of arguments" << std::endl;
      return EXIT_FAILURE;
  }

  if (casm_frontend_pass_1_parse(argv[1]) == nullptr) {
    std::cerr << "Error parsing file" << std::endl;
    res = EXIT_FAILURE;
  } else {
    res = EXIT_SUCCESS;
  }

  casm_frontend_destroy();

  return res;
}
