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

void print_list(struct node* p){
    print_node(p);
    if (p) {
        print_list(p->next);
    }
}


void print_node(struct node* p) {
    if (p) {
        if (p->type == IS_LINE) {
            printf("%s\n", p->cargo);
        }
    } else {
        printf("null\n");
    }
}

struct node * insert_front(struct node* p, void * i) {
    struct node* head = malloc(sizeof(struct node));
    head->cargo = i;
    head->next = p;
    return head;
}

struct node * get_node(int line_no, struct node* head) {
  struct node* current = head;
  int count = 0;
  while (current != NULL)
  {
      if (count == line_no)
          return(current);
      count++;
      current = current->next;
  }
  return(0);
}

struct node * free_list(struct node* p) {
    if (p) {
        free_list(p->next);
        free(p);
    }
    return NULL;
}

struct node * read_file(char* input) {
    // malloc head
    struct node * head = malloc(sizeof(struct node));
    /*printf("made head\n");*/

	char *s = strsep(&input, "\n");
    struct node * currnode = head;
	while (strcmp(s,"")) {
		/*ans[i] = s;	*/
        currnode->cargo = s;
        currnode->next = malloc(sizeof(struct node));
        currnode->type = IS_LINE;
        /*printf("made another node\n");*/
		/*printf("%d : %s", i, ans[i]);*/
		s = strsep(&input, "\n");
        if (s) {
            printf("s: [%s]\n", s);
        }
        currnode = currnode->next;
	}

    currnode->next = NULL;


    // while we arent at the end of the input string
    //      strsep, take until the newline
    //      put this in cargo
    //      set poitner of node to next node
    //      malloc next node

    return head;
}
