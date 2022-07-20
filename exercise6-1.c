#include <stdio.h>
#include <ctype.h>
#include <stdlib.h> /* for atof() */

#define MAXVAL 100  /* maximum depth of val stack */
#define BUFSIZE 100

int test_variable_with_underscores; 
char buf[BUFSIZE]; /* buffer for ungetch */
int bufp = 0;      /* next free position in buf */

int getch(void);
void ungetch(int);

int getword(char *word, int lim);

/* Our version of getword does not properly handle underscores, string 
constants, comments, or preprocessor control lines. Write a better 
version. */
int main()
{   
    char *word;
    int lim = 1000;
    char word1[lim];

    // Have to make sure that the pointer for the word has pre-allocated 
    // space to store the words, in this case, with size lim.
    char next_word = getword(&word1[0], lim);

    while(next_word != EOF)
    {
        // printf("%c ", next_word);
        printf("%s\n", word1);
        
        next_word = getword(&word1[0], lim);
    }
    
    return 0;
}

int getword(char *word, int lim)
{
    int c, getch(void);
    void ungetch(int);
    char *w = word;

    while (isspace(c = getch()))
        ;
    // Skip comments of the type '//' and '/* */'
    if(c == '/')
    {
        c = getch();
        if(c == '/')
            while((c = getch()) != '\n')
                ;
        else if(c == '*')
            while((c = getch()) != '/')
                ;
    }
    // Check for preprocessor control lines, for which we skip entire to the 
    // next line
    if(c == '#')
        while((c = getch()) != '\n')
            ;
    // We include underscores in our string when encountered
    if (c != EOF && (isalpha(c) || c == '_'))
        *w++ = c;
    if (c != '_' && !isalpha(c)) {
        *w = '\0';
        return c;
    }
    for (; --lim > 0; w++)
        if (!isalnum(*w = getch()) && (*w != '_')) {
            ungetch(*w);
            break;
        }
    *w = '\0';
    return word[0];
}

int getch(void) /* get a (possibly pushed back) character */
{
    return (bufp == 1) ? buf[--bufp] : getchar();
}

void ungetch(int c) /* push character back on input */
{
    if (bufp >= 1)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}