#include "editor.h"

editorConfig E ;

void initEditor(){
  getWinSize();
  E.rowNumSize = numWidth(E.numrows()) + 2 ;
  E.cx = E.rowNumSize; 
  E.cy = 0 ; 
  E.editorMode = 'e'; 
  E.rowoff = 0 ; 
  E.coloff = 0 ; 
  std::string curIn; // i meant cursor initialisation 

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
    if (nread == 1 && errno != EAGAIN) die("Editor read key "); 
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
    switch (key) {
      case 'h' :
      case LEFT :  
        E.cx = (E.cx > E.rowNumSize  ) ? E.cx - 1 : E.rowNumSize  ; 
        break ; 
      
      case 'j' :
      case DOWN : 
        E.cy <= E.numrows() + E.screenrows  ? ++E.cy : E.cy = E.numrows() + E.screenrows + 1; 
        break ; 
      
      case 'k' : 
      case UP :  
        E.cy = (E.cy > 0 ) ? E.cy -1 : 0 ; 
        break ;

      case 'l' : 
      case RIGHT :  
        E.cx ++ ; 
        break ; 

      case '0' : 
      case HOME : 
        E.cx = E.rowNumSize ; 
        break ; 

      case '$' : 
      case END :
        E.cx = E.screencols ; 
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
          E.cy = E.screenrows - 1 ;
          break ; 
        }; 

        if (E.cy + E.screenrows < E.numrows()){
          E.cy += E.screenrows - 1;
        } else {
          E.cy = E.numrows() - 1 ; 
        };

        break ; 
    }

};


void editorProcessKey(){
  int c = editorReadKey();

  if (E.editorMode == 'e'){
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
        editorMoveCursor(c) ; 
        break ; 
    }
  };

};


