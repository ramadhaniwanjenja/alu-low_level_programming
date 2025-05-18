#include <stdio.h>
/**
 * main - Entry point
 *
 * Return: Always 0 (Success)
 */
int main(void)
{
int i = 0;
while (i <= 7)
{
int j = i + 1;
while (j <= 8)
{
int k = j + 1;
while (k <= 9)
{
putchar('0' + i);
putchar('0' + j);
putchar('0' + k);
if (i < 7 || j < 8 || k < 9)
{
putchar(',');
putchar(' ');
}
k++;
}
j++;
}
i++;
}
putchar('\n');
return (0);
}
