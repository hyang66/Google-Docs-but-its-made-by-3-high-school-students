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

}
