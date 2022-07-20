#include <stdio.h>
#include <string.h>

static char daytab[2][13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

int day_of_year(int year, int month, int day);
void month_day(int year, int yearday, int *pmonth, int *pday);

/* There is no error checking in day_of_year or momth_day. Remedy this defect */
int main()
{
    /* Testing day_of_year */
    printf("------------------------------------------------------------------\n");
    printf("Year: %d, Month: %d, Day: %d, Day of Year: %d\n", 2021, 2, 40, day_of_year(2021, 2, 40));
    printf("Year: %d, Month: %d, Day: %d, Day of Year: %d\n", 2021, 22, 10, day_of_year(2021, 22, 10)); 
    printf("Year: %d, Month: %d, Day: %d, Day of Year: %d\n", 2021, 2, 29, day_of_year(2021, 2, 29)); 
    printf("Year: %d, Month: %d, Day: %d, Day of Year: %d\n", 2021, 2, 28, day_of_year(2021, 2, 28)); 
    printf("Year: %d, Month: %d, Day: %d, Day of Year: %d\n", 2021, 2, 1 , day_of_year(2021, 2, 1));
    printf("Year: %d, Month: %d, Day: %d, Day of Year: %d\n", 2021, 1, 20, day_of_year(2021, 1, 20));
    printf("Year: %d, Month: %d, Day: %d, Day of Year: %d\n", 1992, 1, 20, day_of_year(1992, 8, 21));

    int day; 
    int month;

    /* Testing month_day */
    printf("------------------------------------------------------------------\n");
    month_day(2021, 20, &month, &day);
    printf("Year: %d, Yearday: %d, Month: %d, Day: %d\n", 2021, 20, month, day);
    
    month_day(2021, 50, &month, &day);
    printf("Year: %d, Yearday: %d, Month: %d, Day: %d\n", 2021, 50, month, day);

    month_day(2021, 400, &month, &day);
    printf("Year: %d, Yearday: %d, Month: %d, Day: %d\n", 2021, 400, month, day);


    month_day(2021, 365, &month, &day);
    printf("Year: %d, Yearday: %d, Month: %d, Day: %d\n", 2021, 356, month, day);

    return 0;
}
/* day_of_year: set day of year from month & day */
int day_of_year(int year, int month, int day)
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
    if (day > daytab[leap][month] || day < 0)
    {
        printf("Value for day is invalid for month: %d\n", month);
        return -1;
    }

    for (i =  1; i < month; i++)
        day += daytab[leap][i];
    return day;
}

/* month_day: set day of year from month & day */
void month_day(int year, int yearday, int *pmonth, int *pday)
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
        for (i = 1; yearday > daytab[leap][i]; i++)
            yearday -= daytab[leap][i];
        *pmonth = i;
        *pday = yearday;
    }
}