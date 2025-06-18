#include "main.h"
#include <stdlib.h>
/**
 * str_concat -  that concatenates two strings.
 * @s1: string to concatenate
 * @s2: string 2 to concatenate
 * Return: a pointer to a newly allocated space in memory.
 */
char *str_concat(char *s1, char *s2)
{
	char *string_cat = NULL;
	unsigned int i = 0;
	unsigned int j = 0;
	unsigned int len1 = 0;
	unsigned int len2 = 0;

	if (s1 == NULL)
		s1 = "";

	if (s2 == NULL)
		s2 = "";

	while (s1[len1] != '\0')
	{
		len1++;
	}

	while (s2[len2] != '\0')
	{
		len2++;
	}
	len2++;

	string_cat = malloc((len1 + len2) * sizeof(char));

	if (string_cat == NULL)
		return (NULL);

	for (i = 0; i < len1; i++)
	{
		*(string_cat + i) = *(s1 + i);
	}

	for (j = 0; j < len2; i++, j++)
	{
		*(string_cat + i) = *(s2 + j);
	}

	return (string_cat);
}
