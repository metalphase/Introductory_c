#include <stdio.h>
#include <stdbool.h>

#define MAX_LENGTH 1000
/* write an alternate version of squeeze(s1,s2) that deletes each charater 
in s1 that matches any character in the string s2*/
void squeeze(char s[], int c);
void squeeze2(char s1[], char s2[]);

int main()
{
    char s1[100] = "characterization";
    char s2[100] = "abcdefghijklmnopqrstuvwxyz";

    squeeze2(s1, s2);
    printf("%s\n", s1);
    return 0;
}

void squeeze(char s[], int c)
{
    int i, j;

    for (i = j = 0; s[i] != '\0'; i++)
        if (s[i] != c)
            s[j++] = s[i];
    s[j] = '\0';
}


void squeeze2(char s1[], char s2[])
{   
    int s1_i = 0;
    int squeezed_s1_i = 0;

    while (s1[s1_i] != '\0')
    {   
        int s2_i = 0;
        bool no_common_chars = true;

        while ((s2[s2_i] != '\0'))
        {
            if (s1[s1_i] == s2[s2_i])
                no_common_chars = false;

            s2_i++;
        }

        if(no_common_chars)
        {
            s1[squeezed_s1_i] = s1[s1_i];
            ++squeezed_s1_i;
        }

        s1_i++;    
    }   

    for(int i = squeezed_s1_i; s1[i] != '\0'; i++)
    {
        s1[i] = '\0';
    }
}   
