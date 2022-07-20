#include <stdio.h>
#include <stdbool.h>


/* Write a function setbits(x,p,n,y) that returns x with the n bits that 
begin at position p set to the rightmost n bits of y, leaving the other bits
unchanged */
unsigned setbits(unsigned x, int p, int n, unsigned y);
unsigned getbits(unsigned x, int p, int n);

int main()
{
    unsigned x, y;
    int p, n;

    x = 256;
    y = 60;

    printf("%d\n", setbits(x, 3,4,y));
    return 0;
}


unsigned getbits(unsigned x, int p, int n)
{
    unsigned result;
    result = (x >> (p+1-n)) & ~(~0 << n);
    
    return result;
}

unsigned setbits(unsigned x, int p, int n, unsigned y)
{
    unsigned x_n_bits, y_n_bits;

    // get the n bits that begin at position p
    y_n_bits = getbits(y, n-1, n);

    // Then we want to left shift it so that it coincides with the p'th 
    // position of x
    y_n_bits = y_n_bits >> (p+1-n);


    // want to mask off the n bits starting at position p in x
    // First we get the n digits starting at position p
    x_n_bits = getbits(x, p, n);

    // We want to left shift this number until it starts at position p again
    x_n_bits = x_n_bits >> (p+1-n);

    // We perform an exclusive or in order to leave the n bits starting at p
    // empty (equal to 0)
    x = x ^ x_n_bits;

    // The result is just the addition of the new x and y_n_bits
    return x+y_n_bits;
}