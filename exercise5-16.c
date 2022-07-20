#include <stdio.h>
#include <ctype.h>
#include <stdlib.h> /* for atof() */


/* Modify the programs entab and detab (written as exercises in Chapter 1) 
to accept a list of tab stops as arguments. Use the default tab settings if
there are no arguments */
int main(int argc, char *argv[])
{   

    int column_start = 0;
    int stops_after_n_columns = 0;

    if(argc >= 3)
    {
        column_start = -1*atoi(argv[1]);
        stops_after_n_columns = -1*atoi(argv[2]);
    }

    printf("m = %d\n", column_start);
    printf("n = %d\n", stops_after_n_columns);
    
    return 0;
}
