#pragma once
#include <string>
#include <vector>

constexpr int TAB_STOP = 8 ; 

enum editorModes {
EDITOR = 1050 ,
INSERT ,
COMMAND , 
VISUAL ,
};
 
struct erow {
  std::string chars ; 
  size_t size() const{ return render.size(); } ; 
  std::string render ;
};

typedef struct editorConfig {
  int cx, cy ; 
  int screenrows ; 
  int screencols ; 
  int rowNumSize ; // for better spacing and stuff   
  editorModes editorMode ; // similar to nvim  
  std::vector<erow> rows ; 
  int numrows() const { return rows.size() ; }; // it updates itself then , hopefully  
  int rowoff ; 
  int coloff ; 
  std::string filename ;
  std::string statusMessage ; // info line below file type and cur pos   
  int lastCx , lastCy ; // this ones for remembering where curosr was after execu commands  
  std::string commandBuffer ;
  bool dirty  ; 
} editorConfig ; 


extern editorConfig E ;

enum editorKey {
  BACKSPACE = 127 ,  
  UP = 1000 , // shouldnt intefere with other ascii values hence such no 
  DOWN ,
  LEFT ,
  RIGHT ,
  PAGE_UP ,
  PAGE_DOWN, 
  HOME , 
  END ,
  DEL_KEY ,
};


