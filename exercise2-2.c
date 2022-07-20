#include <stdio.h>
#include <stdbool.h>
#define MAXLINE 1000    /* maximum input line size */

int get_line(char line[], int maxline);
void copy(char to[], char from[]);

/* print longest input line */
int main()
{
    int len;                /* current line length */
    int max;                /* maximum length seen so far */
    char current_line[MAXLINE];     /* current input line */
    char return_line[MAXLINE];     /* line for return */

    max = 0;
    while ((len = get_line(current_line, MAXLINE)) > 0)
        if (len > 80) {
            copy(return_line, current_line);
            printf("%s", return_line);
            putchar('\n');
        }

    return 0;
}

/* get_line: read a line into s, return length */
/* we want to write a loop equivalent to for (i = 0; i<lim-1 && (c=getchar()) != '\n' && c != EOF; ++i))*/
int get_line(char s[], int lim)
{
    int c, i;
    i = 0;

    bool invalid_input = 0;
    while (!invalid_input)
    {   
        c = getchar();

        if (c != EOF)
        {
            if (c != '\n')
            {
                if (i < lim - 1)
                {
                    s[i] = c;
                    ++i;
                }
                else
                    invalid_input = 1;
            }
            else
                invalid_input = 1; 
        }
        else
            invalid_input = 1;
    }
    if (c == '\n')
    {
        s[i] = c;
        ++i;
    }
    s[i] = '\0';
    return i;
}

/* copy:    copy 'from' into 'to'; assume to is big enough */
void copy(char to[], char from[])
{
    int i;

    i = 0;
    while((to[i] = from[i]) != '\0')
        ++i;
}