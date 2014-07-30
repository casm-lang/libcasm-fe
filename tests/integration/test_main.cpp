#include "libsyntax/driver.h"

// driver must be global, because it is needed for YY_INPUT
// defined in src/libsyntax/driver.cpp
extern Driver *global_driver;

int main (int argc, char *argv[]) {
  int res = 0;

  // Setup the driver
  Driver driver;
  global_driver = &driver;

  if (argc != 2) {
    std::cerr << "Error: invalid number of arguments" << std::endl;
      return EXIT_FAILURE;
  }

  if (driver.parse(argv[1]) == nullptr) {
    std::cerr << "Error parsing file" << std::endl;
    res = EXIT_FAILURE;
  } else {
    res = EXIT_SUCCESS;
  }
  /*
  if (driver.result) {
    delete driver.result;
  }

  */
  return res;
}
