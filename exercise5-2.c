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

int getfloat(float *pn);

/* Write getfloat, the floating-point analog of getint. What type does 
getfloat return as its function value. */
int main()
{   
    float pn;
    int c;

    c = getfloat(&pn);
    printf("pn = %f\n c = %c\n", pn, c);
    printf("---------------------------\n");

    c = getfloat(&pn);
    printf("pn = %f\n c = %c\n", pn, c);
    printf("---------------------------\n");

    c = getfloat(&pn);
    printf("pn = %f\n c = %c\n", pn, c);
    printf("---------------------------\n");

    c = getfloat(&pn);
    printf("pn = %f\n c = %c\n", pn, c);
    printf("---------------------------\n");
    
    c = getfloat(&pn);
    printf("pn = %f\n c = %c\n", pn, c);
    printf("---------------------------\n");

    c = getfloat(&pn);
    printf("pn = %f\n c = %c\n", pn, c);
    printf("---------------------------\n");
    return 0;
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

int getfloat(float *pn)
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
        
        // Checking for floating point
        if (c == '.')
        {   
            c = getch();
            float i = 1;
            for (; isdigit(c); c = getch())
            {   
                i /= 10;
                *pn += (i * (c - '0'));
            }
        }


        *pn *= sign;
        if (c != EOF)
            ungetch(c);
        
        return c;
    }
    else if (c == '.')
    {
        *pn = 0.0;
        c = getch();
        float i = 1;
        for (; isdigit(c); c = getch())
        {   
            i /= 10;
            *pn += (i * (c - '0'));
        }
        
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