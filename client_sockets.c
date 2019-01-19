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
#include <sys/wait.h>

#include "linked_list.h"
#include "definitions.h"
#include "pipe_networking.h"
#include "networking.h" //SOCKETS

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
                     { KEY_ENTER,     "ENTER"           },
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

void draw_text( struct node * head, int l, char* str, char* filename) {

    clear();                /* clear the screen */
    /*  Print a prompt and refresh() the screen  */

    mvprintw(1, 10, "|| %s || Press a key ('Q' to quit and save this line)...", filename);

    /*int l = argv[1]; // this will be the line number*/

    // print tne entire file until the line that is currently being edited...



    /*printf("some seetupt\n");*/
    // print the rest of the file ( and save a space for the line we are editng to be printed )
    int i = l - 1;
    struct node * currnode = head;
    // while you have trversed less than l-1 args
    while (i) {
    //      mvprintw the cargo

        if (l-i < 10){
            mvprintw(l - i + 2, 2, " %d || %s", l-i, currnode->cargo);
        } else {
            mvprintw(l - i + 2, 2, "%d || %s", l-i, currnode->cargo);
        }
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
        if (l+i+1 < 10){
            mvprintw(l+3 + i, 2, " %d || %s", l+i+1, currnode->cargo);
        } else {
            mvprintw(l+3 + i, 2, "%d || %s", l+i+1, currnode->cargo);
        }
        currnode = currnode->next;
        i++;

    }

    /*mvprintw(6, 10, "%s", head->next->next->next->cargo);*/

    //print out the line we are currently editing.
    if (l < 10) {
        mvprintw(l + 2, 1, "* %d || %s", l, str);
    } else {
        mvprintw(l + 2, 1, "*%d || %s", l, str);
    }
    refresh();

}

int main(int argc, char ** argv) {
  /*int to_server, from_server;*/

  /*char buff[BUFFER_SIZE];*/

  /*from_server = client_handshake( &to_server );*/



  char resp[4];
  printf(RESET "[client] do you want to edit alongside someone who is already editng a file? (y/n)\n");
  fgets(resp, 4, stdin);
  resp[strlen(resp) - 1] = '\0';


  int server_socket; // SOCKET CODE

  if (!strncmp(resp, "y", 1)) {

    char ip[BUFFER_SIZE];

    printf(RESET "[client]: enter IP address:\n");
    fgets(ip, BUFFER_SIZE, stdin);
    ip[strlen(ip) - 1] = '\0';

    server_socket = client_setup( ip );
  }
  else {
    server_socket = client_setup( TEST_IP );
  }


  char linenum[BUFFER_SIZE];
  char filename[BUFFER_SIZE];
  /*char rd[BUFFER_SIZE];*/
  int first_time = 1;
  int line_number;
  int try_again = 0;

  while(1) { // us sending requests to the server
      if (first_time) {
        first_time = 0;
        // DIR *d;
        // struct dirent *dir;
        // d = opendir(".");
        if (!try_again) {
            char input[BUFFER_SIZE];
            /*printf("before read [server]: %s\n", input);*/
            read(server_socket, input, BUFFER_SIZE);
            /*printf("after read [server]: %s\n", input);*/


        printf(RESET "[client] enter filename to start editing:\n");
        fgets(filename, BUFFER_SIZE, stdin);
        filename[strlen(filename) - 1] = '\0';
        write(server_socket, filename, BUFFER_SIZE); // tell server what file we are editing
        printf("[client]: wrote the filename  [%s]\n", filename);
            /*} */
            /*else if (!strcmp(resp, "y")) {*/

            /*}*/
            /*else {*/
                /*write(server_socket, "huh", BUFFER_SIZE);*/
            /*}*/
        }

        printf(RESET "[client] enter line number to start editing: ");
        fgets(linenum, BUFFER_SIZE, stdin);
        linenum[strlen(linenum) - 1] = '\0';
        line_number = atoi(linenum);

        /*printf("line number: %d\n", line_number);*/

        int fd = open(filename, O_RDONLY);
        /*printf("opened file\n");*/

        /*printf("read file\n");*/

        char input[FILE_SIZE];
        int n = FILE_SIZE;
        while (n + 1) {
            input[n - 1] = 0;
            n --;
        }
        /*printf("line number: %d\n", line_number);*/
        read(fd, input, FILE_SIZE);
        struct node * head = read_file(input);
        int totlength = length(head);
        if (totlength <= line_number) {
            printf("[client] line number does not exist, please enter a new line less than %d \n", totlength);
            first_time = 1;
            try_again = 1;
        }
        else {
            try_again = 0;
            printf("[cleint]: continuing...\n");
        }
      }


    if (!try_again) {
    /*printf("\n---\n[cleint]: continuing, no need to try again...\n------\n");*/

    // still in the whiile loop

    // send line numbers to server, telling which line we are currently editing
    sprintf(linenum, "%d", line_number);
    /*printf("tellinf server line number\n");*/
    write(server_socket, linenum, BUFFER_SIZE);
    /*printf("done tellinf server line number\n");*/
    /*printf("waitng fro the ok\n");*/
    char input[BUFFER_SIZE];
    read(server_socket, input, BUFFER_SIZE);
    printf("[server]: %s\n", input);
    /*sleep(1);*/

    int fds[2];
    pipe(fds);
    int f = fork();
    if (!f) { // child
        close(fds[READ]);

        // start running curses!!
        /*printf("testing turning a file into a linked list\n");*/

        /*int fd = open(filename, O_RDONLY);*/
        /*printf("opened file\n");*/

        /*printf("read file\n");*/

        // char input[FILE_SIZE];
        // int n = FILE_SIZE;
        // while (n + 1) {
        //     input[n - 1] = 0;
        //     n --;
        // }
        // read(fd, input, FILE_SIZE);
        struct node * head = read_file(input);
        int totlength = length(head);
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


        draw_text(head, line_number, str, filename);

            /*  Loop until user presses 'q'  */

        int fd2 = open("log.txt", O_WRONLY);
        write(fd2, "made it to draw_text.\n", BUFFER_SIZE);
        while ( 1) {

            ch = getch();
            if (ch == 'Q' || ch == 0x103 || ch == 0x102){
                // if user presses quit, up or down
                break;
            }

            // HANNA LOOK AT THIS
            deleteln();
            char newc = intprtkey(ch)[0];
            int i = 0;
            while (str[i]) {
                i ++;
            }
            if (ch == 0x7f || ch == 0x107) {
                str[i] = 0;
                str[i-1] = 0;

            }  else if ( ch == 0xa ) {
                    str[i] = '\n';
                    str[i + 1] = ' ';
                    str[i + 2] = 0;
                    break;

            }  else {
                if (i < CARGO_MAX - 1) {
                    str[i] = newc;
                    str[i + 1] = 0;
                }
            }
            /*  Print a prompt and refresh() the screen  */
            draw_text(head, line_number, str, filename);

        }





        /*  Clean up after ourselves  */

        delwin(mainwin);
        endwin();
        refresh();

        // send this info to the client...

        /*int to_server, from_server;*/
        /*from_server = client_handshake( &to_server );*/

        struct node * edited_line = get_node(line_number-1, head);
        strncpy(edited_line->cargo, str, CARGO_MAX);
        /*printf("[curses]: edited_line: %s\n", edited_line->cargo);*/
        char msg[CARGO_MAX];
        strncpy(msg, edited_line->cargo, CARGO_MAX);
        char ln[10];
        sprintf(ln, "\n%d", totlength);
        strncat(msg, ln, CARGO_MAX);
        /*printf("made it to strcat: %s\n", msg);*/
        write(fds[WRITE], msg, BUFFER_SIZE);
        /*printf("write sucessful\n");*/


        /*print_list(head);*/
        // close(fd);

        if (ch == 'Q') {
                exit(Q);
        }
        if (ch == 0x103) {
                exit(UP);
        }
        if (ch == 0x102) {
                exit(DOWN);
        }
        if (ch == 0xa) {
                exit(ENTER);
        }


        // child sends line to server
        // server makes edit
    }
    else { // parent
        /*printf("[client]: in parent\n");*/

        // setup pipe between parent and child.
        close(fds[WRITE]);
        char msg[CARGO_MAX];
		int i = CARGO_MAX;
		while (i) {
			msg[CARGO_MAX - i] = 0;
			i --;
		}
		/*printf("parents: about to read\n");*/
        int r = read(fds[READ], msg, BUFFER_SIZE);
        if (r == -1 ) {
            printf("read unsucessfule, line 423\n");
            exit(0);
        }
		/*printf("%s : %d\n", msg, r);*/


		int len = strlen(msg);
        int n = 0;
        //ENTER IS BAD BECAUSE OF \/
        while (n < len) {
            if (msg[n] == '\n') {
                break;
            }
            n ++;
        }

		/*printf("strlen %d\n", len);*/
        msg[n] = 0;
        n ++;
        char ln[20];
        int m = 0;
		/*printf(" beforw the while\n");*/
        while (n<len) {
            ln[m] = msg[n];
            n ++;
            m ++;
        }
		/*printf("afterthe while\n");*/
        ln[m] = 0;
        /*printf("b4set totlength\n");*/
        int totlength = atoi(ln);
        /*printf("set totlength\n");*/

        /*printf( "message: %s || total length: %d\n", msg, totlength );*/




        int status;
        wait(&status);

        /*printf("hggfgfg\n");*/
        int child_arg = WEXITSTATUS(status);

        /*printf("[client]: will write [%s] to server\n", msg);*/
        if (child_arg == Q) {
            // exit out of the loop
            printf("[client]: USer presssed quit.\n");
            printf("[client]: Exiting... File saved.\n");
            write(server_socket, msg, BUFFER_SIZE);
            printf("[client]: wrote [%s] to server\n", msg);
            exit(0);
        }

        else if (child_arg == UP) {
           // linenum = 0
            if (line_number <= 1) {
                printf("[client]: At line 1, err...\n");
                line_number = 1;
            }
            else {
                printf("[client]: Going back one line...\n");
                line_number--;
            }
            printf("[client]: USer presssed up.\n, going to line number %d\n", line_number);
           // linenum > 0

        } // end if child arg up


        else if (child_arg == DOWN) {
           // if at the end
            if (line_number >= totlength - 1) {
                printf("[client]: At end of text, err...\n");
                line_number = totlength - 1;
            }
            else {
                printf("[client]: Going back one line...\n");
                line_number++;
            }
            printf("[client]: USer presssed down.\n, going to line number %d\n", line_number);
           // linenum > 0

        } // end if child arg up
        else if (child_arg == ENTER) {
            // tell the server to add new line at that index
            // restart curses with that new line

            // CURRENTLY can only enter at end of line
            // everything else will be lost
            char ENTERstr[CARGO_MAX] = "ENTER|";
            strncat(ENTERstr,msg,CARGO_MAX);
            strncpy(msg,ENTERstr,CARGO_MAX);
            line_number++;
            /*printf("entered, going down a line \n");*/
        }

    // client writes line to server
    // writing the edited line
        write(server_socket, msg, BUFFER_SIZE);
        printf("[client]: wrote []%s[] to server\n", msg);
    // server makes the official edit
        // versions don't get out of sync
    } // end else
    try_again = 0;
}// end if

  } // en88888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888d while 1

    return 0;
}
