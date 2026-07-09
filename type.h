#pragma once
#include <string>
#include <vector>

struct erow {
  std::string chars ; 
  size_t size() const{ return chars.size(); } ; 
  std::string render ;
};

typedef struct editorConfig {
  int cx, cy ; 
  int screenrows ; 
  int screencols ; 
  int rowNumSize ; // for better spacing and stuff   
  char editorMode ; // similar to nvim  
  std::vector<erow> rows ; 
  int numrows() const { return rows.size() ; }; // it updates itself then , hopefully  
  int rowoff ; 
  int coloff ; 
  std::string filename ;
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

