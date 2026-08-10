#include "editor.h"
#include "file.h"
#include "render.h"
#include "type.h"
#include "utils.h"
#include <cerrno>
#include <cstddef>
#include <sys/ioctl.h>
#include <unistd.h>

editorConfig E ;

void initEditor(){
  getWinSize();
  E.rowNumSize = numWidth(E.numrows()) + 2 ;
  E.cx = 0 ;  
  E.cy = 0 ; 
  E.rx = 0 ;  
  E.editorMode = EDITOR; 
  E.rowoff = 0 ; 
  E.coloff = 0 ; 
  E.dirty =  false ;  
  E.screenrows -= 2 ; // this one's for status barrrr 
  // E.filename stays null unless added by file part 

  setStatusMessage(">Got a cup of Coffee ? ");
   
  write(STDOUT_FILENO,"\x1b[2 q",5);// i need that block intially , we can change when user switch to read/write  

};
// \x1b[6 q gives that normal line, make it 5 for blinking  

void getWinSize(){
  struct winsize ws ; 
  if(ioctl(1,TIOCGWINSZ,&ws) == -1 || ws.ws_col == 0 ){
    die("Get winsize() -- editor ");
  };

  E.screencols = ws.ws_col  ; 
  E.screenrows = ws.ws_row  ; 
};

int editorReadKey(){
  int nread ;
  char c ; 

  while ((nread = read(STDIN_FILENO, &c,1 )) != 1){
    if (nread == -1 && errno != EAGAIN) die("Editor read key "); 
  };

  if ( c == '\x1b'){ // checking if its an arrow key  
    char seq[3] ;  

    if (read(STDIN_FILENO, &seq[0],1) != 1) return '\x1b' ;  
    if (read(STDIN_FILENO, &seq[1],1) != 1) return '\x1b' ; 

    if (seq[0] == '[' ){
      
      // page up and down got ESC[5~ , ESC[6~ , del is ESC[3~
      if (seq[1] >= '0' && seq[1] <= '9'){
        if (read(STDIN_FILENO,&seq[2],1) != 1) return '\x1b' ; 

        if (seq[2] == '~'){
          switch (seq[1]){
            case '1' : return HOME ;
            case '4' : return END ; 
            case '5' : return PAGE_UP ; 
            case '6' : return PAGE_DOWN ;  
            case '7' : return HOME ; 
            case '8' : return END ; 
          };
        };

      }else {
        switch (seq[1]){
          case 'A' : return UP;
          case 'B' : return DOWN ; 
          case 'C' : return RIGHT  ; 
          case 'D' : return LEFT ;
          case 'H' : return HOME ; 
          case 'F' : return END  ;
        };
      }
    } else if ( seq[0] == 'O'){
      switch (seq[1]) {
        case 'H' : return HOME;
        case 'F' : return END; 
      }
    };
  } 

  return c ; 
};
// HOME and END  keys are pretty weird some uses ESC[4~ and ESC[5~ , some uses 7 and 8 , 
// apparently kitty uses ESCOH and ESCOF makes no damn sense 


void editorMoveCursor(const int key){
    erow* row = (E.cy < E.numrows()) ? &E.rows[E.cy] : nullptr ;  

    switch (key) {
      case 'h' :
      case LEFT :  
        E.cx = (E.cx > 0 ) ? E.cx - 1 : 0 ; 
        break ; 
      
      case 'j' :
      case DOWN : 
        E.cy < E.numrows() ? ++E.cy : E.cy = E.numrows() ; 
        break ; 
      
      case 'k' : 
      case UP :  
        E.cy = (E.cy > 0 ) ? E.cy -1 : 0 ; 
        break ;

      case 'l' : 
      case RIGHT :  
        if (row && E.cx < row->size() )E.cx ++ ;  
        break ; 

      case '0' : 
      case HOME :
      case ctrl('h'):
        E.cx = 0; 
        break ; 

      case '$' : 
      case END :
      case ctrl('l'): 
        if (row) E.cx = row->size() ; 
        break ; 
   
      case PAGE_UP : 
      case ctrl('k'):
        
        if (E.cy > E.screenrows) {
          E.cy -= E.screenrows -1 ; 
        } else {
          E.cy = 0 ; 
        }; 

        break ;

      case PAGE_DOWN : 
      case ctrl('j'):
        if ( ( !E.numrows() || E.numrows() == 0 ) ){
          E.cy = 0 ;
          break ; 
        }; 

        if (E.cy + E.screenrows  < E.numrows()){
          E.cy += E.screenrows;
        } else {
          E.cy = E.numrows() ; 
        };

        break ; 
    }

    row = (E.cy >= E.numrows()) ? nullptr : &E.rows[E.cy] ; 
    int rowLen = row ? row->size()   : 0 ; 
    if (E.cx > rowLen ) E.cx = rowLen ; 
};


void editorProcessKey(){
  int c = editorReadKey();

  if (E.editorMode == EDITOR){
    switch (c) {
      case ctrl('q'):
        write(STDOUT_FILENO,"\x1b[2J",4); 
        write(STDOUT_FILENO,"\x1b[H",3); 
        std::exit(EXIT_SUCCESS) ; // without exit() program wont actually stop  
        break ; 

      case 'h' :
      case 'k' : 
      case 'j' : 
      case 'l' : 
      case UP : 
      case DOWN : 
      case LEFT : 
      case RIGHT : 
      case HOME : 
      case END : 
      case '$' : 
      case '0' : 
      case PAGE_DOWN : 
      case PAGE_UP : 
      case ctrl('j'):
      case ctrl('k'):
      case ctrl('h'):
      case ctrl('l'):
        editorMoveCursor(c) ; 
        break ; 
      
      case 'i' :
        E.editorMode =  INSERT ;
        setStatusMessage(" --INSERT-- ");
        break;
    
      case ':' : 
        initCommandMode(); 
        break; 
   
        // for some reason init char seq breaks without enclosing in {} 
      case 'd' : {
        char seq ; 
        int nread ; 
        while ((nread = read(STDIN_FILENO,&seq ,1 )) == 0 ||  nread == -1  ){
          if (nread == -1 && errno != EAGAIN) die("Editor read command key [del]"); 
        };
      
        switch (seq) {
          case 'd' : 
            editorDelCurrentRow() ;
            break ; 
          
          // for later  
          case 'w' : 
            break ; 

          default : 
            break ; 
        };
      
        break ; 
      } 
    }
  } 
  else if (E.editorMode == INSERT ){
    switch (c) {
      case '\x1b':
        E.editorMode = EDITOR ; 
        setStatusMessage("");
        break;

      case BACKSPACE : 
      case ctrl('h') : 
      case DEL_KEY   : 
        editorDelChar() ; 
        break ;
     
      case CTRL('s'):
        saveFile(); 
        break ; 
      
      case '\r' :
      case '\n' : 
        editorInsertNewLine();
        break ; 

      default: 
        editorInsertChar(c) ; 
        break ; 
    };
  } 
  else if (E.editorMode == COMMAND ){
    processCommand(c);
  };
};

// need this to create a new row to Rows whenever user goes to last unused line 
void editorInsertRow(const std::string &s , size_t at) {
  erow row  ;
  row.chars = s ; 
  E.rows.insert(E.rows.begin() + at ,std::move(row)) ; 
  updateRow(E.rows[at]) ; 
  E.dirty = true ; 
};

void editorInsertNewLine(){
  if (E.cx == 0 ) {
    editorInsertRow("",E.cy) ; 
  } else {
    erow& row  = E.rows[E.cy] ;  
    editorInsertRow(row.chars.substr(E.cx),E.cy + 1) ; 
    row.chars.erase(E.cx);
    updateRow(row) ; 
  };
  E.cx = 0 ; 
  E.cy ++ ; 
  E.dirty = true ; 
};

void editorRowInsertChar(erow &row, int at, int c){
  if (at < 0 || at > static_cast<int>( row.chars.size()) ) at = static_cast<int>(row.chars.size());

  row.chars.insert(at,1,(char)c); // insert(postion, no of copies , char )
  
  updateRow(row); 
  E.dirty = true ; 
};


void editorInsertChar(int c){
  if (E.cy == E.numrows() ){
    editorInsertRow("") ;
  }  

  editorRowInsertChar(E.rows[E.cy],E.cx ,c) ;
  E.cx++;
};

// static cast is absolutely uncessary since numrows() already have guard rails
// which i constantly forget and is too lazy to changee 
void editorDelRow(int at ) {
  if (at < 0 || at >= static_cast<int>(E.numrows()) ) return; 

  E.rows.erase(E.rows.begin() + at ) ; 
  E.dirty = true ; 
};

void editorDelCurrentRow(){
  if (E.rows.empty()) return ; 

  editorDelRow(E.cy) ; 

  if (E.rows.empty()) {
    editorInsertRow("") ; 
    E.cy = 0 ; 
  }else if (E.cy >= E.numrows() ){
    E.cy = E.numrows() - 1 ; 
  };
  
  int newLen = static_cast<int>(E.rows[E.cy].chars.size()) ; 
  E.cx = std::min(E.cx , newLen ) ; 
  
};

void editorRowDelChar(erow &row, int at){
  if ( at < 0 || at > static_cast<int>(row.chars.size())) at = static_cast<int>(row.chars.size()); 

  row.chars.erase(at,1) ; 
  updateRow(row) ; 
  E.dirty = true ; 
};


void editorDelChar(){
  if (E.cy >= E.numrows() ) return ;  // cant be greater still im adding a check juest in case 
  if (E.cx == 0 && E.cy == 0 ) return  ;
  
  erow& row = E.rows[E.cy] ; 

  if (E.cx > 0 ) {
    editorRowDelChar(row,E.cx - 1) ; 
    E.cx-- ; 
  } else {
    erow& prev = E.rows[E.cy - 1 ] ; 
    E.cx = static_cast<int>(prev.chars.size()) ;
    prev.chars.append(row.chars) ; 
    updateRow(prev) ; 
    editorDelRow(E.cy); 
    E.cy-- ;  
  }; 
};























