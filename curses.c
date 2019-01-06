/*

  some struct code was borrowed from Paul Griffiths 1999
  Email: mail@paulgriffiths.net

*/


#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include "linked_list.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>                  /*  for sleep()  */
#include <curses.h>
#include <ctype.h>


/*  Struct to hold keycode/keyname information  */

struct keydesc {
    int  code;
    char name[20];
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

int main() {

    printf("testing turning a file into a linked list\n");

    int fd = open("haha.txt", O_RDONLY);
    printf("opened file\n");

    char input[500];
    read(fd, input, 500);
    printf("read file\n");

    struct node * head = read_file(input);
    printf("read file into linked list\n");


    WINDOW * mainwin;
    int ch;
    char* str = head->next->cargo;

    
    /*  Initialize ncurses  */

    if ( (mainwin = initscr()) == NULL ) {
        fprintf(stderr, "Error initialising ncurses.\n");
        exit(EXIT_FAILURE);
    }

    noecho();                  /*  Turn off key echoing                 */
    keypad(mainwin, TRUE);     /*  Enable the keypad for non-char keys  */


    /*  Display "Hello, world!" in the centre of the*/
	/*screen, call refresh() to show our changes, and*/
	/*sleep() for a few seconds to get the full screen effect  */

    /*mvaddstr(13, 33, "Hello, world!");*/
    /*refresh();*/
    /*sleep(3);*/

    /*  Print a prompt and refresh() the screen  */

    mvaddstr(1, 10, "Press a key ('q' to quit and save this line)...");
    mvprintw(2, 10, "The file contains: %s", input);
    mvprintw(10, 10, "Your text is: %s", str);
    refresh();

        /*  Loop until user presses 'q'  */

    while ( (ch = getch()) != 'q' ) {

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
        mvprintw(10, 10, "Your text is: %s", str);
        refresh();
    }

    // save this file...

    /*  Clean up after ourselves  */

    delwin(mainwin);
    endwin();
    refresh();



    return EXIT_SUCCESS;
}
