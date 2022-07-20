#include <stdio.h>
#include <time.h>

/* binsearch: find x in v[0] <= v[1] <= ... <= v[n-1] */
int binsearch(int x, int v[], int n);
int binsearch_2(int x, int v[], int n);

#define MATRIX_SIZE 10000
/* Our binary search makes two tests inside the loop, when one would suffice
(at the price of more tests outside). Write a version with only one test 
inside the loop and measure the difference in run-time. */
int main()
{   
    int sorted_array[MATRIX_SIZE];

    for(int i = 0; i < MATRIX_SIZE; i++)
        sorted_array[i] = (2 * i);

    int value = 1024;

    clock_t begin_1 = clock();
    int position = binsearch(value, sorted_array, MATRIX_SIZE); 
    clock_t end_1 = clock();

    clock_t begin_2 = clock();
    int position_2 = binsearch_2(value, sorted_array, MATRIX_SIZE); 
    clock_t end_2 = clock();

    double time_spent_1 = (double)(end_1 - begin_1) / CLOCKS_PER_SEC;
    double time_spent_2 = (double)(end_2 - begin_2) / CLOCKS_PER_SEC;

    printf("Using base algorithm, position of value %d: %d, v[position] has value: %d, found in %f seconds\n", value, position, sorted_array[position], time_spent_1 );
    printf("Using new algorithm,  position of value %d: %d, v[position] has value: %d, found in %f seconds\n", value, position_2, sorted_array[position_2], time_spent_2);

    return 0;
}

int binsearch(int x, int v[], int n)
{
    int low, high, mid;

    low = 0;
    high = n - 1;
    while (low <= high)
    {   
        mid = (mid+high) / 2;
        if (x < v[mid])
            high = mid - 1;
        else if (x > v[mid])
            low = mid + 1;
        else /* found match */
            return mid;

    }
    return -1; /* no match */
}

int binsearch_2(int x, int v[], int n)
{
    int low, high, mid;

    low = 0;
    high = n;
    while (low < high)
    {   
        // recalculate the mid point from both high and low
        mid = low + ((high - low) / 2);

        // If the value at mid is less than our value x, then we
        // raise low to the new value at mid + 1
        if (v[mid] < x)
            low = mid + 1;
        // otherwise, if the value at mid is larger than our value x,
        // then we set high to mid.
        else
            // we cannot set it to mid - 1 since the opposite of v[mid] < x
            // is the scenario where v[mid] >= x
            high = mid;
    }
    // Pressumaby, the loop ends once low == high or low > high
    // We check that low is still within the bounds of the sorted array
    // and we check that the value of v[low] is equal to x, otherwise we
    // return -1.
    if ((low < n) && (v[low] == x))
        return low; // found a solution
    else
        return -1; // no solution found
}