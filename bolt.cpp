#include "editor.h"
#include "render.h"
#include "file.h"

int main (int argc , char* argv[]) {
  enableRawMode();
  initEditor();

  std::atexit(disableRawMode);

  if (argc >= 2 ) {
    openFile(argv[1]); // we looking something like bolt(argv[0]) something.txt(argv[1]) , pretty much like neovim
  }

  while (1) {
    refreshScreen();
    editorProcessKey() ;  
  };
 
  return EXIT_SUCCESS;
};
