#pragma once
#include <termios.h>
#include <unistd.h>
#include "utils.h"
#include <string>
#include "type.h"

int readCommand(); 

void executeCommand(const std::string &command);

void processCommand(int c);

void initCommandMode();


