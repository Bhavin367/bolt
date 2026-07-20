#pragma once
#include <termios.h>
#include <unistd.h>
#include "utils.h"
#include <string>
#include "type.h"

void initCommandMode();

std::string readCommand();
