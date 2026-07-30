#include "commands.h"
#include "type.h"
#include "utils.h"

void resetCommandMode(){
  E.cx = E.lastCx ; 
  E.cy = E.lastCy ; 
  E.editorMode = EDITOR ; 
  E.statusMessage = " " ; 
  E.commandBuffer.clear() ; 
};

void executeCommand(std::string &command){
  if ( command.empty()) {
    setStatusMessage("No commands found !!! ");
    return;  
  }; 

  trim(command); 

  if (command == "q") {
    write(STDOUT_FILENO,"\x1b[2J",4);
    write(STDOUT_FILENO,"\x1b[H",3);
    std::exit(EXIT_SUCCESS);
    return ;  
  };
};

void processCommand(int c ){
  if (c == '\n' || c == '\r' ){
    executeCommand(E.commandBuffer); 
    resetCommandMode() ;  
  } 
  else if ( c == '\b' || c == BACKSPACE || c == ctrl('h')){
    if (!E.commandBuffer.empty()) {
      E.commandBuffer.pop_back() ; 
      E.statusMessage = ":" + E.commandBuffer ; 
    } else {
      resetCommandMode() ;  
    }; 
  }  
  else {
    E.commandBuffer += (char)c ;
    E.statusMessage = ":" + E.commandBuffer ;  
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


