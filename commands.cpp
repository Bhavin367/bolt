#include "commands.h"
#include "utils.h"

// for cur pos, bg idk whatever i feel like  
void initCommandMode(){  
  std::string command  = readCommand(); 

  if (command == "q"){
    write(STDOUT_FILENO,"\x1b[2J",4); 
    write(STDOUT_FILENO,"\x1b[H",3); 
    std::exit(EXIT_SUCCESS) ;
  };
};

std::string readCommand(){
  std::string buffer ;
  char c ;
  
  while(true){
    int nread = static_cast<int>(read(STDIN_FILENO,&c,1)) ;
    if ( nread == -1 && errno != EAGAIN ) {
      die("Command read failed !! ");
    };  
  
    if (c == '\n' || nread == 0 ) break ; // nread == 0 => EOF 
    buffer.push_back(c);
  };

  return buffer ; 
};
