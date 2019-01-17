#include "linked_list.h"
#include "definitions.h"

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
        /*printf("null\n");*/
    }
}

struct node * insert_front(struct node* p, char * i) {
    struct node* head = malloc(sizeof(struct node));
    strncpy(head->cargo, i, CARGO_MAX);
    head->next = p;
    return head;
}

struct node * insert(struct node* head, char * i, int line) {
    struct node * curnode = head;
    if (line == 0) {
        insert_front(head, i);
    }
    curnode = get_node (line - 1, head);
    struct node * insertnode = insert_front(curnode->next, i);

    curnode->next = insertnode;
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
	while (s) {
        if (!currnode) {
            break;
        }
		/*ans[i] = s;	*/
        char* str = calloc(sizeof(char), CARGO_MAX);
        strncpy(str, s, CARGO_MAX);
        // printf("[%s]\n", s);
        strncpy(currnode->cargo, str, CARGO_MAX);
        // printf("expect to see the line: []%s[]\n", currnode->cargo);
        // printf("expect to see nothing: %c\n", str[75]);
        currnode->next = malloc(sizeof(struct node));
        currnode->type = IS_LINE;
        /*printf("made another node\n");*/
		/*printf("%d : %s", i, ans[i]);*/
		s = strsep(&input, "\n");
        /*if (s) {*/
            /*printf("s: [%s]\n", s);*/
        /*}*/
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

int length(struct node* head) {
    struct node* curnode = head;
    int length = 0;

    while (curnode) {
        length++;
        curnode = curnode->next;
    }

    return length;
}
