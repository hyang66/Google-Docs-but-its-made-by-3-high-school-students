#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>                  /*  for sleep()  */
#include <curses.h>
#include <ctype.h>

#include "linked_list.h"
#include "definitions.h"
#include "pipe_networking.h"
#define KCYN  "\x1B[36m"
#define KMAG  "\x1B[35m"
#define KNRM  "\x1B[0m"


/*  Struct to hold keycode/keyname information  */

struct keydesc {
    int  code;
    char name[30];
};


/*  Returns a string describing a character passed to it  */

char * intprtkey(int ch) {

    /*  Define a selection of keys we will handle  */

    static struct keydesc keys[] = { { KEY_UP,        "Up arrow"        },
                     { KEY_DOWN,      "Down arrow"      },
                     { KEY_LEFT,      "Left arrow"      },
                     { KEY_RIGHT,     "Right arrow"     },
                     { KEY_HOME,      "Home"            },
                     { KEY_END,       "End"             },
                     { KEY_BACKSPACE, "Backspace"       },
                     { KEY_IC,        "Insert"          },
                     { KEY_DC,        "Delete"          },
                     { KEY_NPAGE,     "Page down"       },
                     { KEY_PPAGE,     "Page up"         },
                     { KEY_F(1),      "Function key 1"  },
                     { KEY_F(2),      "Function key 2"  },
                     { KEY_F(3),      "Function key 3"  },
                     { KEY_F(4),      "Function key 4"  },
                     { KEY_F(5),      "Function key 5"  },
                     { KEY_F(6),      "Function key 6"  },
                     { KEY_F(7),      "Function key 7"  },
                     { KEY_F(8),      "Function key 8"  },
                     { KEY_F(9),      "Function key 9"  },
                     { KEY_F(10),     "Function key 10" },
                     { KEY_F(11),     "Function key 11" },
                     { KEY_F(12),     "Function key 12" },
                     { -1,            "<unsupported>"   }
    };
    static char keych[2] = {0};

    if ( isprint(ch) && !(ch & KEY_CODE_YES)) {

    /*  If a printable character  */

    keych[0] = ch;
    return keych;
    }
    else {

    /*  Non-printable, so loop through our array of structs  */

    int n = 0;

    do {
        if ( keys[n].code == ch )
        return keys[n].name;
        n++;
    } while ( keys[n].code != -1 );

    return keys[n].name;
    }

    return NULL;        /*  We shouldn't get here  */
}

void draw_text( struct node * head, int l, char* str) {

    clear();                /* clear the screen */
    /*  Print a prompt and refresh() the screen  */

    mvaddstr(1, 10, "Press a key ('q' to quit and save this line)...");

    /*int l = argv[1]; // this will be the line number*/

    // print tne entire file until the line that is currently being edited...
    

    mvprintw(2, 10, "The file contains:");

    /*printf("some seetupt\n");*/
    // print the rest of the file ( and save a space for the line we are editng to be printed )
    int i = l - 1;
    struct node * currnode = head;
    // while you have trversed less than l-1 args
    while (i) {
    //      mvprintw the cargo
    
        mvprintw(l - i + 2, 2, "%d %s", l-i, currnode->cargo);    
        currnode = currnode->next;
        i--;

    }
    
    // 
    /*printf("printed the first half...\n");*/
    /*mvprintw(5, 10, "%s", head->next->next->cargo);*/
    // go to the l+1st arg
    currnode = get_node(l,head);
    // mvprintw the cargo
    while (currnode->next) {
        mvprintw(l+3 + i, 2, "%d %s", l+i+1, currnode->cargo);
        currnode = currnode->next;
        i++;

    }

    /*mvprintw(6, 10, "%s", head->next->next->next->cargo);*/

    //print out the line we are currently editing.
    mvprintw(l + 2, 2, "%d %s", l, str);
    refresh();

}

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


    printf(RESET "[client] enter line number to start editing: ");
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

        // start running curses!!
        /*printf("testing turning a file into a linked list\n");*/
        int line_number = atoi(linenum);

        int fd = open("haha.txt", O_RDONLY);
        /*printf("opened file\n");*/

        char input[500];
        int n = 499;
        while (n + 1) {
            input[n] = 0;
            n --;
        }
        read(fd, input, 500);
        /*printf("read file\n");*/

        struct node * head = read_file(input);
        /*printf("read file into linked list\n");*/


        WINDOW * mainwin;
        int ch;

        
        /*  Initialize ncurses  */

        if ( (mainwin = initscr()) == NULL ) {
            fprintf(stderr, "Error initialising ncurses.\n");
            exit(EXIT_FAILURE);
        }

        noecho();                  /*  Turn off key echoing                 */
        keypad(mainwin, TRUE);     /*  Enable the keypad for non-char keys  */

        char str[CARGO_MAX];
        char * s = get_node(line_number-1, head)->cargo;
        int i = 0;
        while (s&& i < CARGO_MAX) {
            str[i] = *s;
            s++;
            i ++;
        } 


        draw_text(head, line_number, str);

            /*  Loop until user presses 'q'  */

        while ( (ch = getch()) != 'q') {

            /*  Delete the old response line, and print a new one  */

            deleteln();
            char newc = intprtkey(ch)[0];
            int i = 0;
            while (str[i]) {
                i ++;
            }
            if (newc == '<') {
                str[i-1] = 0;

            } else {
                if (i < 19) {
                    str[i] = newc;
                    str[i + 1] = 0;
                }
            }
            /*  Print a prompt and refresh() the screen  */
            draw_text(head, line_number, str);

        }

        


        
        /*  Clean up after ourselves  */

        delwin(mainwin);
        endwin();
        refresh();

        // send this info to the client...
        
        /*int to_server, from_server;*/
        /*from_server = client_handshake( &to_server );*/

        struct node * edited_line = get_node(line_number-1, head);
        edited_line->cargo = str;
        printf("[curses]: edited_line: %s\n", edited_line->cargo);
        write(fds[WRITE], str, BUFFER_SIZE);

        /*write(to_server, str, BUFFER_SIZE);*/
        // print_list(head);
        // printf("test\n");
        // 

        /*print_list(head);*/
        close(fd);

        exit(0);


        // child sends line to server
        // server makes edit
    }
    else { // parent
        printf("[client]: in parent\n");

        // setup pipe between parent and child.
        close(fds[WRITE]);
        char msg[BUFFER_SIZE];
        int i = BUFFER_SIZE;
        while (i) {
            msg[BUFFER_SIZE - i] = 0;
            i --;
        }
        read(fds[READ], msg, BUFFER_SIZE);

        /*printf("%s\n", msg);*/
        
        

        int status;
        wait(&status);

        int child_arg = WEXITSTATUS(status);

        if (child_arg == Q) {
            // exit out of the loop 
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
    
    // client writes line to server
        write(to_server, msg, BUFFER_SIZE);
        printf("[client]: wrote to server\n");
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
