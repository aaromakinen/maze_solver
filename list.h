#ifndef LIST_H
#define LIST_H
#include <stdbool.h>

struct coords {
        int row;
        int col;
};

struct node {
	int moves;
	struct coords point;
	struct node *next;
	struct node *prev;
};

struct node* init_list(struct coords point);
int add_to_list(struct coords point, struct node* cur);
bool list_empty(struct node* cur);
void dealloc_list();

#endif
