#include <stdio.h>
#include <openacc.h> //OpenACC library

#define N 1000000
 
int main()
{   
    int i, errors = 0;
    float x[N];

    // Use device 1 for execution
    #pragma acc set device_num(1)
    #pragma acc parallel loop copy(x)
    for(i = 0; i < N; i++)
    {
        x[i] = (float)i;
    }

    // Check for errors
    for(i = 0; i < N; i++)
    {
        if(x[i] != (float)i)
        {
            errors++;
        }
    }

    if(errors > 0)
    {
        printf("The set directive test FAILED with %d errors.\n", errors);
    }
    else
    {
        printf("The set directive test PASSED successfully!\n");
    }
   
    return 0;
}