#include "terminal.h"
#include <unistd.h>


static struct termios orig_termios ; 

void disableRawMode(){
  tcsetattr(STDIN_FILENO,TCSAFLUSH,&orig_termios);
};

void enableRawMode(){
  tcgetattr(STDIN_FILENO,&orig_termios);
  struct termios raw = orig_termios ; 

  std::atexit(disableRawMode);

  raw.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP
                 | INLCR | IGNCR | ICRNL | IXON);
  raw.c_oflag &= ~OPOST;
  raw.c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);
  raw.c_cflag &= ~(CSIZE | PARENB);
  raw.c_cflag |= CS8;

  tcsetattr(STDIN_FILENO,TCSAFLUSH,&raw);

};

