#include <stdlib.h>
#include <stdbool.h>
#include "list.h"
#include "maze.h"

struct node *last_node = NULL;
struct node *head = NULL;

/* Initialize the linked list with starting coordinates of the maze. */
struct node* init_list(struct coords point) {
	struct node *new_node = (struct node*) malloc(sizeof(struct node));
	if (new_node == NULL) {
                printf("Allocation has failed!\n");
                return NULL;
        }
	last_node = head = new_node;
	new_node->prev = NULL;
	new_node->next = NULL;
	new_node->point = point;
	new_node->moves = 0;
	return new_node;
}
/* Add an item to the list. */
int add_to_list(struct coords point, struct node *cur) {
	struct node *new_node = (struct node*) malloc(sizeof(struct node));

	if (new_node == NULL) {
		printf("Allocation has failed!\n");
		return -1;
	}
	last_node->next = new_node;
	last_node = new_node;
	/* We use the previous node pointer as reference to the last step that
	 * took us to this node. It is not necessarily the previous node in the
	 * linked list
	 */
	new_node->prev = cur;
	new_node->next = NULL;
	new_node->point = point;
	new_node->moves = cur->moves + 1;
	return 0;
}

bool list_empty(struct node *cur) {

	return (cur == NULL);
}
/* Deallocate the memory for the linked list. */
void dealloc_list() {
	struct node *temp;
	if (head == NULL)
		return;
	do {
		temp = head->next;
		free(head);
		head = temp;
	} while (head != NULL);
}
