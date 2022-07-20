#include <stdio.h>

#define NUMCHARS 126

/* count the frequency of each character within the text input */
int main()
{
    // Initialize length histogram
    // Make assumption that our words are at most characters long.
    int freq_histogram[NUMCHARS];

    for (int i = 0; i < NUMCHARS; ++i)
        freq_histogram[i] = 0;


    // Count the length of each word

    int c;

    while ((c = getchar()) != EOF)
    {   
        ++freq_histogram[c];
    }

    // Display the histogram
    
    for (int i = 0; i < NUMCHARS; ++i)
    {
        printf("i = %2d :", i);
        for (int j = 0; j < freq_histogram[i]; ++j)
            putchar('-');
        putchar('\n');
    }


    return 0;
}