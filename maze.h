#ifndef MAZE_H
#define MAZE_H
#include <stdio.h>
#include "list.h"

#define MAX_GRID_LENGTH 40

struct maze {
	char grid[MAX_GRID_LENGTH][MAX_GRID_LENGTH];
	int rows;
	int cols;
	struct coords start;
};

struct maze* initialize_maze(FILE *fp);
void print_maze(struct maze*, struct node* cur);

#endif
