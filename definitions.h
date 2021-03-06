#ifndef DEFINITION
#define DEFINITION

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

//data entry
#define Q 0
#define UP  1
#define DOWN 2
#define ENTER 3

//linked list
#define IS_LIST 0
#define IS_LINE 1
#define CARGO_MAX 1000

// file stuff
#define WRITE 1
#define READ 0
#define FILE_SIZE 1000

// colors
#define RESET "\x1b[0m"
#define MAGENTA "\x1b[35m"
#define CYAN "\x1b[36m"

#endif
