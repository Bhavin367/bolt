#include "utils.h"

void die(const char* err){
  write(STDIN_FILENO,"\x1b[2J",4); 
  write(STDIN_FILENO,"\x1b[H",3);

  std::perror(err);
  EXIT_FAILURE;
};


