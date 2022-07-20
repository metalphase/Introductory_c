#include <stdio.h>
#include <string.h>

#define MAX_STRING_LENGTH 10000
/* Write a function escape(s, t) that converts characters like newline
and tab into visible escape sequences like \n and \t as it copies the string
t to s. Use a switch. Write a function for the other direction as well,
converting escape sequences into the real characters. */
void escape(char s[], char t[]);

int main()
{  
    char t[] = "This \n \n \n \n \t \t \t is a string with a newline, \n, and a tab, \t. These will not appear in s.";
    char s[strlen(t)];
   

    
    escape(s,t);
    for(int i = 0; s[i] != '\0'; i++)
        putchar(s[i]);
        
    return 0;
}

// We'll assume that the char array, s[], is the same size as t
void escape(char s[], char t[])
{   
    int i, j;

    i = 0;
    j = 0;
    while(t[i] != '\0')
    {
        switch(t[i])
        {   
            case '\n': 
                s[j]   = '\\';
                s[j+1] = 'n';
                j += 2;
                break;
            case '\t':
                s[j]   = '\\';
                s[j+1] = 't';
                j += 2;
                break;
            default:
                s[j] = t[i];
                ++j;
                break;
        }

        ++i;
    }
}
