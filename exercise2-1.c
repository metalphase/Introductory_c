#include <stdio.h>
#include <limits.h>
#include <float.h>
/* Write a program to determine the ranges of char, short, int, and long
variables, both signed and unsigned, by printing appropriate values from 
standard headers and by direct computation. Harder if you compute them: 
determine the ranges of the various floating-point types. */
int main()
{
    // Range of char
    printf("CHAR_MAX = %d, CHAR_MIN = %d\n", CHAR_MAX, CHAR_MIN);

    // Range of short
    printf("SHORT_MAX = %d, SHORT_MIN = %d\n", SHRT_MAX, SHRT_MIN);
    
    // Range of long
    printf("LONG_MAX = %ld, LONG_MIN = %ld\n", LONG_MAX, LONG_MIN);

    // Range of int
    printf("INT_MAX = %d, INT_MIN = %d\n", INT_MAX, INT_MIN);

    // Range of signed char
    printf("SCHAR_MAX = %d, SCHAR_MIN = %d\n", SCHAR_MAX, SCHAR_MIN);

    // Range of unsigned int
    printf("UINT_MAX = %d\n", UINT_MAX);

    // Range of unsigned long
    printf("ULONG_MAX = %lu\n", ULONG_MAX);

    // Range of unsigned short
    printf("USHRT_MAX = %d\n", USHRT_MAX);

    // Range of floats
    printf("FLT_MAX = %f, FLT_MIN = %f\n", FLT_MAX, FLT_MIN);

    // Range of doubles
    printf("DBL_MAX = %f, DBL_MIN = %f\n", DBL_MAX, DBL_MIN);
    
}
