#include <stdio.h>

#define IN 1
#define OUT 0
#define MAXSTRINGSIZE 40
/* count lines, words, and characters in input */
int main()
{
    // Initialize length histogram
    // Make assumption that our words are at most characters long.
    int len_histogram[MAXSTRINGSIZE];

    for (int i = 0; i < MAXSTRINGSIZE; ++i)
        len_histogram[i] = 0;


    // Count the length of each word

    int c, state, word_length;
    
    state = OUT;
    word_length = 0; 

    while ((c = getchar()) != EOF)
    {   
        if (c == ' ' || c == '\n' || c == '\t')
        {
            // Assign to array
            if (word_length != 0)
            {
                len_histogram[word_length] = len_histogram[word_length] + 1;
                word_length = 0;
            }
            
            state = OUT;
        }
        else if (state == OUT)
        {
            state = IN;
            ++word_length;
        }
        else
        {
            ++word_length;
        }
    }

    
    // Display the histogram
    for (int i = 0; i < MAXSTRINGSIZE; ++i)
    {
        printf("i = %2d :", i);
        for (int j = 0; j < len_histogram[i]; ++j)
            putchar('-');
        putchar('\n');

    }
    return 0;
}