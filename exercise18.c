#include <stdio.h>
#define MAXLINE 1000    /* maximum input line size */

int get_line(char line[], int maxline);
void copy(char to[], char from[]);

/* print longest input line */
main()
{
    int len;                /* current line length */
    int max;                /* maximum length seen so far */
    char current_line[MAXLINE];     /* current input line */
    char return_line[MAXLINE];     /* line for return */

    max = 0;
    while ((len = get_line(current_line, MAXLINE)) > 0)
    {
        int new_len = len;
        int i = len - 1;

        while((current_line[i] == ' ' || current_line[i] == '\t') && i >= 0){
            printf("Here!");
            putchar(current_line[i]);
            --new_len;
            --i;
        }

        /*
        for(int j = 0; j < len; j++)
        {
            if(current_line[j] == ' ' || current_line[j] == '\t')
                printf("Found blank/tab space!");
        }
        
        for (int j  = 0; j < new_len; j++)
            putchar(current_line[j]);
        */
        
        printf("old length: %d , new length: %d\n", len, new_len);

    }
    return 0;
}

/* get_line: read a line into s, return length */
int get_line(char s[], int lim)
{
    int c, i;

    for (i=0; i<lim-1 && (c=getchar())!=EOF && c!='\n'; ++i)
        s[i] = c;
    if (c == '\n'){
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