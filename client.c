#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/types.h>
#include "pipe_networking.h"

int main() {
  int to_server, from_server;

  char buff[BUFFER_SIZE];

  from_server = client_handshake( &to_server );

  char wr[BUFFER_SIZE];
  char rd[BUFFER_SIZE];

  while(1){ // us sending requests to the server
    printf("[client] enter line number to start editing:"); 
    // send line numbers to server, telling which line we are currently editing
    fgets(wr, BUFFER_SIZE, stdin);
    wr[strlen(wr) - 1] = '\0';
    write(to_server, wr, BUFFER_SIZE);
    read(from_server, rd, BUFFER_SIZE);
    printf("[server]: %s\n", rd);
    // after we recieve the ok from the server,
    // 
    // fork off a child to edit line
    //      PARENT:
    //          wait for child
    //          child can return one of arrows or q
    //              q: 0
    //              up: 1
    //              down: 2
    //          change line number if needed
    //          if q: done
    //      CHILD:
    //          execvp curses and line number
    //
  }

    // server client handshake
    //
    //
    // display the text, wait for user to pick what line to edit
    //
    //
    //

    // checks for keybindings
    //
    // ~ for help menu
    // i for edit
    // o for new line
    return 0;
}
