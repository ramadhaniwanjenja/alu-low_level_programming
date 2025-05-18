#include <stdio.h>
/**
 * main - Entry point
 *
 * Return: Always 0 (Success)
 */
int main(void)
{
int i = 0;
while (i <= 9)
{
putchar('0' + i);
i++;
}
i = 0;
while (i < 6)
{
putchar('a' + i);
i++;
}
putchar('\n');
return (0);
}
