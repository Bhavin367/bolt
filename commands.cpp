#include "commands.h"
#include "utils.h"

int readCommand(){
  int nread ; 
  char c ; 

  while ((nread = read(STDIN_FILENO,&c,1)) != 1 ){
    if (nread == -1 ) die("Read Command func failed ");
  };

  return c ; 
};

void executeCommand(const std::string &command){
  if ( command.empty()) {
    setStatusMessage("");
  }; 

};

void processCommand(int c ){
  if (c == '\n'){
    E.cx = E.lastCx ; 
    E.cy = E.lastCy ; 
    E.editorMode = EDITOR ; 
    E.statusMessage = "" ;
    executeCommand(E.commandBuffer); 
    E.commandBuffer.clear() ; 
  } else {
    E.commandBuffer += (char)c ;
  };
};

// for cur pos, bg idk whatever i feel like  
void initCommandMode(){  
  E.editorMode = COMMAND ;  
  E.lastCx = E.cx ; 
  E.lastCy = E.cy ; 
  E.commandBuffer.clear() ;
  E.statusMessage = ":" ;
}; 


