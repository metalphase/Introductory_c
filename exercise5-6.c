#include <stdio.h>
#include <ctype.h>
#include <stdlib.h> /* for atof() */

/* Rewrite appropriate programs from earlier chapters and exercises with
pointers instead of array indexing. Good possibilities include getline,
atoi, itoa, and their variants, and strindex and getop. */

int get_line_ptr(char *s, int lim);
int atoi_ptr(char *s);

int main()
{   
    // Testing get_line_ptr 
    int lim = 100;
    char s1[lim];

    get_line_ptr(&s1[0], lim);
    printf("s1 = %s\n", s1);

    get_line_ptr(&s1[0], lim);
    printf("s1 = %s\n", s1);

    // Testing atoi_ptr
    char s2[100] = "1234567";
    printf("s2 = %d\n", atoi_ptr(&s2[0]));

    char s3[100] = "-1234567";
    printf("s3 = %d\n", atoi_ptr(&s3[0]));

    char s4[100] = "";
    printf("s4 = %d\n", atoi_ptr(&s4[0]));
    return 0;
}

int atoi_ptr(char *s)
{
    int i, sign, val;

    for(i=0;isspace(*s);i++)
        ;
    sign = (*s == '-') ? -1 : 1;
    if(*s == '+' || *s == '-')
        s++;
    for(val = 0; isdigit(*s); s++)
        val = 10*val + (*s - '0');

    return sign * val;
}

int get_line_ptr(char *s, int lim)
{
    int c, i;

    for(i=0; i<lim-1 && (c=getchar())!=EOF && c!='\n'; ++i)
    {
        *s = c;
        s++;
    }
    if (c == '\n')
    {
        *s = c;
        s++;
        i++;
    }
    *s = '\0';
    return i;
}