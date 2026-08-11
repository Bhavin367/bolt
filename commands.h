#pragma once
#include <termios.h>
#include <unistd.h>
#include "utils.h"
#include <string>
#include "type.h"
#include "file.h"
#include "utils.h"
#include <functional>

using commandArgs = std::vector<std::string> ; 
using commandFunc = std::function<void(const commandArgs&)> ;

class commandManager {
  private: 
    std::unordered_map<std::string,commandFunc> commandTable ; 

  public: 
    commandManager() ;
    void executeCommand(std::string& cmd);
};


void resetCommandMode();
void initCommandMode();
void processCommand(int c );
