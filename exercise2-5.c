#include <stdio.h>
#include <stdbool.h>

/* Write the function any(s1, s2), which returns the first location in 
the string s1 where any character from the string s2 occurs, or -1 if 
s1 contains no characters from s2 */
int any(char s1[], char s2[]);

int main()
{
    char s1[100] = "This is an example of a sentence";
    char s2[100] = "T";

    printf("%d\n", any(s1, s2));
    return 0;
}

int any(char s1[], char s2[])
{
    bool found_same_char = false;
    int s1_i = 0;

    for (s1_i = 0; (s1[s1_i] != '\0') && (found_same_char == false); s1_i++)
    {
        int s2_j;
        for (s2_j = 0; s2[s2_j] != '\0'; s2_j++)
        {
            if(s1[s1_i] == s2[s2_j])
                found_same_char = true;
        }
    }

    if(found_same_char)
        return s1_i;
    
    return -1;
}