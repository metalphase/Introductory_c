#include <stdio.h>

/* print Fahrenheit-Celsious table
    for fahr = 0, 20, ..., 300 */
main()
{
    float fahr, celsius;
    int lower, upper, step;


    printf("Fahrenheit to Celsius Conversion Table\n");
    printf("--------------------------------------\n");
    printf("   Fahrenheit    |\t Celsius\n");
    printf("--------------------------------------\n");
    for(fahr = 300; fahr >= 0; fahr = fahr - 20)
    {
        printf("\t %3.0f \t | \t %6.1f\n", fahr, (5.0/9.0) * (fahr-32.0));
    }
    
}

