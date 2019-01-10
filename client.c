#include "pipe_networking.h"
#include "definitions.h"

int main() {
  int to_server, from_server;

  /*char buff[BUFFER_SIZE];*/

  from_server = client_handshake( &to_server );

  char linenum[BUFFER_SIZE];
  /*char filename[BUFFER_SIZE];*/
  char rd[BUFFER_SIZE];
  int first_time = 1;

  while(1) { // us sending requests to the server
      if (first_time) {
        first_time = 0;
        DIR *d;
        struct dirent *dir;
        d = opendir(".");
        if (d)
        {
          printf(CYAN "Here are the directory contents:\n");
          while ((dir = readdir(d)) != NULL)
          {
            printf("%s\n", dir->d_name);
          }
          closedir(d);
        }

      }

    /*char resp[4];*/
    /*printf(RESET "[client] do you want to edit alongside someone who is already editng a file? (y/n)\n");*/
    /*fgets(resp, 4, stdin);*/
    /*resp[strlen(resp) - 1] = '\0';*/
    
    /*if (!strcmp(resp, "n")){*/

        /*printf(RESET "[client] enter filename to start editing:\n");*/
        /*fgets(filename, BUFFER_SIZE, stdin);*/
        /*filename[strlen(filename) - 1] = '\0';*/
    /*}*/


    printf(RESET "[client] enter line number to start editing:\n");
    fgets(linenum, BUFFER_SIZE, stdin);
    linenum[strlen(linenum) - 1] = '\0';


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
    int fds[2];
    pipe(fds);
    int f = fork();
    if (!f) { // child
        close(fds[READ]);
        char *args[2];
        args[0] = "./curses";
        args[1] = linenum;

        printf("[child of clinet: ready to execvp\n]");

        execvp("./curses", args);
    }
    else { // parent
        close(fds[WRITE]);
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

        if (child_arg == ENTER) {
            // tell the server to add new line at that index
            // restart curses with that new line
            //
            // CURRENTLY can only enter at end of line
            // everything else will be lost

        }
    // write edited line with parent
    // client writes line to server
    // server makes the official edit
        // versions don't get out of sync
    }

  } // end while 1

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
