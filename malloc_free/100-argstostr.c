#include "main.h"
#include <stdlib.h>
/**
 * argstostr -  that concatenates all the arguments of your program.
 * @ac: argument count
 * @av: array of pointers
 * Return: a pointer to a newly allocated space in memory.
 */
char *argstostr(int ac, char **av)
{
	char *concat = NULL;
	int len = 0, i, j, k = 0;

	/* Check if ac is zero or av is NULL */
	if (ac == 0 || av == NULL)
		return (NULL);

	/* Calculate the length to malloc */
	for (i = 0; i < ac; i++)
	{
		/* this will loop to get len of particular arg*/
		for (j = 0; av[i][j] != '\0'; j++)
		{
			len++;
		}
		len++; /* For the newline character after each arg */
	}
	len++; /* For the null terminator */

	/* Allocate memory for the concatenated concating */
	concat = malloc(len * sizeof(char));
	if (concat == NULL)
	{
		free(concat);
		return (NULL);
	}

	/* Copy each argument to the concat string */
	for (i = 0; i < ac; i++)
	{
		for (j = 0; av[i][j] != '\0'; j++)
		{
			concat[k] = av[i][j];
			k++;
		}
		concat[k] = '\n';
		k++;
	}
	concat[k] = '\0';
	return (concat);
}
