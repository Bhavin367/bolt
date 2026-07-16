#pragma once 
#include "type.h" 
#include <unistd.h>
#include <format>
#include "utils.h"
#include <string>
#include <utility>

void handleScroll();

template <typename... Args>   
void setMessage(std::format_string<Args...> msg, Args&&...args ){ 
  E.statusMessage = std::format(msg,std::forward<Args>(args)...);
};
// explained at Docs/render.md 
// way too much stuff to just add comments 

void drawRows(std::string &ab);

void drawStatusBar(std::string &ab);

void refreshScreen();
