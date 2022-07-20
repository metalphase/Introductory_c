#include <stdio.h>
#include <stdlib.h>


int bytes_read;
int current_char = 0;
size_t size = 10;
char *string;


char getchar_line(); /* gets the next char from the current line until the
                        end of the liine or document */

int main()
{   
    char c;
    while ((c = getchar_line()) != EOF)
        putchar(c); 

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
