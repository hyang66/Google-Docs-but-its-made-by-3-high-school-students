#include "definitions.h"
struct node { 
    char cargo[CARGO_MAX]; 
    struct node *next; 
    int type; // will be 0 or 1
};

void print_list(struct node* p);
void print_node(struct node* p);
struct node * get_node(int line_no, struct node* head);
struct node * insert_front(struct node* p, char * i);
struct node * insert(struct node* head, char * i, int line);
struct node * free_list(struct node* p);

struct node * read_file(char* input);
int length(struct node* head);
