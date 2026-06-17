#include "render.h"

void drawRows(std::string &ab){
  int y ; 

  for ( y = 0 ; y < E.screenrows ; ++y){
    std::string rowNo = std::to_string(y); 
    ab.append(" "); 
    ab.append(rowNo) ; 

    ab.append("\x1b[K"); // clears one line 

    if ( y < E.screenrows - 1){
      ab += "\r\n"; 
    };
  };
};

void refreshScreen(){
  std::string appendBuff ; 

  appendBuff.append("\x1b[?25l"); // hides cursor 
  appendBuff.append("\x1b[H"); 
  drawRows(appendBuff);

  // cursor positioning
  
  appendBuff.append(std::format("\x1b[{};{}H",E.cy + 1 , E.cx + 1));
  
  appendBuff.append("\x1b[?25h"); // show cursor 
  write(STDOUT_FILENO, appendBuff.c_str(),appendBuff.size());

};
