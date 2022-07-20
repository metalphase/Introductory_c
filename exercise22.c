#include <stdio.h>
#define MAXLINE 1000    /* maximum input line size */

#define N 30 /* maximum number of characters before new line*/


main()
{
    int num_chars = 0;

    while ((c = getchar()) != EOF)
    {   

        if (num_chars < N)
        {
            putchar(c);
            num_chars++;
        }
        
        

    }
}
