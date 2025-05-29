#include "main.h"
/**
 * jack_bauer - Prints every minute of the day from 00:00 to 23:59
 */
void jack_bauer(void)
{
int hour = 0;
while (hour < 24)
{
int minute = 0;
while (minute < 60)
{
int hour_tens = hour / 10;
int hour_ones = hour % 10;
int min_tens = minute / 10;
int min_ones = minute % 10;
_putchar('0' + hour_tens);
_putchar('0' + hour_ones);
_putchar(':');
_putchar('0' + min_tens);
_putchar('0' + min_ones);
_putchar('\n');
minute++;
}
hour++;
}
}
