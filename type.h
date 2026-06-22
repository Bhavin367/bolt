#pragma once

typedef struct editorConfig {
  int cx, cy ; 
  int screenrows ; 
  int screencols ; 
  int rowNumSize ; // for better spacing and stuff   
  char editorMode ; // similar to nvim  
} editorConfig ; 


extern editorConfig E ;

enum editorKey {
  UP = 1000 , // shouldnt intefere with other ascii values hence such no 
  DOWN ,
  LEFT ,
  RIGHT ,
  PAGE_UP ,
  PAGE_DOWN, 
  HOME , 
  END ,
};
