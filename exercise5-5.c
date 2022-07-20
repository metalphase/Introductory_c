#include <stdio.h>
#include <ctype.h>
#include <stdlib.h> /* for atof() */

char *strncpy_user(char *s, char *t, int n);
char *strncat_user(char *s, char *t, int n);
int strncmp_user(char *s, char *t, int n);

/* Write versions of the library functions strncpy, strncat, and strncmp
which operate on at most the first n characters of their argument strings.
For example, strncpy(s, t, n) copies at most n characters of t to s. 

strncpy
----------------
s = first
t = second

strncpy(s, t, 1) // s = sirst
strncpy(s, t, 2) // s = serst
strncpy(s, t, 3) // s = secst


strncat
---------------
s = firstsecond
t =      second

strncat
*/


int main()
{   

    // Testing strncpy_user
    printf("--------------------\n");
    printf("Testing strncpy_user\n");
    printf("--------------------\n");

    char s1[100] = "first";    
    char t[] = "second";

    strncpy_user(&s1[0], &t[0], 1);
    printf("s1 = %s\n", s1);

    char s2[100] = "first";
    strncpy_user(&s2[0], &t[0], 2);
    printf("s2 = %s\n", s2);

    char s3[100] = "first";
    strncpy_user(&s3[0], &t[0], 3);
    printf("s3 = %s\n", s3);

    char s4[100] = "first";
    strncpy_user(&s4[0], &t[0], 10);
    printf("s4 = %s\n", s4);
    printf("--------------------\n");
    
    // Testing strncat_user
    printf("Testing strncat_user\n");
    printf("--------------------\n");
    char s5[100] = "first";    

    strncat_user(&s5[0], &t[0], 1);
    printf("s5 = %s\n", s5);

    char s6[100] = "first";
    strncat_user(&s6[0], &t[0], 2);
    printf("s6 = %s\n", s6);

    char s7[100] = "first";
    strncat_user(&s7[0], &t[0], 3);
    printf("s7 = %s\n", s7);

    char s8[100] = "first";
    strncat_user(&s8[0], &t[0], 10);
    printf("s8 = %s\n", s8);
    printf("--------------------\n");

    // Testing strncmp_user
    printf("Testing strncmp_user\n");
    printf("--------------------\n");
    char s9[100] = "first";    

    printf("s = %s, t = %s\n", s9, t);
    printf("strncmp(s,t,1) = %d\n",strncmp_user(&s9[0], &t[0], 1));

    char s10[100] = "sirst";
    printf("s = %s, t = %s\n", s10, t);
    printf("strncmp(s,t,1) = %d\n",strncmp_user(&s10[0], &t[0], 1));

    printf("s = %s, t = %s\n", s10, t);
    printf("strncmp(s,t,2) = %d\n",strncmp_user(&s10[0], &t[0], 2));

    printf("s = %s, t = %s\n", s10, t);
    printf("strncmp(s,t,10) = %d\n",strncmp_user(&s10[0], &t[0], 10));

    char s11[100] = "second";
    printf("s = %s, t = %s\n", s11, t);
    printf("strncmp(s,t,6) = %d\n",strncmp_user(&s11[0], &t[0], 6));

    printf("s = %s, t = %s\n", s11, t);
    printf("strncmp(s,t,20) = %d\n",strncmp_user(&s11[0], &t[0], 20));
    return 0;
}


int strncmp_user(char *s, char *t, int n)
{
    char *ps, *pt;
    int len, difference;
    
    ps = s;
    pt = t;
    difference = 0;

    for(int i = 0; i < n && (*ps != '\0' || *pt != '\0'); i++)
    {   
        if(*ps != *pt)
        {
            difference = *ps - *pt;
            return difference;
        }

        ps++;
        pt++;
    }

    return difference;
}

char *strncpy_user(char *s, char *t, int n)
{
    char *ps, *pt;
    int len;

    ps = s;
    pt = t;

    while(*pt != '\0')
        pt++;
    
    // Get the length of the string t, and compare to n
    len = pt - t;
    pt = t;

    // If n is less than the length of the string, t, then we set len to 
    // n and iterate. Otherwise, we limit ourselves to at most len iterations.
    if (n < len)
        len = n;
    
    for (int i = 0; i < len; i++)
    {
        *ps++ = *pt++;
    }

    return s;
}

char *strncat_user(char *s, char *t, int n)
{
    char *ps, *pt;
    int len;

    ps = s;
    pt = t;

    while(*ps != '\0')
        ps++;
    while(*pt != '\0')
        pt++;
    
    // Get the length of the string t, and compare to n
    len = pt - t;
    pt = t;

    // If n is less than the length of the string, t, then we set len to 
    // n and iterate. Otherwise, we limit ourselves to at most len iterations.
    if (n < len)
        len = n;
    
    for (int i = 0; i < len; i++)
    {
        *ps++ = *pt++;
    }
    
    ps++;
    *ps = '\0';

    return s;
}
