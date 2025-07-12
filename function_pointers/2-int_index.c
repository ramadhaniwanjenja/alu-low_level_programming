#include "function_pointers.h"
/**
 * int_index - executes a function given as a parameter on each
 * element of an array.
 * @array: parameter
 * @size: size of array
 * @cmp:a pointer to the function you need to use
 * Return:  index of the first element after cmp funnction runs
 */
int int_index(int *array, int size, int (*cmp)(int))
{
	int i;

	if (array != NULL && cmp != NULL)
	{
		for (i = 0; i < size; i++)
		{
			if (cmp(*(array + i)))
				return (i);
		}
	}
	return (-1);
}
