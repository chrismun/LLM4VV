#include <stdio.h>
#include <openacc.h>

#define SIZE 10000
#define GANG_SIZE 512

int main()
{
    int data[SIZE];
    int i;
    
    // Initialize array
    for(i = 0; i < SIZE; i++)
        data[i] = i;
    
    #pragma acc parallel loop gang vector_length(GANG_SIZE)
    for(i = 0; i < SIZE; i++)
    {
        data[i] = data[i] + 1;
    }

    // Check results
    int error = 0;
    for(i = 0; i < SIZE; i++)
    {
        if(data[i] != i+1)
        {
            error = 1;
            printf("data[%d] = %d, expected %d\n", i, data[i], i+1);
            break;
        }
    }

    if(error)
        printf("FAILED\n");
    else
        printf("PASSED\n");

    return 0;
}