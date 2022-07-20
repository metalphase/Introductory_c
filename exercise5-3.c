#include <stdio.h>
#include <ctype.h>
#include <stdlib.h> /* for atof() */

void strcat_ptr(char *s, char *t);

/* Write a pointer version of the function strcat that we showed in Chapter
2: strcat(s, t) copies the string t to the end of s.*/
int main()
{   
    char s[100] = "first";
    char t[100] = "second";

    strcat_ptr(&s[0], &t[0]);
    printf("%s\n", s);

    return 0;
}

void strcat_ptr(char *s, char *t)
{
    // Find the end of s
    while (*s != '\0')
    {
        printf("%c", *s);
        s++;
    }
    printf("%c\n", *s);
    
    // Copy t
    while ((*s = *t) != '\0')
    {   
        printf("%c", *s);
        
        s++;
        t++;
    }

    putchar('\n');
}
