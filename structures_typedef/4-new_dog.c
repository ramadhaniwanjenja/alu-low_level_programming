#include <stdio.h>
#include <stdlib.h>
#include "dog.h"

/**
* _strlen - returns the length of a string.
* @s: pointer to string
*
* Return: length
*/
int _strlen(char *s)
{
	int length = 0;

	while (s[length] != '\0')
		length++;

	return (length);
}

/**
 * _strcpy -  copies the string pointed to by src, including the
 * terminating null byte (\0), to the buffer pointed to by dest.
 * @dest: pointer
 * @src: pointer
 *
 * Return: the pointer to dest
 */
char *_strcpy(char *dest, char *src)
{
	int i;

	for (i = 0; i <= _strlen(src); i++)
		dest[i] = src[i];

	return (dest);
}

/**
* new_dog -  creates a new dog.
* @name: first member of struct
* @age: second member of struct
* @owner: third member of struct
*
* Return:  new dog
*/
dog_t *new_dog(char *name, float age, char *owner)
{
	dog_t *my_dog;
	char *name_copy = NULL;
	char *owner_copy = NULL;

	my_dog = malloc(sizeof(dog_t));
	if (my_dog == NULL)
	{
		return (NULL);
	}

	my_dog->age = age;

	if (name != NULL)
	{
		name_copy = malloc(_strlen(name) + 1);
		if (name_copy == NULL)
		{
			free(my_dog);
			return (NULL);
		}
		my_dog->name = _strcpy(name_copy, name);
	}
	else
		my_dog->name = NULL;

	if (owner != NULL)
	{
		owner_copy = malloc(_strlen(owner) + 1);
		if (owner_copy == NULL)
		{
			free(name_copy);
			free(my_dog);
			return (NULL);
		}
		my_dog->owner = _strcpy(owner_copy, owner);
	}
	else
		my_dog->owner = NULL;

	return (my_dog);
}
