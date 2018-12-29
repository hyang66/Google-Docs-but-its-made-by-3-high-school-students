#define IS_LIST 0
#define IS_LINE 1

struct node { 
    void * cargo; 
    struct node *next; 
    int type; // will be 0 or 1
};

void print_list(struct node* p);
void print_node(struct node* p);
struct node * insert_front(struct node* p, void* i);
struct node * free_list(struct node* p);

struct node * read_file(char* input);

