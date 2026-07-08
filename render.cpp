#include "render.h"
#include <unistd.h>

void handleScroll(){

  if (E.cy < E.rowoff ) E.rowoff = E.cy ;

  if ( E.cy >= E.rowoff + E.screenrows ){
    E.rowoff = E.cy - E.screenrows + 1;
  };

  if (E.cx < E.coloff ){
    E.coloff = E.cx ;
  };  

  if (E.cx >= E.coloff + E.screencols ) {
    E.coloff = E.cx - E.screencols + 1;
  };
};

void drawRows(std::string &ab){
  int y ; 

  for ( y = 0 ; y < E.screenrows ; ++y){
    int filerow = y + E.rowoff ; // rowoff is essentially rows that are hidden  
    std::string rowNo = std::format("{:>{}}",filerow + 1  , E.rowNumSize );
    // format allows aligning , :> right align 
   
    ab.append(rowNo) ; 

    ab.append("\x1b[K"); // clears one line 

    if ( E.numrows() &&  filerow < E.numrows()){
      int len = (int)E.rows[filerow].size() - E.coloff ; // apparently this guy was giving size_t we need INT  
      len = len <= 0 ? 0 : len ; 
      if ( len > E.screencols - 2) len = E.screencols - 2 ;
      ab.append(" ") ; 
      if (len > 0 ) ab.append(E.rows[filerow].chars,E.coloff,len);
    }

      ab += "\r\n"; 
  };
};

void drawStatusBar(std::string& ab){
  int len = 0 ; 
   
  ab.append("\x1b[7m");
  while ( len < E.screencols ) {
    ab += " " ;
    ++len; 
  };

  ab.append("\x1b[m");
};

void refreshScreen(){
  E.rowNumSize = numWidth(E.numrows()) + 2 ;
  handleScroll(); 
  std::string appendBuff ; 

  appendBuff.append("\x1b[?25l"); // hides cursor 
  appendBuff.append("\x1b[H"); 
  drawRows(appendBuff);
  drawStatusBar(appendBuff);
  
  // cursor positioning
  
  appendBuff.append(std::format("\x1b[{};{}H",(E.cy - E.rowoff) + 1 , ( E.cx - E.coloff ) + E.rowNumSize + 2));
  
  appendBuff.append("\x1b[?25h"); // show cursor 
  write(STDOUT_FILENO, appendBuff.c_str(),appendBuff.size());
};
