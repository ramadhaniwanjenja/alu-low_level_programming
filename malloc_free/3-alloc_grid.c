#include "main.h"
#include <stdlib.h>
/**
 * alloc_grid -  returns a pointer to a 2 dimensional array of integers.
 * @width: width of array
 * @height: height of array
 * Return: a pointer to a newly allocated space in memory.
 */
int **alloc_grid(int width, int height)
{
	int **array = NULL;
	int r = 0;
	int c = 0;

	if (width <= 0 || height <= 0)
		return (NULL);

	array = malloc(height * sizeof(int *));

	if (array == NULL)
		return (NULL);

	for (r = 0; r < height; r++)
	{
		array[r] = malloc(width * sizeof(int));
		if (array[r] == NULL)
		{
			for (r = 0; r < height; r++)
				free(array[r]);
			free(array);
			return (NULL);
		}

		for (c = 0; c < width; c++)
			array[r][c] = 0;
	}
	return (array);
}
