#include "main.h"
/**
 * print_alphabet - prints the alphabet in lowercase followed by a newline
 *
 * Return: void
 */
void print_alphabet(void)
{
char ch[] = "abcdefghijklmnopqrstuvwxyz\n";
int i = 0;
while (ch[i] != '\0')
{
_putchar(ch[i]);
i++;
}
}
