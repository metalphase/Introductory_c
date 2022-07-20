#include <stdio.h>
#include <stdlib.h> /* for atof() */
#include <ctype.h>
#include <math.h>

#define MAXOF 100  /* max size of operand or operator */
#define NUMBER '0' /* signal that a number was found */
#define MAXVAL 100  /* maximum depth of val stack */
#define BUFSIZE 100
#define MAXLINE 100 /* Maximum length of line */

char buf[BUFSIZE]; /* buffer for ungetch */
int bufp = 0;      /* next free position in buf */

// Variables required in reading characters one-by-one within a complete
// line
int bytes_read;
int current_char = 0;
size_t size = 10;
char *string;

int getop(char []);
void push(double);
double pop(void);

int getch(void);
void ungetch(int);

int sp = 0;         /* next free stack position */
double val[MAXVAL]; /* value stack */

double variables[26]; /* array storage for variables 'a-z' */

char getchar_line(); /* gets the next char from the current line until the
                        end of the liine or document */
                    
/* An alternate organization uses getline to read an entire input line; this
makes getch and ungetch unnecessary. Revise the calculator to use this 
approach*/
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

/* getchar_line: returns a character representing the next character in the 
input line */
char getchar_line()
{   
    if (bytes_read == -1)
    {
        return EOF;
    }
    else if (bytes_read == 0 ||  ((bytes_read - 1) - current_char) == 0)
    {
        bytes_read = getline(&string, &size, stdin);
        current_char = 0;

        return '\n';
    }
    else
        return string[current_char++];
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

int getch(void) /* get a (possibly pushed back) character */
{
    return (bufp == 1) ? buf[--bufp] : getchar_line();
}

void ungetch(int c) /* push character back on input */
{
    if (bufp >= 1)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}