#pragma once
#include <unistd.h>
#include <cstdio>
#include <stdlib.h>

void die(const char* err);

constexpr char ctrl(char k){
  return k & 0x1f ; 
};   // since this runs on compile time this needs to be defined in header 
