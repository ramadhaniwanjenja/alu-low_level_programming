#include "main.h"
#include <stdlib.h>
/**
 * _strdup - returns a pointer to a newly allocated space in memory,
 * which contains a copy of the string given as a parameter.
 * @str: string to copy
 *
 * Return: a pointer to a newly allocated space in memory.
 */
char *_strdup(char *str)
{
	char *string_cpy = NULL;
	unsigned int i = 0;
	unsigned int len = 0;

	if (str == NULL)
		return (NULL);

	while (str[len] != '\0')
	{
		len++;
	}
	len++;

	string_cpy = malloc(len * sizeof(char));

	if (string_cpy == NULL)
		return (NULL);

	for (i = 0; i < len; i++)
	{
		string_cpy[i] = str[i];
	}

	return (string_cpy);
}
