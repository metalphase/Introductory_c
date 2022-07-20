#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_STRING_LENGTH 10000
/* Write a function expand(s1, s2) that expands shorthand notations 
like a-z in the string s1 into the equivavlent complete list abc...xyz in s2.
Allow for letters of either case and digits, and be prepared to handle cases 
like a-b-c and a-z0-9 and -a-z. Arrange that a leading or trailing - is taken
literally. */
void expand(char s1[], char s2[]);

int main()
{  
    char s1[] = "this is a a-z sentence with b-z a s-t p-z - p- l-a expandable section";
    char s2[MAX_STRING_LENGTH];
    
    expand(s1,s2);
    for(int i = 0; s2[i] != '\0'; i++)
        putchar(s2[i]);
        
    putchar('\n');
    return 0;
}

void expand(char s1[], char s2[])
{
    int i, j;

    i = 0;
    j = 0;
    while(s1[i] != '\0')
    {
        if(s1[i] != '-')
        {
            s2[j] = s1[i];
            i++;
            j++;
        }
        else
        {
            if(s1[i+1] != '\0')
            {
                char c_before, c_after;

                c_before = s1[i-1];
                c_after  = s1[i+1];

                bool c_before_is_alpha = ((c_before >= 'a' && c_before <= 'z') || (c_before >= 'A' && c_before <= 'Z'));
                bool c_after_is_alpha  = ((c_after >= 'a' && c_after <= 'z') || (c_after >= 'A' && c_after <= 'Z'));

                // check if alphabetical
                if (c_before_is_alpha && c_after_is_alpha)
                {
                    // if they are alphabetical, then check if c_before is 
                    // alphetically before c_after
                    if (c_before < c_after)
                    {
                        // Loop over the char integers between c_before and
                        // c_after and store them in s2[j]
                        for (char c=c_before+1;c<=c_after;c++)
                        {
                            s2[j] = c;
                            j++;
                        }

                        // Increment i by one so that we are at s[j+1]
                        i++;
                    }
                    // If c_before does not come before c_after then we just 
                    // place the current '-' in s2[j]
                    else
                    {
                        s2[j] = s1[i];
                        j++;
                    }
                }
                // If only one of c_before and c_after are alphatical or 
                // neither are alphabetical, we store '-' at s2[j]
                else
                {
                    s2[j] = s1[i];
                    j++;
                }
                
                // Increment i by one
                i++;
            }
            else
            {
                s2[j] = s1[i];
                j++;
                i++;
            }
        }
    }
}
    
    