#include "main.h"
/**
 * times_table - Prints the 9 times table, starting with 0
 */
void times_table(void)
{
int i = 0;
while (i <= 9)
{
int j = 0;
while (j <= 9)
{
int product = i * j;
if (j > 0)
{
_putchar(',');
_putchar(' ');
}
if (product >= 10)
{
_putchar('0' + (product / 10));
}
else if (j > 0)
{
_putchar(' ');
}
if (product < 10 && j > 0)
{
_putchar(' ');
}
else if (product >= 10)
{
}
_putchar('0' + (product % 10));
j++;
}
_putchar('\n');
i++;
}
}
