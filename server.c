#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/types.h>
#include "linked_list.h"
#include "pipe_networking.h"

static void sighandler(int signo) {
  if (signo == SIGINT) {
      remove("wkp");
      exit(0);
  }
}

int main() {
  signal(SIGINT, sighandler);

    int to_client;
    int from_client;

    while(1) {

      from_client = server_handshake( &to_client );
      char msg[BUFFER_SIZE];

      while(read(from_client, msg, BUFFER_SIZE)) {
        //get filename from client
        printf("[client] %s\n", msg);
        DIR *d;
        struct dirent *dir;
        d = opendir(".");
        if (d)
        {
          while ((dir = readdir(d)) != NULL)
          {
            if (strcmp(msg, dir->d_name) == 0) {
              write(to_client, "What line number do you want to edit?", BUFFER_SIZE);
              //TO DO:
              //Execvp file writing
            }
            printf("%s\n", dir->d_name);
          }
          closedir(d);
        }
      }
        strcat(msg, " -- changes read into file");
        write(to_client, msg, BUFFER_SIZE);
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
