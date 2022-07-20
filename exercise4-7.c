#include <stdio.h>
#include <stdlib.h> /* for atof() */
#include <ctype.h>
#include <math.h>

#define MAXOF 100  /* max size of operand or operator */
#define NUMBER '0' /* signal that a number was found */
#define MAXVAL 100  /* maximum depth of val stack */
#define BUFSIZE 100

char buf[BUFSIZE]; /* buffer for ungetch */
int bufp = 0;      /* next free position in buf */

int getop(char []);
void push(double);
double pop(void);

int getch(void);
void ungetch(int);
void ungets(char []);

void swap(void);

int sp = 0;         /* next free stack position */
double val[MAXVAL]; /* value stack */

double variables[26]; /* array storage for variables 'a-z' */

/* Write a routine ungets(s) that will push back an entire string onto the 
input. Should ungets know about buf and bufp, or should it just use ungetch? */
int main()
{   
    int type;
    int tmp1, tmp2, tmp3, next_op;
    double op1, op2, ans;
    char s[MAXOF];
    char ret_s[3];

    while ((type = getop(s)) != EOF)
    {
        switch (type){
            case NUMBER:
                ans = atof(s);
                push(ans);
                break;
            case '+':
                op2 = pop();
                op1 = pop();

                push(op1 + op2);
                break;
            case '*':
                op2 = pop();
                op1 = pop();
                
                push(op1 * op2);
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
                op1 = pop();

                if (op2 != 0)
                    push(op1 / op2);
                else
                    printf("error: zero divisor\n");
                break;
            case '%':
                op2 = (int) pop();

                if (op2 != 0)
                {
                    op1 = (int) pop();
                    push(((int) op1) % ((int) op2));
                }
                else
                    printf("error: zero divisor\n");
                break;
            // Create a '=' operator that assigns values to variables
            case 'a':

                tmp1 = getch();
                tmp2 = getch();

                ret_s[0] = tmp1;
                ret_s[1] = tmp2;
                ret_s[2] = '\0';

                if((tmp1 == 'n') && (tmp2 == 's'))
                {
                    printf("ans = %f\n", ans);
                    push(ans);
                }
                else
                    ungets(ret_s);
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
            case 's':

                tmp1 = getch();
                tmp2 = getch();
                tmp3 = getch();

                ret_s[0] = (char) tmp1;
                ret_s[1] = (char) tmp2;
                ret_s[2] = (char) tmp3;

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
                    ungets(ret_s);
                
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

void ungets(char s[])
{
    int i = 0;

    while((s[i] != '\0') && (bufp < BUFSIZE))
    {
        buf[bufp++] = s[i++];
        if(bufp == BUFSIZE)
            printf("ungets: too many characters\n");
    }
}