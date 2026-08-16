#pragma once
#include <format>
#include <unistd.h>
#include <stdlib.h>
#include <utility>
#include <vector>
#include "type.h"

void die(const char* err);

void clearScreen();

void close() ; 

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

static inline bool is_not_space(char c );

void ltrim(std::string& s);

void rtrim(std::string& s);

void trim(std::string& s) ;

int rowCxToRx(erow& row , int cx );

std::vector<std::string> splitCommands(std::string& cmd ) ;

void resetEditorState();
