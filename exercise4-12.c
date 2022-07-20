#include <stdio.h>
#include <string.h>

#define MAXSTRINGSIZE 100
/*printd: print n in decimal */
void printd(int n);
void itoa_recursive(int n, char s[], int i);

/* Adapt the ideas of printd to write a recursive version of itoa; that is,
convert an integer into a string by calling a recursive routine. */
int main()
{   
    printd(12345);
    putchar('\n');
    putchar('\n');
    
    
    char s1[MAXSTRINGSIZE];
    char s2[MAXSTRINGSIZE];
    char s3[MAXSTRINGSIZE];
    char s4[MAXSTRINGSIZE];
    char s5[MAXSTRINGSIZE];
    
    int i = 0;
    int input = 1;
    printf("Input = %d\n", input);
    itoa_recursive(input, s4, i);
    printf("%s\n", s4);

    i = 0;
    input = -1;
    printf("Input = %d\n", input);
    itoa_recursive(input, s5, i);
    printf("%s\n", s4);
    
    i = 0;
    input = 12345;
    printf("Input = %d\n", input);
    itoa_recursive(input, s1, i);
    printf("%s\n", s1);

    i = 0;
    input = -12345;
    printf("Input = %d\n", input);
    itoa_recursive(input, s2, i);
    printf("%s\n", s2);

    i = 0;
    input = 15;
    printf("Input = %d\n", input);
    itoa_recursive(input, s3, i);
    printf("%s\n", s3);
   

    return 0;
}

void printd(int n)
{
    if (n < 0)
    {
        putchar('-');
        n = -n;
    }
    if (n/10)
    {
        printf("i = n/10: %d\n", n/10);     
        printd(n / 10);
    }
    putchar(n % 10 + '0');
}

// convert an integer into a string by calling a recursive routine
/*
void itoa_recursive(int n, char s[], int i)
{
    if (n < 0)
    {
        s[i] = '-';
        n = -n;
        i++;
    }
    if (n/10)
    {
        printf("i = %d, n/10 = %d\n",i, n/10);
        i++;
        itoa_recursive((n / 10), s, i);
    }
    s[i] = n % 10 + '0';
    printf("i = %d, s[i] = %c\n", i, s[i]);
}
*/

void itoa_recursive(int n, char s[], int i)
{
    static int len = 0;
    int m;
    i++;

    if (n < 0)
    {
        n = -n;
        len+=2;
        s[0] = '-';
    }
    if(n / 10)
        itoa_recursive((n/10), s, i);
    
    if (len == 0)
        len = i;

    printf("i = %d, len = %d, len - i = %d,  %d\n", i, len, len - i,  n%10);
    s[len-i] = (n % 10) + '0';
    s[len-i+1] = '\0';
    
    /*
    if(i == 1)
    {
        printf("i = %d, len = %d, len - i = %d, %d null\n", i, len, len - i, n%10);
    }
    */
    
}

// change function return from void to int, where the returned int is the length