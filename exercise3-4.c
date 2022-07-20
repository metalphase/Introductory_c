#include <stdio.h>
#include <string.h>
#include <limits.h>

/* In a two's complement number representation, our version of itoa does not
handle the largest negative number, that is, the value of n equal to 
-(2^(wordsize-1)). Explain why not. Modify it to print that value correctly, 
regardless of the machine on which it runs*/
#define MAX_STRING_SIZE 10000

void itoa(int n, char s[]);
void itoa_fixed(int n, char s[]);
void reverse(char s[]);
void display_string(char s[]);

int main()
{  
    int n = INT_MIN;
    char s[MAX_STRING_SIZE];
    
    printf("%d\n", n);
    printf("%d\n", -n);
    printf("%d\n", n + (-n));
    
    itoa(n, s);
    display_string(s);
    putchar('\n');

    itoa_fixed(n, s);
    display_string(s);
    putchar('\n');

    n = INT_MIN + 1;
    itoa_fixed(n, s);
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

/* itoa: convert n to characters in s */
void itoa(int n, char s[])
{
    int i, sign;
    if ((sign = n) < 0) /* record sign */
        n = -n;         /* make n positive */
                        // Our problem begins here because the absolute
                        // value of the smallest integer is larger than 
                        // the largest possible integer, so we lose accuracy
    i = 0;
    do {                        /* generates digits in reverse order */
        s[i++] = n % 10 + '0';  /* get next digit */
    } while ((n /= 10) > 0);    /* delete it */
    if (sign < 0)
        s[i++] = '-';
    s[i] = '\0';
    reverse(s);
}

void itoa_fixed(int n, char s[])
{
    int i, sign;
    long int n_l;

    n_l = n;
    if ((sign = n_l) < 0) /* record sign */
        n_l = -n_l;         /* make n positive */
                    
    i = 0;
    do {                        /* generates digits in reverse order */
        s[i++] = n_l % 10 + '0';  /* get next digit */
    } while ((n_l /= 10) > 0);    /* delete it */
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