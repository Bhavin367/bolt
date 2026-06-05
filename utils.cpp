#include "utils.h"
#include <cstdlib>


void die(const char* err){
  std::perror(err);
  EXIT_FAILURE;
};
