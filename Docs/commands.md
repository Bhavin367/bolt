
# Commands 

- Im skipping most functions for now as they are self explanatory nothing really confusing except 


## processCommand 

        void processCommand(int c ){
          if (c == '\n' || c == '\r' ){
            executeCommand(E.commandBuffer); 
            resetCommandMode() ;  
          } else {
            E.commandBuffer += (char)c ;
            E.statusMessage = ":" + E.commandBuffer ;  
          };
        };

- *c == \r* - that tripped me a lot , basically in raw mode, entering newline keyboard doesnt send 
\n or ASCII 10 instead it sends \r or ASCII 13. 
