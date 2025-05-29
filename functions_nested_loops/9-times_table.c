#include "main.h"
/**
 * times_table - Prints the 3 times table, starting with 0
 */
void times_table(void)
{
int row = 0;
while (row <= 9)
{
int col = 0;
while (col <= 9)
{
int product = row * col;
if (col > 0)
{
_putchar(',');
_putchar(' ');
if (product < 10)
{
_putchar(' ');
}
}
if (product >= 10)
{
_putchar('0' + (product / 10));
}
else if (col > 0)
{
}
_putchar('0' + (product % 10));
col++;
}
_putchar('\n');
row++;
}
}
