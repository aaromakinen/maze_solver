#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "maze.h"


struct maze* initialize_maze(FILE *fp) {
        char *line = NULL;
        struct maze* new_maze = (struct maze*) malloc(sizeof(struct maze));
        size_t len;
	ssize_t size;
	int i;
        if (!new_maze) {
                printf("Failed to allocate maze!\n");
                return NULL;
        }
	new_maze->start.row = -1;
	new_maze->start.col = -1;
        if ((size = getline(&line, &len, fp)) == -1) {
                printf("Failed to read input file!\n");
                return NULL;
        }
        /* First line of the input file determines the allowed width of the
         * maze. Exclude new line character.
         */
        new_maze->cols = size - 1;
        new_maze->rows = -1;
        do {
                new_maze->rows++;
                if (new_maze->cols != size - 1) {
                        printf("The width of the maze has to be constant\n");
                        return NULL;
                }
                for (i = 0; i < new_maze->cols; i++) {
                        if (line[i] == '^') {
				if (new_maze->start.col != -1) {
					printf("Multiple entry points not supported. Sorry!\n");
					return NULL;
				}
                                new_maze->start.row = new_maze->rows;
                                new_maze->start.col = i;
                        }
                        else if (line[i] != ' ' && line[i] != '#' && line[i] != 'E') {
				printf("Invalid character in row %d column %d\n",
						new_maze->rows, new_maze->cols);
				return NULL;
			}
			new_maze->grid[new_maze->rows][i] = line[i];
                }
	} while ((size = getline(&line, &len, fp)) != -1 && new_maze->rows < MAX_GRID_LENGTH);
        if (new_maze->rows < 3) {
                printf("Less than 3 rows in the input file is not allowed.\n");
                return NULL;
        }
	if (new_maze->start.col == -1) {
		printf("No starting point in maze!\n");
		return NULL;
	}
	return new_maze;
}

void print_maze(struct maze* maze, struct node* cur) {
	int i, j;
	char temp[MAX_GRID_LENGTH][MAX_GRID_LENGTH];
	memcpy(temp, maze->grid, MAX_GRID_LENGTH*MAX_GRID_LENGTH* sizeof(char));
	while (cur != NULL) {
		temp[cur->point.row][cur->point.col] = 'o';
		cur = cur->prev;
	}
	for (i = 0; i <= maze->rows; i++) {
		for (j = 0; j <= maze->cols; j++) {
			printf("%c",temp[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}
