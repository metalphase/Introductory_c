#include <stdio.h>

#define IN 1
#define OUT 0

/* count lines, words, and characters in input */
main()
{
    int c, state;
    
    state = OUT;
    while ((c = getchar()) != EOF)
    {
        int prev_c;
        if (c == ' ' || c == '\n' || c == '\t'){
            state = OUT;
            
            if ((prev_c != ' ') && (prev_c != '\n') && (prev_c != '\t'))
                putchar('\n');
                
            prev_c = c;
        }
        else if (state == OUT){
            state = IN;
            prev_c = c;
            putchar(c);
        }
        else if (state == IN){
            putchar(c);
            prev_c = c;
        }
    }
}