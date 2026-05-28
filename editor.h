#pragma once
#include <sys/ioctl.h>

typedef struct editorConfig {
  int cx, cy ; 
  int screenrows ; 
  int screencols ; 
} editorConfig ; 


extern editorConfig E ;

void initEditor();

void getWinSize();
