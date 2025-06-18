#include "main.h"
#include <stdlib.h>
/**
 * free_grid -  that frees a 2 dimensional grid previously
 * created by your alloc_grid function.
 * @grid: array to free
 * @height: height of array
 * Return: a pointer to a newly allocated space in memory.
 */
void free_grid(int **grid, int height)
{
	int row;

	if (grid == NULL)
		free(grid);

	for (row = 0; row < height; row++)
		free(grid[row]);

	free(grid);
}
