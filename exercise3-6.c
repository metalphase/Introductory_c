#include <stdio.h>
#include <string.h>

/* Write a version of itoa that accepts three arguments instead of two. The 
third argument is a minimum field width; the converted number must be padded
with blanks on the left if necessary to make it wide enough. */
#define MAX_STRING_SIZE 100

void itoa(int n, char s[]);
void itoa_fill(int n, char s[], int min_width);
void display_string(char s[]);
void reverse(char s[]);

int main()
{  
    int n = 128;
    char s[MAX_STRING_SIZE];

    // 20 Minimum Width
    itoa_fill(n, s, 20);
    display_string(s);
    putchar('\n');

    // 10 Minimum Width
    itoa_fill(n, s, 10);
    display_string(s);
    putchar('\n');

    // 2 Minimum Width
    itoa_fill(n, s, 2);
    display_string(s);
    putchar('\n');

    // 0 Minimum Width
    itoa_fill(n, s, 0);
    display_string(s);
    putchar('\n');
    
    return 0;
}

/* reverse: reverse string s in place */
void reverse(char s[])
{
    int c, i, j;

    for (i = 0, j = strlen(s)-1; i < j; i++, j--)
    {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

void itoa(int n, char s[])
{
    int i, sign;
    
    if ((sign = n) < 0) /* record sign */
        n = -n;         /* make n positive */
    i = 0;
    do {                        /* generates digits in reverse order */
        s[i++] = n % 10 + '0';  /* get next digit */
    } while ((n /= 10) > 0);    /* delete it */
    if (sign < 0)
        s[i++] = '-';
    s[i] = '\0';
    reverse(s);
}

void itoa_fill(int n, char s[], int min_width)
{
    int i, sign;
    
    if ((sign = n) < 0) /* record sign */
        n = -n;         /* make n positive */
    i = 0;
    do {                        /* generates digits in reverse order */
        s[i++] = n % 10 + '0';  /* get next digit */
    } while ((n /= 10) > 0);    /* delete it */
    if (sign < 0)
        s[i++] = '-';
    
    // Check that we are below the minimum width 
    if (i < min_width)
        // Print the corrent number of spaces to pad the length while we are
        // under the minimum width
        while(i < min_width)
            s[i++] = ' ';
    
    s[i] = '\0';

    reverse(s);
}

void display_string(char s[])
{
    for(int i = 0; ((s[i] != '\0') && (i < MAX_STRING_SIZE)); i++)
        putchar(s[i]);
}