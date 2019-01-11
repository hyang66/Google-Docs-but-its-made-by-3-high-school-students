#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/types.h>
#include "linked_list.h"
#include "pipe_networking.h"

#define NUM_LINES 78

static void sighandler(int signo) {
  if (signo == SIGINT) {
      remove("wkp");
      exit(0);
  }
}

int main() {
    /*int SOMEONE_EDITING = 0;*/
    int lines_being_edited[NUM_LINES];
    
    int i = NUM_LINES;
    while (i) {
        lines_being_edited[NUM_LINES - i] = 0;
        i --;
    }

    signal(SIGINT, sighandler);

    int to_client;
    int from_client;

    while(1) {

      from_client = server_handshake( &to_client );
      char msg[BUFFER_SIZE];

      // find out if client is wants to start a new file or not:
      
      

      int f = fork();
      if(!f) {
        while(read(from_client, msg, BUFFER_SIZE)) {
          //get filename from client
          printf("[client] %s\n", msg);
          int line_number = atoi(msg);
          if (!lines_being_edited[line_number]) {
            strcat(msg, "ok");
            write(to_client, msg, BUFFER_SIZE);
          }
        }
      }

      }
      return 0;
    }

    // get filename thru aguments
    // open file, and read it into a linked list

    // swpan off a client for the first user

    // in a while loop:
    // wait for server client handsake
    //
    // send linked list to client for client to display
    // wait for client to send back what line they are working on, and how they edited it
    // edit the linked list
    // send new linked list to all clients
    //
    //
    //
    // write edited line with parent
    // client writes line to server
    // server makes the official edit
        // versions don't get out of sync
    //
