#include <stdio.h>
#include <stdlib.h>
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
            printf("%s --> ", p->cargo);
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

struct node * free_list(struct node* p) {
    if (p) {
        free_list(p->next);
        free(p);
    }
    return NULL;
}

struct node * read_file(char* input) {
    // malloc head

    // while we arent at the end of the input string
    //      strsep, take until the newline 
    //      put this in cargo
    //      set poitner of node to next node
    //      malloc next node
        
    // return head  
}
