#include <stdio.h>

/* copy input to output; 2nd version */
main()
{
    int c;

    c = (getchar() != EOF);
    printf("%s", c);
}

