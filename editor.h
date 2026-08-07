#pragma once
#include <sys/ioctl.h>
#include "utils.h"
#include <unistd.h>
#include <cerrno>
#include "terminal.h"
#include "type.h"
#include <format>
#include "commands.h"
#include "utils.h"
#include "render.h"

void getWinSize();

void initEditor();

void editorMoveCursor(const int key); // technically char is an int and custom keys wont work if i passed char 

int editorReadKey();

void editorProcessKey();

void editorInsertRow(const std::string& s , size_t at = E.numrows() ) ; 

void editorRowInsertChar(erow& row , int at , int c );

void editorInsertChar(int c) ;

void editorDelRow(int at );

void editorDelCurrentRow() ;

void editorRowDelChar(erow& row , int at ); // lower level function 

void editorDelChar() ; // does all the checking and stuff  
