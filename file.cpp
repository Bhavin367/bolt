#include "file.h"
#include "render.h"
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
};
