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
    // make linked list

    /*int SOMEONE_EDITING = 0;*/
    int lines_being_edited[NUM_LINES];
    
    int i = NUM_LINES;
    while (i) {
        lines_being_edited[NUM_LINES - i] = 0;
        i --;
    }

    signal(SIGINT, sighandler);

    // server client handshake
    int to_client;
    int from_client;

    while(1) {
      printf("[server]: DOING CLIENT-HANDSHAKE\n");
      from_client = server_handshake( &to_client );
      char msg[BUFFER_SIZE];

      // find out if client is wants to start a new file or not:
      
      

      int f = fork();
      if(!f) {
        
        read (from_client, msg, BUFFER_SIZE);

        char filename[BUFFER_SIZE];
        strncpy(filename, msg, BUFFER_SIZE);
        int fd = open(filename, O_RDONLY);
        printf("[client]: filename [%s]\n", filename);
        // read the file we got into a linked list
        struct node * head = read_file(filename);

        while(read(from_client, msg, BUFFER_SIZE)) {
          //get filename from client
          //

          
          printf("line number:%s\n", msg);
          int line_number = atoi(msg);
          while (lines_being_edited[line_number]) {
              printf("waiting...\n");
          }
          
          lines_being_edited[line_number] = 1;
          write(to_client, "ok" , BUFFER_SIZE);
          
          
          int r = read(from_client,msg,BUFFER_SIZE);
          printf("%d", r);
          printf("[server]: msg received [%s]\n", msg);

          // saving the file
          int spot = 1;
          struct node * curnode = head;
          while (spot < line_number) {
              curnode = curnode->next;
              spot++;
          }
          strncpy(curnode->cargo, msg, BUFFER_SIZE);
          printf("[server]: writing to file\n");
          print_list(head);
          close(fd);
          fd = open(filename, O_WRONLY);
          int stdoutfd = dup(STDOUT_FILENO);
          dup2(fd, STDOUT_FILENO);
          print_list(head);
          dup2(stdoutfd, STDOUT_FILENO);
          printf("[server]: writing sucessful\n");
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
