#include <stdio.h>
#include <openacc.h>

#define SIZE 1024

int main()
{
    float a[SIZE];
    float b[SIZE];

    // Initialize Array
    for (int i = 0; i < SIZE; i++)
    {
        a[i] = (float)i;
        b[i] = 0;
    }

    #pragma acc data copyin(a) copyout(b)
    {
        #pragma acc parallel
        {
            #pragma acc loop gang
            for (int i = 0; i < SIZE; i++)
            {
                b[i] = a[i]*2.0f;
            }
        }
    }

    // Check Results
    for (int i = 0; i< SIZE; i++)
        if (b[i] != i * 2.0f) {
            printf("Error at position %d\n", i);
            return 1;
        }

    printf("Test passed successfully!\n");
    return 0;