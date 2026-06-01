#include "terminal.h"
#include <cstdlib>
#include "editor.h"
#include "render.h"

int main () {
  enableRawMode();
  initEditor();
  while (1) {
    refreshScreen();
  };
  
  disableRawMode(); 
  return EXIT_SUCCESS;
};
