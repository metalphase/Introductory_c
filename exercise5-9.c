#include <stdio.h>
#include <string.h>


static char daytab[2][13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

// index = leap*13 + month + 1

int day_of_year(char *pdaytab,int year, int month, int day);
void month_day(char *pdaytab, int year, int yearday, int *pmonth, int *pday);

/* Rewrite the routines day_of_year and month_day with pointers instead of 
indexing */
int main()
{   
    /*
    char daytab2[2][13] = {
        {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
        {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
    };  
    
    char *pdaytab;
    pdaytab = &(daytab2[0][0]);

    printf("Testing pointer operations\n");
    
    printf("daytab[%d][%d] = %d\n", 0, 0, daytab2[0][0]);
    printf("%d\n", *pdaytab);
    printf("%d\n", *(pdaytab+1));
    printf("%d\n", *(pdaytab+13+4));
    */

    /* Testing day_of_year */
    char *pdaytab = &(daytab[0][0]);
    printf("------------------------------------------------------------------\n");
    printf("Year: %d, Month: %d, Day: %d, Day of Year: %d\n", 2021, 2, 40, day_of_year(pdaytab, 2021, 2, 40));
    printf("Year: %d, Month: %d, Day: %d, Day of Year: %d\n", 2021, 22, 10, day_of_year(pdaytab, 2021, 22, 10)); 
    printf("Year: %d, Month: %d, Day: %d, Day of Year: %d\n", 2021, 2, 29, day_of_year(pdaytab, 2021, 2, 29)); 
    printf("Year: %d, Month: %d, Day: %d, Day of Year: %d\n", 2021, 2, 28, day_of_year(pdaytab, 2021, 2, 28)); 
    printf("Year: %d, Month: %d, Day: %d, Day of Year: %d\n", 2021, 2, 1 , day_of_year(pdaytab, 2021, 2, 1));
    printf("Year: %d, Month: %d, Day: %d, Day of Year: %d\n", 2021, 1, 20, day_of_year(pdaytab, 2021, 1, 20));
    printf("Year: %d, Month: %d, Day: %d, Day of Year: %d\n", 1992, 8, 21, day_of_year(pdaytab, 1992, 8, 21));

    int day; 
    int month;
    
    /* Testing month_day */
    printf("------------------------------------------------------------------\n");
    month_day(pdaytab, 2021, 20, &month, &day);
    printf("Year: %d, Yearday: %d, Month: %d, Day: %d\n", 2021, 20, month, day);
    
    month_day(pdaytab, 2021, 50, &month, &day);
    printf("Year: %d, Yearday: %d, Month: %d, Day: %d\n", 2021, 50, month, day);

    month_day(pdaytab, 2021, 400, &month, &day);
    printf("Year: %d, Yearday: %d, Month: %d, Day: %d\n", 2021, 400, month, day);


    month_day(pdaytab, 2021, 365, &month, &day);
    printf("Year: %d, Yearday: %d, Month: %d, Day: %d\n", 2021, 356, month, day);

    return 0;
}
/* day_of_year: set day of year from month & day */
int day_of_year(char *pdaytab, int year, int month, int day)
{   
    /* check that the month is a valid number */
    if (month <= 0 || month > 12)
    {
        printf("month value, %d, is invalid.\n", month);
        return -1;
    }

    int i, leap;

    leap = year%4 == 0 && year%100 != 0 || year%400 == 0;
    
    /* check if day is a valid number */
    if (day > *(pdaytab+ leap*13 + month) || day < 0)
    {
        printf("Value for day is invalid for month: %d\n", month);
        return -1;
    }

    for (i =  1; i < month; i++)
        day += *(pdaytab + leap*13 + i);
    return day;
}

/* month_day: set day of year from month & day */
void month_day(char *pdaytab, int year, int yearday, int *pmonth, int *pday)
{
    if(yearday > 365)
    {
        *pmonth = -1;
        *pday = -1;

        printf("yearday is invalid, use values from 0 to 365");
    }
    else
    {
        int i, leap;

        leap = year%4 == 0 && year%100 != 0 || year%400 == 0;
        for (i = 1; yearday > *(pdaytab+ leap*13 + i); i++)
            yearday -= *(pdaytab+ leap*13 + i);
        *pmonth = i;
        *pday = yearday;
    }
}