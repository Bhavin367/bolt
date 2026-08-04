#include "commands.h"
#include "file.h"
#include "type.h"
#include "utils.h"
#include <cstdlib>

void resetCommandMode(){
  E.cx = E.lastCx ; 
  E.cy = E.lastCy ; 
  E.editorMode = EDITOR ; 
  E.commandBuffer.clear() ; 
};

void executeCommand(std::string &command){
  if ( command.empty()) {
    setStatusMessage("No commands found !!! ");
    return;  
  }; 

  trim(command); 

  if (command == "q!") {
    close() ; 
    return ;  
  }
  else if ( command == "q"){
    if (E.dirty ) {
      setStatusMessage("Unsaved changes found in ''{}'' , use q! to force quit !! ", E.filename ); 
      return ; 
    }; 
    close(); 
    return ; 
  } 
  else if (command == "w") {
    saveFile(); 
    return ; 
  }
  else if (command == "wq"){
    saveFile() ; 
    close() ; 
    return ; 
  } ; 
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


