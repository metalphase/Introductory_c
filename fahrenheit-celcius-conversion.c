#include <stdio.h>

/* print Fahrenheit-Celsious table
    for fahr = 0, 20, ..., 300 */
main()
{
    float fahr, celsius;
    int lower, upper, step;

    lower = 0;
    upper = 300;
    step = 20;

    fahr = lower;

    printf("Fahrenheit to Celsius Conversion Table\n");
    printf("--------------------------------------\n");
    printf("   Fahrenheit    |\t Celsius\n");
    printf("--------------------------------------\n");
    while (fahr <= upper) {
        celsius = (5.0/9.0) * (fahr-32.0);
        printf("\t %3.0f \t | \t %6.1f\n", fahr, celsius);
        fahr = fahr + step;
    }

    /* Printing a Celsius to Fahrenheit Table*/
    /*float fahr2, celsius2;
    int lower, upper, step;*/

    lower = 0;
    upper = 150;
    step = 10;

    celsius = lower;

    printf("Celsius to Fahrenheit Conversion Table\n");
    printf("--------------------------------------\n");
    printf("    Celsius      |\t Fahrenheit\n");
    printf("--------------------------------------\n");
    while (celsius <= upper) {
        fahr = (9.0/5.0)*celsius + 32.0;
        printf("\t %3.0f \t | \t %6.1f\n", celsius, fahr);
        celsius = celsius + step;
    }
    
}

