#include <stdio.h>
#include <stdlib.h> /* for atof() */
#include <ctype.h>
#include <math.h>

#define MAXOF 100  /* max size of operand or operator */
#define NUMBER '0' /* signal that a number was found */
#define CHARACTER '1' /* signal that a number was found */
#define MAXVAL 100  /* maximum depth of val stack */
#define BUFSIZE 100

char buf[BUFSIZE]; /* buffer for ungetch */
int bufp = 0;      /* next free position in buf */

int getop(char []);
void push(double);
double pop(void);

int getch(void);
void ungetch(int);

void swap(void);

int sp = 0;         /* next free stack position */
double val[MAXVAL]; /* value stack */

/* Add access to library functions like sin, exp, and pow. See <math.h> in
Appendix B, Section 4 */
int main()
{   
    int type;
    int tmp1, tmp2, tmp3, next_op;
    double op2;
    char s[MAXOF];

    while ((type = getop(s)) != EOF)
    {
        switch (type){
            case NUMBER:
                push(atof(s));
                break;
            case '+':
                push(pop() + pop());
                break;
            case '*':
                push(pop() * pop());
                break;
            case '-':

                // Check that this is not simply a negative sign, in which case
                // we skip the processing of the proceeding operator and treat
                // them both in the same processing step.
                tmp1 = getch();

                if (tmp1 >= '0' && tmp1 <= '9')
                {   
                    next_op = tmp1 - '0';
                    tmp1 = getch();

                    while(tmp1 >= '0' && tmp1 <= '9')
                    {
                        next_op *= 10;
                        next_op += tmp1 - '0';
                        tmp1 = getch();
                    }
                    ungetch(tmp1);

                    push(-1*(next_op));
                    break;
                }
                else
                {
                    ungetch(tmp1);
                    
                    op2 = pop();
                    push(pop() - op2);
                    break;
                }
                
            case '/':
                op2 = pop();
                if (op2 != 0)
                    push(pop() / op2);
                else
                    printf("error: zero divisor\n");
                break;
            case '%':
                tmp1 = (int) pop();

                if (tmp1 != 0)
                {
                    tmp2 = (int) pop();
                    push(tmp2 % tmp1);
                }
                else
                    printf("error: zero divisor\n");
                break;
            case 's':

                tmp1 = getch();
                tmp2 = getch();
                tmp3 = getch();

                if ((tmp1 == 'w') && (tmp2 == 'a') && (tmp3 == 'p'))
                {
                    swap();
                }
                else if ((tmp1 == 'i') && (tmp2 == 'n'))
                {
                    push(sin(pop()));
                    ungetch(tmp3);
                }
                else
                {
                    ungetch(tmp1);
                    ungetch(tmp2);
                    ungetch(tmp3);
                }
                break;
            case 't':

                // check for the next characters 'o' and 'p'
                tmp1 = getch();
                tmp2 = getch();

                if ((tmp1 == 'o') && (tmp2 == 'p'))
                {
                    op2 = pop();

                    printf("\t%.8g\n", op2);
                    push(op2);
                }
                else
                {
                    ungetch(tmp2);
                    ungetch(tmp1);
                }
                break;
            case 'e':

                tmp1 = getch();
                tmp2 = getch();
                
                if((tmp1 == 'x') && (tmp2 == 'p'))
                {
                    push(exp(pop()));
                }
                else
                {
                    ungetch(tmp2);
                    ungetch(tmp1);
                }
                break;
            case 'p':
            
                tmp1 = getch();
                tmp2 = getch();
                
                if((tmp1 == 'o') && (tmp2 == 'w'))
                {
                    op2 = pop();
                    push(pow(pop(), op2));
                }
                else
                {
                    ungetch(tmp2);
                    ungetch(tmp1);
                }
                break;
            // Duplicate the top element and insert to the top of the stack
            case 'd':

                tmp1 = getch();
                tmp2 = getch();

                if ((tmp1 == 'u' && tmp2 == 'p'))
                {
                    // Get the top element
                    op2 = pop();

                    // Push it twice to restore our stack to the original state
                    // and to add a duplicate to the stack
                    push(op2);
                    push(op2);
                }
                else
                {
                    ungetch(tmp2);
                    ungetch(tmp1);
                }
                break;
            // Clear the current stack
            case 'c':

                tmp1 = getch();
                tmp2 = getch();
                
                if((tmp1 == 'l') && (tmp2 == 'r'))
                {
                    while(sp > 0)
                        pop();
                    printf("Stack Cleared!\n");
                }
                else if ((tmp1 == 'o') && (tmp2 == 's'))
                {
                    push(cos(pop()));
                }
                else
                {
                    ungetch(tmp2);
                    ungetch(tmp1);
                }
                break;
            case '\n':
                printf("\t%.8g\n", pop());
                break;
            default:
                printf("error: unknown command %s\n", s);
                break;
        }
    }


    return 0;
}

/* getop: get next operator or numeric operand */
int getop(char s[])
{
    int i, c;

    while ((s[0] = c = getch()) == ' ' || c == '\t')
        ;
    s[1] = '\0';
    if (!isdigit(c) && c != '.')
        return c; /* not a number */

    // c >= 'a' && c <= 'z'
    i = 0;
    if (isdigit(c)) /* collect integer part */
        while (isdigit(s[++i] = c = getch()))
            ;
    if (c == '.')   /* collect fraction part */
        while (isdigit(s[++i] = c = getch()))
            ;
    s[i] = '\0';
    if (c != EOF)
        ungetch(c);
    return NUMBER;
}

/* push: push f onto value stack */
void push(double f)
{
    if (sp < MAXVAL)
        val[sp++] = f;
    else
        printf("error: stack full, can't push %g\n", f);
}

/* pop: pop and return top value from stack */
double pop(void)
{
    if (sp > 0)
        return val[--sp];
    else{
        printf("error: stack empty\n");
        return 0.0;
    }
}

/* swap: interchanges the values at the top of the stack */
void swap(void)
{
    int pop1, pop2;

    pop1 = pop();
    pop2 = pop();

    push(pop1);
    push(pop2);
}

int getch(void) /* get a (possibly pushed back) character */
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) /* push character back on input */
{
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}