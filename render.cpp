#include "render.h"
#include "utils.h"

void handleScroll(){

  if (E.cy < E.rowoff ) E.rowoff = E.cy ;

  if ( E.cy >= E.rowoff + E.screenrows ){
    E.rowoff = E.cy - E.screenrows + 1;
  };

  if (E.cx < E.rowNumSize ) {
    E.cx = E.rowNumSize ; 
  };
};

void drawRows(std::string &ab){
  int y ; 

  for ( y = 0 ; y < E.screenrows ; ++y){
    int filerow = y + E.rowoff ; // rowoff is essentially rows that are hidden  
    std::string rowNo = std::format("{:>{}}",filerow + 1 , E.rowNumSize - 2);
    // format allows aligning , :> right align 
   
    ab.append(" "); 
    ab.append(rowNo) ; 

    ab.append("\x1b[K"); // clears one line 

    if ( filerow < E.numrows()){
      int len = E.rows[filerow].size() ; 
      if ( len > E.screencols ) len = E.screencols ;
      ab.append(" ") ; 
      ab.append(E.rows[filerow].chars);
    }

    if ( y < E.screenrows - 1){
      ab += "\r\n"; 
    };
  };
};

void refreshScreen(){
  E.rowNumSize = numWidth(E.numrows()) + 2 ;
  handleScroll(); 
  std::string appendBuff ; 

  appendBuff.append("\x1b[?25l"); // hides cursor 
  appendBuff.append("\x1b[H"); 
  drawRows(appendBuff);

  // cursor positioning
  
  appendBuff.append(std::format("\x1b[{};{}H",(E.cy - E.rowoff) + 1 , E.cx + 1));
  
  appendBuff.append("\x1b[?25h"); // show cursor 
  write(STDOUT_FILENO, appendBuff.c_str(),appendBuff.size());
  
};
