/*#include <stdlib.h>*/
/*#include <ctype.h>*/
/*#include <stdio.h>*/
/*#include <termios.h>*/
/*#include <unistd.h>*/
/*struct termios orig_termios;*/
/*void disableRawMode() {*/
  /*tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);*/
/*}*/
/*void enableRawMode() {*/
  /*tcgetattr(STDIN_FILENO, &orig_termios);*/
  /*atexit(disableRawMode);*/
  /*struct termios raw = orig_termios;*/
  /*raw.c_lflag &= ~(ECHO);*/
  /*tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);*/
/*}*/
/*int main() {*/
  /*enableRawMode();*/
  /*char c;*/
  /*while (read(STDIN_FILENO, &c, 1) == 1 && c != 'q') {*/
    /*if (iscntrl(c)) {*/
      /*printf("%d\n", c);*/
    /*} else {*/
      /*printf("%d ('%c')\n", c, c);*/
    /*}*/
  /*}*/
  /*return 0;*/
/*}*/

#include<unistd.h>
#include<fcntl.h>
#include<stdio.h>

int main()
{

if((write(STDIN_FILENO,"arrgh!",6))==-1)
{
    printf("error writing to file");
}

char c;

read(STDIN_FILENO,&c,10);
printf("printed: %s\n", &c);

}
