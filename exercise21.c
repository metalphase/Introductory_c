#include <stdio.h>
#define MAXLINE 1000    /* maximum input line size */

int get_line(char line[], int maxline);
void copy(char to[], char from[]);

/* print longest input line */
main()
{
    int c, num_blanks;
    num_blanks = 0;

    while ((c = getchar()) != EOF)
    {   
        if (c == ' ')
            num_blanks++;

        if (num_blanks == 4)
        { 
            putchar('\t');
            putchar('|');
            num_blanks = 0;
        }
        else if (num_blanks > 0 && c != ' ')
        {
            for (int num_chars = 0; num_chars < num_blanks; num_chars++)
            {
                putchar(' ');
                putchar('/');
            }
            
            putchar(c);
            num_blanks = 0;
        }
        else
            putchar(c);
    }

    return 0;
}
