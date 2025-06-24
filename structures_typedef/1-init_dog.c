#include <stdio.h>
#include "dog.h"
/**
 * init_dog -  initialize a variable of type struct dog
 * @d: a variable of type struct dog
 * @name: first member of struct
 * @age: second member of struct
 * @owner: third member of struct
 */

void init_dog(struct dog *d, char *name, float age, char *owner)
{
	if (d != NULL)
	{
		d->name = name;
		d->age = age;
		d->owner = owner;
	}
}
