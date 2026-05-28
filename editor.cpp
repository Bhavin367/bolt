#include "editor.h"
#include <sys/ioctl.h>

editorConfig E ;

void initEditor(){
  E.cx = 0; 
  E.cy = 0 ; 
  E.screencols = 0 ; 
  E.screenrows = 0 ; 
};

void getWinSize(){
  struct winsize ws ; 
  ioctl(1,TIOCGWINSZ,&ws);

  E.screencols = ws.ws_col ; 
  E.screenrows = ws.ws_row ; 
};
