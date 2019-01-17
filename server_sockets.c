#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/types.h>

#include "linked_list.h"
#include "pipe_networking.h"
#include "networking.h" // SOCKET CODE

#define NUM_LINES 45

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

    /*// server client handshake*/
    /*int to_client;*/
    /*int from_client;*/

    // SOCKET CODE
    int listen_socket;
    listen_socket = server_setup();

    while(1) {
      /*printf("[server]: DOING CLIENT-HANDSHAKE\n");*/
      /*from_client = server_handshake( &to_client );*/
      char msg[BUFFER_SIZE];

      printf("[server]: DOING SOCKET SETUP\n");
      int client_socket = server_connect(listen_socket);
      // find out if client is wants to start a new file or not:



      int f = fork();
      if(!f) {

        read (client_socket, msg, BUFFER_SIZE);

        char filename[BUFFER_SIZE];
        strncpy(filename, msg, BUFFER_SIZE);
        int fd = open(filename, O_RDONLY | O_CREAT, 0664);
        printf("[client to us]: filename [%s]\n", filename);
        // read the file we got into a linked list
        


        while(read(client_socket, msg, BUFFER_SIZE)) {
              //
             printf("got the line number!!\n");

              char input[FILE_SIZE];
              int n = FILE_SIZE -1;
              while (n + 1) {
                  input[n] = 0;
                  n --;
              }
              fd = open(filename, O_RDONLY);
              int a = read(fd, input, FILE_SIZE);
              printf ("read value: %d\n", a);
              printf("file before we turn it into ll: %s\n",input );
              
              struct node * head = read_file(input);
              printf("[server]: contents of the file\n");
              print_list(head);

              printf("line number:%s\n", msg);
              
              int line_number = atoi(msg);
              /*while (lines_being_edited[line_number]) {*/
                  /*printf("waiting...\n");*/
              /*}*/

              lines_being_edited[line_number] = 1;
              write(client_socket, "ok" , BUFFER_SIZE);


              /* int r = */read(client_socket,msg,BUFFER_SIZE);
              /*printf("read value: %d\n", r);*/
              printf("[server]: msg received [%s]\n", msg);

              // parse to see if it is enter
              if (!strncmp(msg, "ENTER|", 6)) {
                   printf("[server]: now entering in a new line");
                   // add node to linked list
                   insert(head, " ", line_number);
              } else{
                  printf("there was no enter\n");
              }

              // saving the file
              printf("[server]: contents of the file\n");
              print_list(head);
              struct node * curnode = get_node(line_number-1, head);
              printf("got the node: %s\n", curnode->cargo);

              /*printf("[server]: contents of the file\n");*/
              /*print_list(head);*/
              strncpy(curnode->cargo, msg , strlen(msg));
              printf("so heres the strcpy\n");
              printf("[server]: writing to file\n");
              print_list(head); // there's a problem
              printf("[server]: end of list\n");
              close(fd);
              fd = open(filename, O_WRONLY);
              int stdoutfd = dup(STDOUT_FILENO);
              dup2(fd, STDOUT_FILENO);
              print_list(head);
              dup2(stdoutfd, STDOUT_FILENO);
              printf("------ \n[server]: writing sucessful\n -------\n");
              close(fd);

              printf("[server]: waiting for client to send line number\n");

              free_list(head);

        } // end while read
        exit(0); // end if not f 
       
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
