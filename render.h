#pragma once 
#include "type.h" 
#include <unistd.h>
#include <format>
#include "utils.h"
#include <string>
#include <utility>

void handleScroll();

// template function has to be defined in .h 
template <typename... Args> // 0 or multiple arguments of different type  
void setMessage(std::format_string<Args...> msg, Args&&...args ){ 
  E.statusMessage = std::format(msg,std::forward<Args>(args)...);
};

// format_string basically starting screaming at compile time instead of shooting be at runtime

void drawRows(std::string &ab);

void drawStatusBar(std::string &ab);

void refreshScreen();
