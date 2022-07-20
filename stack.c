#include <stdio.h>
#include <ctype.h>

/* atof: covert string s to double */
double atof(char s[]);
double atof2(char s[]);

/* Extend atof to handle scientific notation of the form 123.45e-6 */
int main()
{   

}
#include <stdio.h>
#include "calc.h"

#define MAXVAL 100  /* maximum depth of val stack */

int sp = 0;         /* next free stack position */
double val[MAXVAL]; /* value stack */

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