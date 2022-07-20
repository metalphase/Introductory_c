#include <stdio.h>
#include <ctype.h>
#include <stdlib.h> /* for atof() */

void strcat_ptr(char *s, char *t);
int strend(char *s, char *t);

/* Write the function strend(s, t) which returns 1 if the string t occurs
at the end of the string s, and zero otherwise. 

s = firstsecond
t =      second
t2 =     pefond

strend(s, t) // returns 1
strend(s, t2) // returns 0

*/


int main()
{   
    char s1[] = "firstsecond";
    char s2[] = "firstsepond";
    char s3[] = "firstrecond";
    char s4[] = "firstreconf";
    
    char t[] = "second";

    printf("s = %s, t = %s, strend = %d\n", s1, t, strend(&s1[0], &t[0]));
    printf("s = %s, t = %s, strend = %d\n", s2, t, strend(&s2[0], &t[0]));
    printf("s = %s, t = %s, strend = %d\n", s3, t, strend(&s3[0], &t[0]));
    printf("s = %s, t = %s, strend = %d\n", s4, t, strend(&s4[0], &t[0]));
    return 0;
}

int strend(char *s, char *t)
{
    char *ps, *pt;
    int len, i;

    ps = s;
    pt = t;

    // Get ps and pt to point to end of s and t, respectively
    while(*ps != '\0')
        ps++;

    while(*pt != '\0')
        pt++;

    ps--;
    pt--;

    i = 0;
    len = pt - t;
    
    while(*ps == *pt && i <= len)
    {
        printf("*ps = %c, *pt = %c, i = %d, len = %d\n", *ps, *pt, i, len);
        i++;
        ps--;
        pt--;
    }

    printf("*ps = %c, *pt = %c, i = %d, len = %d\n", *ps, *pt, i, len);
    if (i == len + 1)
        return 1;
    else
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
