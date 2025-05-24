#include "main.h"

/**
 * print_alphabet_x10 - prints the alphabet in lowercase 10 times
 *
 * Return: void
 */
void print_alphabet_x10(void)
{
int i = 0;
char line[] = "abcdefghijklmnopqrstuvwxyz\n";
while (i < 10)
{
int j = 0;
while (line[j] != '\0')
{
_putchar(line[j]);
j++;
}
i++;
}
}

