#include <stdio.h>
#include <ctype.h>
#include <stdlib.h> /* for atof() */

#define STACKLEN 100 /* max length of stack for calculator */


int stack_pos = 0;
int argv_pos = 0;
// Store our operators in a stack/array of size STACKLEN
int ops[STACKLEN];
int op1;
int op2;

void push_operator(char op);
int pop_operator();

/* Write the program expr, which evaluates a reverse Polish expression 
from the command line, where each operator or operand is a separate argument.
For example,

expr 2 3 4 + * */
int main(int argc, char *argv[])
{   
    while (argv_pos++ < argc-1)
    {   
        printf("arg[%d] = %d, arg[%d] = %d, arg[%d] = %d, arg[%d] = %d\n", 0, ops[0], 1, ops[1], 2, ops[2], 3, ops[3]);
        if(atoi(argv[argv_pos]))
        {
            push_operator(atoi(argv[argv_pos]));
        }
        else if(*argv[argv_pos] == '+')
        {
            op2 = pop_operator();
            op1 = pop_operator();

            printf("%d + %d = %d\n", op1, op2, op1+op2);
            push_operator(op1+op2);
        }
        else if(*argv[argv_pos] == '*')
        {
            op2 = pop_operator();
            op1 = pop_operator();

            printf("%d * %d = %d\n", op1, op2, op1*op2);
            push_operator(op1*op2);
        }
        else
        {
            printf("argv[%d] = %s\n", argc, argv[argv_pos]);
        }
    }


    return 0;
}

void push_operator(char op)
{
    if(stack_pos < STACKLEN)
        ops[stack_pos++] = op;
    else
        printf("error: stack is full!\n");
}

int pop_operator()
{
    if (stack_pos > 0)
    {
        int tmp = ops[--stack_pos];

        ops[stack_pos] = 0;
        return tmp;
    }
    else{
        printf("error: stack empty!\n");
        return 0.0;
    }
}