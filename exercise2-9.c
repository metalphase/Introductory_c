#include <stdio.h>
#include <math.h>
#include <limits.h>
#include <stdlib.h>

int bitcount(unsigned x);
int bitcount_2s(unsigned x);

/* In a two's complement number system, x &= (x-1) deletes the rightmost 
1-bit in x. Explain why. Use this observation to write a faster version 
of bitcount */
int main()
{ 
    unsigned x;

    x = 255;
    printf("%d\n", bitcount(x));

    printf("%d\n", bitcount_2s(x));

    return 0;
}

int bitcount(unsigned x)
{
    int b;

    for(b = 0; x != 0; x >>= 1)
        if (x & 01)
            b++;

    return b;
}

int bitcount_2s(unsigned x)
{
    int b;

    for(b = 0; x != 0; x >>= 1)
    {
        x &= (x-1);
        b++;
    }
    return b;
}