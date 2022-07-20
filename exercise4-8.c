

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

void swap(void);

int sp = 0;         /* next free stack position */
double val[MAXVAL]; /* value stack */

double variables[26]; /* array storage for variables 'a-z' */

/* Suppose that there will never be more than one character of pushback.
Modify getch and ungetch accordingly. */
int main()
{   
    int type;
    int tmp1, tmp2, tmp3, next_op;
    double op1, op2, ans;
    char s[MAXOF];

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
            case '!':
                // Scenario that deliberate tries to add more than 1
                // character to the buffer
                ungetch(' ');
                ungetch(' ');
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
    if (bufp == 1)
    {
        bufp -= 1;
        return buf[0];
    }
    else
    {
        return getchar();
    }
}

void ungetch(int c) /* push character back on input */
{
    if (bufp >= 1)
        printf("ungetch: too many characters\n");
    else
    {
        bufp += 1;
        buf[0] = c;
    }
}