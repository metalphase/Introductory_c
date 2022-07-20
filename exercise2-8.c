#include <stdio.h>
#include <math.h>
#include <limits.h>
#include <stdlib.h>

unsigned rightrot(unsigned x, int n);

/* Write a function rightrot(x,n) that returns the value of the integer
x rotated to the right by n bit positions */
int main()
{ 
    printf("%d\n", rightrot(128, 8));

    return 0;
}

unsigned rightrot(unsigned x, int n)
{   
    // If our number is 1 then we want to cycle back to the largest 
    // representable integer on the machine
    if (x == 1)
    {   
        // Set x to the largest possible unsigned int
        x = ~0;

        // After dividing by 2 once, we continue by dividing by 2
        // n-1 times
        for (int i = 0; i < n-1; i++)
            x = x / 2;
    }
    else
    {   
        // We divide by 2 n times but we check if we have reached 1 
        // with remaining divisions by 2 so that we set x back to the 
        // largest unsigned integer.
        for (int i = 0; i < n; i++)
        {
            if ((x == 1) && (i < n))
                x = ~0;
            
            x = x / 2;
        }

    }

    return x;
}