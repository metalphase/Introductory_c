#include <stdio.h>
#include <string.h>

/* Write the function itob(n,s,b) that converts the integer n into a base b
character representation in the string s. In particular, itob(n,s,16) formats
n as a hexadecimal integer in s.*/
#define MAX_STRING_SIZE 100

void itoa(int n, char s[]);
void itob(int n, char s[], int b);
void display_string(char s[]);
void reverse(char s[]);

int main()
{  
    int n = 128;
    char s[MAX_STRING_SIZE];
    char s_b[MAX_STRING_SIZE];


    itob(256, s_b, 16);
    display_string(s_b);
    putchar('\n');

    itob(n, s_b, 16);
    display_string(s_b);
    putchar('\n');

    itob(n, s_b, 2);
    display_string(s_b);
    putchar('\n');

    itob(n, s_b, 8);
    display_string(s_b);
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

/* itoa: convert n to characters in s */
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

void itob(int n, char s[], int b)
{
    int i, sign;
    
    if ((sign = n) < 0) /* record sign */
        n = -n;         /* make n positive */
    i = 0;
    do {                        /* generates digits in reverse order */
        s[i++] = n % b + '0';  /* get next digit */
    } while ((n /= b) > 0);    /* delete it */
    if (sign < 0)
        s[i++] = '-';
    s[i] = '\0';
    reverse(s);

}

void display_string(char s[])
{
    for(int i = 0; ((s[i] != '\0') && (i < MAX_STRING_SIZE)); i++)
        putchar(s[i]);
}