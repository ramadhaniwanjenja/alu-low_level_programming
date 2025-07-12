#include "function_pointers.h"
/**
 * print_name - function that prints name
 * @name: parameter
 * @f:function to be executed
 */
void print_name(char *name, void (*f)(char *))
{
	if (name != NULL && f != NULL)
	{
		f(name);
	}
}
