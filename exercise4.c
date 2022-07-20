#include <stdio.h>

/* copies the input to output, replacing each string of one or more blanks
   with a single blank */
main()
{
    int c;

    while ((c = getchar()) != EOF)
    {
        if(c == ' ')
        {   
            int d; 

            while ((d = getchar()) != EOF && d == ' ')
                ;

            putchar(' ');
            putchar(d);
            
        }
        else
            putchar(c);
    }

}