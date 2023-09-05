#include <stdio.h>
#include <stdlib.h>

int main()
{
    int size = 1024;
    float *a = (float *)malloc(size * sizeof(float));
    float *b = (float *)malloc(size * sizeof(float));

    // Initialize the data  
    for(int i=0; i<size; i++)
    {
        a[i] = i * 1.0f;
        b[i] = 0;
    }

    // Compute on the GPU, num_gangs gives the number of gangs.
    #pragma acc parallel num_gangs(512) copyin(a[0:size]) copyout(b[0:size])
    {
        #pragma acc loop gang
        for(int i=0; i<size; i++)
        {
            b[i] = a[i] * 2.0f;
        }
    }

    // Checking the results on host
    for(int i=0; i<size; i++)
    {
        if (b[i] != i*2.0f)
        {
            printf("Result error at index %d, expected %f, found %f\n", i, i*2.0f, b[i]);
            exit(1);
        }
    }

    printf("Test PASSED\n");
    // Free memory
    free(a);
    free(b);

    return 0;
}