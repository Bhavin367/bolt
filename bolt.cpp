#include "editor.h"
#include "render.h"

int main () {
  enableRawMode();
  initEditor();

  std::atexit(disableRawMode);

  while (1) {
    refreshScreen();
    editorProcessKey() ;  
  };
 
  return EXIT_SUCCESS;
};
