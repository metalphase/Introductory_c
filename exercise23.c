 % %#include <stdio.h>
#define MAXLINE 1000    /

#define IN_SINGLE_LINE_COMMENT 2
#define IN_MULTI_LINE_COMMENT 1
#define REGULAR_CODE 0

/

/

int main()
{
    int c, prev_c, new_c, state, prev_state, new_state; 
    prev_c = 0; /
    new_c = 0;
    state = REGULAR_CODE;
    prev_state = REGULAR_CODE;
    new_state = REGULAR_CODE;

    /

    while ((new_c = getchar()) != EOF)
    {  
        
        if (new_state == REGULAR_CODE)
        {
            
            if (c == '/' && new_c == '/')
                new_state = IN_SINGLE_LINE_COMMENT;
        
            
            else if (c == '/' && new_c == '*')
                new_state = IN_MULTI_LINE_COMMENT;
        }
        else if (new_state == IN_SINGLE_LINE_COMMENT)
        {
            
            if (new_c == '\n')
                new_state = REGULAR_CODE;
        }
        else if (new_state == IN_MULTI_LINE_COMMENT)
        {
            
            if (c == '*' && new_c == '/')
                new_state = REGULAR_CODE;
        }

        
        if ((prev_state == REGULAR_CODE) && (state == REGULAR_CODE))
        {   
            putchar(prev_c); 
        }

        prev_state = state;
        state = new_state;

        
        prev_c = c;
        c = new_c;
    