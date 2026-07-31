#include "file.h"
#include "render.h"
#include "utils.h"
#include <cerrno>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <string>
#include <utility>

void openFile(const std::string& filename){
  std::ifstream fp(filename);
   
  if (!fp.is_open()) die("Open file function failed to open !!!");
  
  E.filename = filename ;

  std::string line ;

  while (std::getline(fp,line)){
    if (!line.empty() && line.back() == '\r'){
      line.pop_back();
    };
    // back() checks last charact , pop_back() removes it 
    erow row ; 
    row.chars = std::move(line); 
    updateRow(row); 
    E.rows.push_back(std::move(row)) ;
  };

  E.dirty = 0 ; // just in case ig
};

std::string rowsToString(){
  std::string buf ;  
  for (const auto& row : E.rows ) {
    buf.append(row.chars) ; 
    buf.append("\n") ; 
  };
  return  buf ;
};

void saveFile(){
  if ( E.filename.empty() ) {
    setStatusMessage(" No file name !! ") ;  
    E.dirty = 0 ;  
    return ; 
  }; 

  std::ofstream file(E.filename,std::ios::binary) ; // binary mode better  
 
  if (!file) {
  setStatusMessage(" Can't save ! I/O error : {}" , std::string(strerror(errno))); 
  die("File operations failed : saveFile() ") ;  
  return ; 
  } ;  
  std::string data = rowsToString(); 

  file.write(data.data(),data.size()) ; 

  if (!file) {
    setStatusMessage(" Can't save ! write failed !! "); 
    die("File operations failed : saveFile() .. write ") ; 
    return ; 
  };

  file.close() ; 
  setStatusMessage("\"{}\" {}B written", E.filename, data.size()); 
  E.dirty = 0 ;
};
