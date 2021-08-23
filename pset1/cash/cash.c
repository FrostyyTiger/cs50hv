#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    float n, i;
    do
    {
      n = get_float("Change owed: ");
    }
    while(n < 0);
    i = round(n*100);
    int cb = 0;
    while(i >= 25)
    {
      i = i - 25;
      cb++;
    }
    while(i >= 10)
    {
      i = i - 10;
      cb++;
    }
    while(i >= 5)
    {
      i = i - 5;
      cb++;
    }
    while(i >= 1)
    {
      i = i - 1;
      cb++;
    }
    printf("%i\n", cb);
}