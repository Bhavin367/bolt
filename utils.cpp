#include "utils.h"

void die(const char* err){
  write(STDIN_FILENO,"\x1b[2J",4); 
  write(STDIN_FILENO,"\x1b[H",3);

  std::perror(err);
  EXIT_FAILURE;
};


int numWidth(int rowNo){
  int count = 1 ;

  while (rowNo >= 10 ) {
    rowNo = rowNo/10 ; 
    ++count ;  
  }; 

  return count ;
};
