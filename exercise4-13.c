#include <stdio.h>
#include <stdlib.h> /* for atof() */


#define swap(t,x,y) {t tmp = x; x = y; y = tmp;}

/* Define a macro swap(t,x,y) that interchanges two arguments of type t. */
int main()
{   
    int x = 2;
    int y = 1;

    printf("x = %d, y = %d\n", x, y);
    swap(int, x, y);
    printf("x = %d, y = %d\n", x, y);

    
    x = 123;
    y = 456;

    printf("x = %d, y = %d\n", x, y);
    swap(int, x, y);
    printf("x = %d, y = %d\n", x, y);

    return 0;
}
