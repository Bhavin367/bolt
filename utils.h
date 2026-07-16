#pragma once
#include <format>
#include <unistd.h>
#include <stdlib.h>
#include <utility>
#include "type.h"

void die(const char* err);

constexpr char ctrl(char k){
  return k & 0x1f ; 
} ; // since this runs on compile time this needs to be defined in header

int numWidth(int rowNo); 

template <typename... Args>
void setStatusMessage(std::format_string<Args...> msg , Args&&... args){
  E.statusMessage = std::format(msg, std::forward<Args>(args)...);
};

// explained at Docs/utility.md 
// way too much stuff to just add comments 


