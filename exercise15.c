#include <stdio.h>

int power(int m, int n);
void fahr_to_celc(float fahr);

/* test power function */
int main()
{
    int i, j;
    j = 0;

    for (i = 0; i < 10; ++i)
    {
        j = power(i, 2);
        fahr_to_celc(j);
    }
    return 0;
}

/* power:   raise base to n-th power; n >= 0 */
int power(int base, int n)
{
    int i, p;

    p = 1;
    for (i = 1; i <= n; ++i)
        p = p * base;
    return p;
}

void fahr_to_celc(float fahr)
{
    printf("\t %3.0f \t | \t %6.1f\n", fahr, (5.0/9.0) * (fahr-32.0));
}