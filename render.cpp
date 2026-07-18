#include "render.h"
#include "type.h"

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
    int filerow = y + E.rowoff; // rowoff is essentially rows that are hidden  
    ab.append("\x1b[2m"); // faint mode for numberings  
    
    std::string rowNo = std::format("{:>{}}",filerow + 1  , E.rowNumSize );  // for future me i intentionally added that + 1
    // format allows aligning , :> right align 
    

    ab.append(rowNo) ; 
    ab.append("\x1b[m");
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
  ab.append("\x1b[7;40m");
  
  int len = 0 ; 
  std::string fileName = E.filename.empty() ? "[No Name] - 0 lines " : E.filename + " - " + std::to_string(E.numrows()) + " lines";
  std::string curPos = " " + std::to_string((int)E.cx) + "/" + std::to_string((int)E.cy) + " "; // i just want cursor position on right now, might add other stuff in future  
  
  len = fileName.length() ;   
  if ( len > E.screencols ) {
    len = E.screencols ; 
    fileName = fileName.substr(0,len); // clamping filename incase len is smaller than filename.length  
  }; 

  ab.append(fileName);
  while ( len < E.screencols ) {
    if ( E.screencols - len == curPos.length()){
      ab.append(curPos);
      break; 
    } else {
      ab += " " ;
      ++len; 
    }; 
  };

  ab.append("\x1b[m");
  ab.append("\r\n");
};

void drawMessageBar(std::string &ab){
  ab.append("\x1b[K");
  int len = static_cast<int>(E.statusMessage.length());  // why not just (int), cause I CAN 

  if( len > E.screencols ) len = E.screencols ; 
  ab.append(E.statusMessage.c_str(), len); // c_str() is a pointer to that variable so we dont have to make unnessary copies 
};

// to decide stuff like cursor state depending on editor mode
void renderStyle(std::string &ab){
  static editorModes last = static_cast<editorModes>(-1); // -1 is an unlikely no
  
  if (last == E.editorMode ){ 
    return ;
  } else {
    last = E.editorMode ;
  }; 

  if (E.editorMode == INSERT){
    ab.append("\x1b[5 q");
  } 
  else if ( E.editorMode == EDITOR){
    ab.append("\x1b[2 q");
  };
};

void refreshScreen(){
  E.rowNumSize = numWidth(E.numrows()) + 2 ;
  handleScroll(); 
  std::string appendBuff ; 

  appendBuff.append("\x1b[?25l"); // hides cursor 
  appendBuff.append("\x1b[H"); 
  drawRows(appendBuff);
  drawStatusBar(appendBuff);
  drawMessageBar(appendBuff); 
  renderStyle(appendBuff); 

  // cursor positioning
  
  appendBuff.append(std::format("\x1b[{};{}H",(E.cy - E.rowoff) + 1 , ( E.cx - E.coloff ) + E.rowNumSize + 2 ));
  
  appendBuff.append("\x1b[?25h"); // show cursor 
  write(STDOUT_FILENO, appendBuff.c_str(),appendBuff.size());
};
