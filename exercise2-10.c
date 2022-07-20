#include <stdio.h>
#include <math.h>
#include <limits.h>
#include <stdlib.h>


int lower(int c);
int lower2(int c);
/* Rewrite the function lower, which converts upper case letters
to lower case, with a conditional expression instead of if-else */
int main()
{ 
    putchar(lower2('A'));
    putchar('\n');
    putchar(lower2('a'));
    putchar('\n');


    putchar(lower('B'));
    putchar('\n');
    putchar(lower('b'));
    putchar('\n');
    return 0;
}

int lower(int c)
{
    if (c >= 'A' && c <= 'Z')
        return c + 'a' - 'A';
    else
        return c;

}

int lower2(int c)
{
    int ans = 0;

    ans = (c >= 'A' && c <= 'Z') ? (c + 'a' - 'A') : c;
    return ans;
}