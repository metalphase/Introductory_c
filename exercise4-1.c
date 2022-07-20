#include <stdio.h>

/* Write the function strrindex(s,t), which returns the position of the 
rightmost occurence of t in s, or -1 if there is none */
int strrindex(char s[], char t[]);

// Prototype function which checks the index of t in s, however checks for
// the leftmost occurence of t in s.
int strindex(char s[], char t[]);

int main()
{   
    char t[] = "ould"; /* pattern to search for*/
    char s[] = "This should be a good example of a sentence with many \
                incidences of 'ould'. The program would find the latest \
                occurence of 'ould'. It should find this one in this sentence!";
    char s2[] = "The algorithm should find the 'ould' <- here.";
    char s3[] = "ould ould ould ould ould";
    char s4[] = "Will it find an occurence here?";

    // -------------------------------------------------------------------//
    int last_occurence = strrindex(s, t);
    printf("%d\n", last_occurence);

    if (last_occurence > 0)
        for(int i = last_occurence; s[i] != '\0'; i++)
            putchar(s[i]);
    else
        printf("Couldn't find an occurence");

    putchar('\n');

    // -------------------------------------------------------------------//
    putchar('\n');

    last_occurence = strrindex(s2, t);
    printf("%d\n", last_occurence);

    if (last_occurence > 0)
        for(int i = last_occurence; s2[i] != '\0'; i++)
            putchar(s2[i]);
    else
        printf("Couldn't find an occurence");

    putchar('\n');

    // -------------------------------------------------------------------//
    putchar('\n');

    last_occurence = strrindex(s3, t);
    printf("%d\n", last_occurence);

    if (last_occurence > 0)
        for(int i = last_occurence; s3[i] != '\0'; i++)
            putchar(s3[i]);
    else
        printf("Couldn't find an occurence");
    putchar('\n');

    // -------------------------------------------------------------------//
    putchar('\n');

    last_occurence = strrindex(s4, t);
    printf("%d\n", last_occurence);

    if (last_occurence > 0)
        for(int i = last_occurence; s4[i] != '\0'; i++)
            putchar(s4[i]);
    else
        printf("Couldn't find an occurence");
    putchar('\n');

    return 0;
}

int strindex(char s[], char t[])
{
    int i, j, k;

    for (i = 0; s[i] != '\0'; i++)
    {
        for (j=i, k=0; t[k]!='\0' && s[j]==t[k]; j++, k++)
            ;
        if (k > 0 && t[k] == '\0')
            return i;
    }
    return -1;
}

int strrindex(char s[], char t[])
{
    int i, j, k, last_pos;

    last_pos = -1;
    for (i = 0; s[i] != '\0'; i++)
    {
        for (j=i, k=0; t[k]!='\0' && s[j]==t[k]; j++, k++)
            ;
        if (k > 0 && t[k] == '\0')
            last_pos = i;
    }
    return last_pos;


    return -1;
}
