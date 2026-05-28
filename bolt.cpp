#include "terminal.h"
#include <cstdlib>
#include "editor.h"
#include "render.h"

int main () {
  while (1) {
    enableRawMode();
    initEditor();
    refreshScreen();
  };
  
  disableRawMode(); 
  return EXIT_SUCCESS;
};
