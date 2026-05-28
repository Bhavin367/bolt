#include "render.h"
#include "editor.h"
#include <string>

void refreshScreen(){
  std::string apbuf ; 

  apbuf.append("\x1b[?25l");
  apbuf.append("\x1b[H");

  for (int y = 0 ; y < E.screenrows ; y++ ) {
    apbuf.append(std::to_string(y));
    apbuf.append("\r\n");
  };

  apbuf.append("\r\n");
  apbuf.append("\x1b[0K");
};
