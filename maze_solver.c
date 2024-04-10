#include "maze_solver.h"
#include "maze.h"
#include "list.h"

/* Use BFS to find the optimal solution for the maze. Don't */
int solve_maze(struct maze *maze, int max_moves) {
	struct node *cur;
	bool visited[MAX_GRID_LENGTH][MAX_GRID_LENGTH] = { 0 };
	cur = init_list(maze->start);
	if (cur == NULL)
		return -1;
	while(!list_empty(cur)){
		int row = cur->point.row;
		int col = cur->point.col;
		char c;
		if (cur->moves > max_moves) {
			printf("The maze has no solution with %d moves!\n\n",
					max_moves);
			dealloc_list();
			return 0;
		}
		visited[row][col] = 1;
		if (row+1 <= maze->rows && !visited[row+1][col]) {
			if ((c = maze->grid[row+1][col]) == 'E') {
				break;
			}
			else if (c == ' '){
				struct coords new = { row+1, col };
				if(add_to_list(new, cur))
					return -1;
			}
		}
		if (row-1 >= 0 && !visited[row-1][col]) {
			if ((c = maze->grid[row-1][col]) == 'E') {
				break;
			}
			else if (c == ' '){
				struct coords new = { row-1, col };
				if(add_to_list(new, cur))
					return -1;
			}
		}
		if (col+1 <= maze->cols && !visited[row][col+1]) {
			if ((c = maze->grid[row][col+1]) == 'E') {
				break;
			}
			else if (c == ' '){
				struct coords new = { row, col+1 };
				if(add_to_list(new, cur))
					return -1;
			}
		}
		if (col-1 >= 0 && !visited[row][col-1]) {
			if ((c = maze->grid[row][col-1]) == 'E') {
				break;
			}
			else if (c == ' '){
				struct coords new = { row, col-1 };
				if(add_to_list(new, cur))
					return -1;
			}
		}
		cur = cur->next;
		if (cur == NULL){
		}
	}
	if (cur != NULL) {
		printf("Solution with max %d moves and with total of %d moves\n",
				max_moves, cur->moves);
		print_maze(maze, cur);
	}
	else {
		printf("The maze has no solution!\n");
	}
	dealloc_list();
	return 0;
}
