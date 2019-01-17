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

    int fd = open("h", O_RDONLY);
    printf("opened file\n");

    char input[500];
    read(fd, input, 500);
    printf("read file\n");

    struct node * head = read_file(input);
    printf("read file into linked list\n");

    print_list(head);

    printf("\n");

    printf("testing get_node\n");
    struct node * cur = get_node(1,head);
    strncpy(cur->cargo, "uwu (line 3)", 13);
    strcpy(cur->next->cargo, "uwu (line 3)");

    print_list(head);


    


}
