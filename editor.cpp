#include "editor.h"
#include <cstdlib>
#include "utils.h"

editorConfig E ;

void initEditor(){
  E.cx = 0; 
  E.cy = 0 ; 
  getWinSize();
};

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

  return c ; 
};


void editorMoveCursor(const char key){
  switch (key) {
    case 'h':
      E.cx -- ; 
      break ; 
    case 'j' : 
      E.cy ++ ; 
      break ; 
    case 'k' : 
      E.cy -- ; 
      break ; 
    case 'l' : 
      E.cx ++ ; 
      break ; 


  }
};


void editorProcessKey(){
  int c = editorReadKey();

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
      editorMoveCursor(c) ; 
      break ; 
  }
};


