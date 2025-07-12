#include "3-calc.h"
#include <stdlib.h>

/**
 * get_op_func -function returns a pointer to the function that
 * corresponds to the operator given as a parameter
 * @s: operator passed as argument to the program : +, *, -, /, %
 * Return: pointer to the correct operation function or NULL if not match
 * with 's'.
 */
int (*get_op_func(char *s))(int, int)
{
	op_t ops[] = {
		{"+", op_add},
		{"-", op_sub},
		{"*", op_mul},
		{"/", op_div},
		{"%", op_mod},
		{NULL, NULL}
	};
	int i = 0;

	while (ops[i].op != NULL)
	{
		if (*s == *(*(ops + i)).op)
		{
			return ((*(ops + i)).f);
		}
		i++;
	}
	return (NULL);
}
