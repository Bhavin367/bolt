#include "utils.h"
#include "file.h"
#include "type.h"
#include <algorithm>

void die(const char* err){
  write(STDIN_FILENO,"\x1b[2J",4); 
  write(STDIN_FILENO,"\x1b[H",3);

  std::perror(err);
  EXIT_FAILURE;
};

void close(){
    write(STDOUT_FILENO,"\x1b[2J",4);
    write(STDOUT_FILENO,"\x1b[H",3);
    std::exit(EXIT_SUCCESS);
    return ;
} ;

int numWidth(int rowNo){
  int count = 1 ;

  while (rowNo >= 10 ) {
    rowNo = rowNo/10 ; 
    ++count ;  
  }; 

  return count ;
};

static inline bool is_not_space(char c){
  return c == ' ' ? false : true ; 
};

void ltrim(std::string &s){
  auto first_non_space = std::find_if(s.begin(), s.end(),is_not_space); 
  s.erase(s.begin(),first_non_space); 
};


void rtrim(std::string &s){
  auto last_non_space = std::find_if(s.rbegin(), s.rend(),is_not_space);
  s.erase(last_non_space.base(),s.end());
};


void trim(std::string &s){
  ltrim(s); 
  rtrim(s);
};

int rowCxToRx(erow &row, int cx){
  int rx = 0 ; 
  int j ; 

  for ( j = 0 ; j < cx  ; ++j ){
    if (row.chars[j] == '\t'){
      rx += (TAB_STOP - 1) - (rx% TAB_STOP) ; 
    };
    rx++ ;
  };

  return rx ; 
};
