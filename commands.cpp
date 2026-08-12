#include "commands.h"
#include "utils.h"
#include <exception>
#include <vector>


commandManager cmdManager ; 

void resetCommandMode(){
  E.cx = E.lastCx ; 
  E.cy = E.lastCy ; 
  E.editorMode = EDITOR ; 
  E.commandBuffer.clear() ; 
};

// for cur pos, bg idk whatever i feel like  
void initCommandMode(){  
  E.editorMode = COMMAND ;  
  E.lastCx = E.cx ; 
  E.lastCy = E.cy ; 
  E.commandBuffer.clear() ;
  E.statusMessage = ":" ;
}; 

commandManager::commandManager(){
  commandTable = {
      {"q!",[](const commandArgs &args) {close();}},
      
      {"q",[](const commandArgs &args ) {
        if (E.dirty) { 
          setStatusMessage("Unsaved changes found in ''{}'' , use q! to force quit !! ", E.filename );   
          return ; 
        }; 

        close() ; 
      }}, 
    
      {"wq",[](const commandArgs &args) {
        if (args.size() > 1 ) { setStatusMessage("Too many arguments !!! "); 
        return;  
        }; 
        if (!args.empty()) E.filename = args[0] ;        
        saveFile(); 
        close() ; 
      }},

      {"w",[](const commandArgs &args){
        if (args.size() > 1 ) { 
          setStatusMessage("Too many arguments !!! ") ;
          return ;  
        };

        if (!args.empty()) E.filename = args[0] ; 

        saveFile(); 

      }},
    }; 

};

void commandManager::executeCommand(std::string& cmd ) {
  if (cmd.empty()){  
    setStatusMessage("No commands found !! ");
    return ; 
  };

  std::vector<std::string> tokens = splitCommands(cmd); 

  if(tokens.empty()) {
    setStatusMessage("Command processor error !!! ");
    return ;  
  } ; 

  std::string name  = tokens[0] ; // main stuff like w wq q / and all that 

  commandArgs args(tokens.begin() + 1 , tokens.end()) ;
  auto it = commandTable.find(name);
  
  if (it == commandTable.end()){ // end is one term after last actual value 
    setStatusMessage("Command : {} not recogonised ", cmd ) ; 
    return ;  
  };

  it->second(args);  
};

// it is basically unorderedlist(std::string,commandFunc) , so 
// it->second basically pass arguments to commandFunc 

void processCommand(int c ){
  if (c == '\n' || c == '\r' ){
    cmdManager.executeCommand(E.commandBuffer) ; 
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


