#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include "linked_list.h"


int main() {

    printf("testing turning a file into a linked list\n");

    int fd = open("haha.txt", O_RDONLY);
    printf("opened file\n");

    char input[500];
    read(fd, input, 500);
    printf("read file\n");

    struct node * head = read_file(input);
    printf("read file into linked list\n");

    print_list(head);

    printf("testing get_node\n");
    print_list(get_node(2,head));

    char* str = head->next->cargo;

    printf("Press a key ('q' to quit and save this line)...");

    /*int l = argv[1]; // this will be the line number*/
    int l = 2;

    // print tne entire file until the line that is currently being edited...
    

    printf("The file contains:\n%s\n", input);

    printf("some seetupt\n");
    // print the rest of the file ( and save a space for the line we are editng to be printed )
    int i = l;
    struct node * currnode = head;
    // while you have trversed less than l-1 args
    while (i) {
    //      mvprintw the cargo
    
        printf("%s\n", currnode->cargo);    
        currnode = currnode->next;
        i--;

    }
    // 
    printf("printed the first half...\n");
    /*mvprintw(5, 10, "%s", head->next->next->cargo);*/
    // go to the l+1st arg
    currnode = get_node(l+1,head);
    // mvprintw the cargo
    while (currnode->next) {
        printf("%s\n", currnode->cargo);
        currnode = currnode->next;
        i++;

    }
    /*mvprintw(6, 10, "%s", head->next->next->next->cargo);*/

    //print out the line we are currently editing.
    printf( "%s\n", str);
}
