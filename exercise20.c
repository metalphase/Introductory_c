#include <stdio.h>
#define MAXLINE 1000    /* maximum input line size */

int get_line(char line[], int maxline);
void copy(char to[], char from[]);

/* print longest input line */
main()
{
    int c, i;

    while ((c = getchar()) != EOF)
    {
        if(c == '\t')
            printf("    ");
        else
            putchar(c);
    }

    return 0;
}
