#include <stdio.h>
#include <stdlib.h>
#include "maze.h"
#include "maze_solver.h"

void usage() {
	printf("Usage: maze_solver [FILE]\n Solves a maze from given file\n");
}

int main(int argc, char * argv[]) {
	FILE *file = NULL;
	struct maze *maze;
	int max_tries[3] = { 20, 150, 200 };
	int i;

	if (argc != 2) {
		usage();
		return -1;
	}
	file = fopen(argv[1], "r");
	if (file == NULL) {
		printf("Error opening file! Exiting!\n");
		return -1;
	}
	maze = initialize_maze(file);
	if (maze == NULL)
		return -1;
	for (i = 0; i < 3; i++){
		if(solve_maze(maze, max_tries[i]))
			return -1;
	}
	free(maze);
	return 0;
}
