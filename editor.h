#pragma once
#include <sys/ioctl.h>
#include "utils.h"
#include <unistd.h>
#include <cerrno>
#include "terminal.h"
#include "type.h"

void getWinSize();

void initEditor();

int editorReadKey();

void editorProcessKey();
