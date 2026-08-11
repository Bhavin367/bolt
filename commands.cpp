#include "commands.h"
#include "utils.h"
#include <vector>

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

class commandManager {
  private: 
    std::unordered_map<std::string,commandFunc> commandTable  = 

  public: 
    void executeCommand()
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

  std::vector<std::string> token ; 

};


// void executeCommand(std::string &command){
//   if ( command.empty()) {
//     setStatusMessage("No commands found !!! ");
//     return;  
//   }; 
//
//   trim(command); 
//
//   if (command == "q!") {
//     close() ; 
//     return ;  
//   }
//   else if ( command == "q"){
//     if (E.dirty ) {
//       setStatusMessage("Unsaved changes found in ''{}'' , use q! to force quit !! ", E.filename ); 
//       return ; 
//     }; 
//     close(); 
//     return ; 
//   } 
//   else if (command == "w") {
//     saveFile(); 
//     return ; 
//   }
//   else if (command == "wq"){
//     saveFile() ; 
//     close() ; 
//     return ; 
//   } ; 
// };
//
// void processCommand(int c ){
//   if (c == '\n' || c == '\r' ){
//     executeCommand(E.commandBuffer); 
//     resetCommandMode() ;  
//   } 
//   else if ( c == '\b' || c == BACKSPACE || c == ctrl('h')){
//     if (!E.commandBuffer.empty()) {
//       E.commandBuffer.pop_back() ; 
//       E.statusMessage = ":" + E.commandBuffer ; 
//     } else {
//       resetCommandMode() ;  
//     }; 
//   }  
//   else {
//     E.commandBuffer += (char)c ;
//     E.statusMessage = ":" + E.commandBuffer ;  
//   };
// };
//

