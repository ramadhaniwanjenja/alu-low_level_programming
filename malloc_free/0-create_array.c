#include "main.h"
#include <stdlib.h>
/**
 * create_array - creates an array of chars, and initializes
 * it with a specific char.
 * @c: char
 * @size: size of the array of chars
 *
 * Return: a pointer to the array, or NULL if it fails.
 */
char *create_array(unsigned int size, char c)
{

	char *array = NULL; /* Declare a pointer to store the array */
	unsigned int i;

	/*Check if size is zero */
	if (size == 0)
		return (NULL);

	/* Allocate memory for the array */
	array = malloc(size * sizeof(char));

	/* Check if allocation was successful */
	if (array == NULL)
		return (NULL);

	for (i = 0; i < size; i++)
	{
		array[i] = c;
	}

	return (array);
}
