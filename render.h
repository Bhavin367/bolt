#pragma once 
#include "type.h" 
#include <unistd.h>
#include <format>
#include "utils.h"
#include <string>

void handleScroll();

void drawRows(std::string &ab);

void drawStatusBar(std::string &ab);

void drawMessageBar(std::string &ab);

void refreshScreen();
