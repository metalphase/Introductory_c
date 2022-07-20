#include <stdio.h>
#include <ctype.h>
#include <stdlib.h> /* for atof() */

#define MAXVAL 100  /* maximum depth of val stack */
#define BUFSIZE 100

char buf[BUFSIZE]; /* buffer for ungetch */
int bufp = 0;      /* next free position in buf */

int getch(void);
void ungetch(int);
int getint(int *pn);
int getint2(int *pn);

/* As written, getint treats a + or - not followed by a digit as a valid
representation of zero. Fix it to push such a character back on the input */
int main()
{   
    int c;
    int c2;
    int pn;
    int pn2;

    c2 = getint2(&pn2);
    printf("pn2 = %d\n", pn2);
    printf("c2 = %c\n", c2);

    printf("buf[0] = %c\n", buf[0]);
    printf("buf[1] = %c\n", buf[1]);
    printf("-------------\n");

    c2 = getint2(&pn2);
    printf("pn2 = %d\n", pn2);
    printf("c2 = %c\n", c2);

    printf("buf[0] = %c\n", buf[0]);
    printf("buf[1] = %c\n", buf[1]);
    printf("-------------\n");


    return 0;
}

int getint2(int *pn)
{
    int c, sign;

    while (isspace(c = getch())) /* skip white space */
        ;
    
    if (!isdigit(c) && c != EOF && c != '+' && c != '-'){
        ungetch(c); /* it's not a number */
        return 0;
    }

    sign = (c == '-') ? -1 : 1;
    if (c == '+' || c == '-')
        c = getch();
    
    // Check that c is a digit. If it is, we continue with for loop
    // otherwise we push it back with ungetch as long as it is not an EOF.
    if (isdigit(c))
    {
        for (*pn = 0; isdigit(c); c = getch())
            *pn = 10 * *pn + (c - '0');
        
        *pn *= sign;
        if (c != EOF)
            ungetch(c);
        
        return c;
    }
    else
    {
        if (c != EOF)
            ungetch(c);
        
        return c;
    }
}

int getint(int *pn)
{
    int c, sign;

    while (isspace(c = getch())) /* skip white space */
        ;
    
    if (!isdigit(c) && c != EOF && c != '+' && c != '-'){
        ungetch(c); /* it's not a number */
        return 0;
    }

    sign = (c == '-') ? -1 : 1;
    if (c == '+' || c == '-')
        c = getch();
    
    for (*pn = 0; isdigit(c); c = getch())
        *pn = 10 * *pn + (c - '0');
        
    *pn *= sign;
    if (c != EOF)
        ungetch(c);
        
    return c;
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