#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/types.h>
#include "pipe_networking.h"

#define Q 0
#define UP  1
#define DOWN 2

int main() {
  int to_server, from_server;

  char buff[BUFFER_SIZE];

  from_server = client_handshake( &to_server );

  char linenum[BUFFER_SIZE];
  char rd[BUFFER_SIZE];
  int first_time = 1;

  while(1){ // us sending requests to the server
      if (first_time) {
        first_time = 0;

        printf("[client] enter line number to start editing:"); 
        fgets(linenum, BUFFER_SIZE, stdin);
        linenum[strlen(linenum) - 1] = '\0';
      }


    // send line numbers to server, telling which line we are currently editing
    write(to_server, linenum, BUFFER_SIZE);
    read(from_server, rd, BUFFER_SIZE);
    printf("[server]: %s\n", rd);
    // after we recieve the ok from the server,
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
    int f = fork();
    if (!f) { // child
        char *args[2];
        args[0] = "./curses";
        args[1] = linenum;

        execvp("./curses", args);
    }
    else { // parent
        int status;
        wait(&status);

        int child_arg = WEXITSTATUS(status);

        if (child_arg == Q) {
            return EXIT_SUCCESS;
        }

        if (child_arg == UP) {
           // linenum = 0
           // linenum > 0
        }
    }
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
