#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
struct termios orig_termios;
void disableRawMode() {
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}
void enableRawMode() {
    tcgetattr(STDIN_FILENO, &orig_termios);
    atexit(disableRawMode);
    struct termios raw = orig_termios;
    raw.c_lflag &= ~(ECHO);
    raw.c_oflag &= ~(OPOST);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}
int main() {
  enableRawMode();
  char c;
  while (read(STDIN_FILENO, &c, 1) == 1 && c != 'q') {
    if (iscntrl(c)) {
      printf("%d\r\n", c);
    } else {
      printf("%d ('%c')\r\n", c, c);
    }
  }
  return 0;
}

/*#include<unistd.h>*/
/*#include<fcntl.h>*/
/*#include<stdio.h>*/

/*int main()*/
/*{*/

    /*printf("your current text is: haha\n");*/

    /*printf("haha\r");*/

    /*printf("hm");*/
    /*char* c[10];*/
    /*read(STDIN_FILENO, &c, 5);*/

/*}*/
