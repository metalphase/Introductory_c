#include <stdio.h>
#include <ctype.h>

/* atof: covert string s to double */
double atof(char s[]);
double atof2(char s[]);

/* Extend atof to handle scientific notation of the form 123.45e-6 */
int main()
{   
    char n_chars[] = "1.23456";
    double n_double;

    n_double = atof2(n_chars);
    printf("%f\n", n_double);

    n_double = atof2("123.45e-3");
    printf("%f\n", n_double);

    n_double = atof2("123.45e3");
    printf("%f\n", n_double);

    n_double = atof2("123456789.5e-10");
    printf("%f\n", n_double);

    n_double = atof2("123456789.5e10");
    printf("%f\n", n_double);

    n_double = atof2("1234567895e-10");
    printf("%f\n", n_double);

    return 0;
}

/* atof: convert string s to double */
double atof(char s[])
{
    double val, power;
    int i, sign;

    for (i = 0; isspace(s[i]); i++) /* skip white space */
        ;
    sign = (s[i] == '-') ? -1 : 1;
    if(s[i] == '+' || s[i] == '-')
        i++;
    for (val = 0.0; isdigit(s[i]); i++)
        val = 10.0 * val + (s[i] - '0');
    if (s[i] == '.')
        i++;
    for (power = 1.0; isdigit(s[i]); i++)
    {
        val = 10.0 * val + (s[i] - '0');
        power *= 10.0;
    } 
    return sign * val / power;
}

double atof2(char s[])
{
    double val, power;
    int i, sign, exp_sign, exp;

    for (i = 0; isspace(s[i]); i++) /* skip white space */
        ;

    // Get the sign of the input number
    sign = (s[i] == '-') ? -1 : 1;
    if(s[i] == '+' || s[i] == '-')
        i++;
    // Add each digit into val using the appropriate powers of 10
    for (val = 0.0; isdigit(s[i]); i++)
        val = 10.0 * val + (s[i] - '0');
    // If we encounter a decimal point, we increment our index by one
    if (s[i] == '.')
        i++;
    // We continue collecting numbers per usual, but our method of adding 
    // appropriate powers of ten must be offset for any values after the 
    // period, hence our variable power
    for (power = 1.0; isdigit(s[i]); i++)
    {
        val = 10.0 * val + (s[i] - '0');
        power *= 10.0;
    }
    // We now check that our next number is an exponential, e. Otherwise we 
    // return our value as in atof().
    if (s[i] == 'e')
    {   
        // We will store the exponent value in this variable
        double exp_value = 1.0;

        // We increment our index by one and extract the sign 
        i++;
        exp_sign = (s[i] == '-') ? -1 : 1;

        if (exp_sign == -1)
        {
            i++;
            for (exp = 0; isdigit(s[i]); i++)
                exp = 10 * exp + (s[i] - '0');

            for (int i = 0; i < exp; i++)
                exp_value /= 10.0;
        }
        else if (exp_sign == 1)
        {
            for (exp = 0; isdigit(s[i]); i++)
                exp = 10 * exp + (s[i] - '0');

            for (int i = 0; i < exp; i++)
                exp_value *= 10.0;
        }

        
        return (sign * val / power) * exp_value;
    }
    else
        return sign * val / power;
}