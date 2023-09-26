// Test program for OpenACC declare directive with a link clause

#include <stdlib.h>
#include <stdio.h>
#include "openacc.h"

#ifndef N
#define N 100
#endif

// Declare a global variable
float x[N];

// Declare a link to the global variable on the accelerator
#pragma acc declare link(x)

int main()
{
    // Initialize the variable on the host
    for(int i = 0; i < N; i++)
    {
        x[i] = (float)rand()/(float)(RAND_MAX/100);
    }
        
    #pragma acc data copy(x)
    {
        // Perform computation on the accelerator
        #pragma acc kernels loop
        for(int i = 0; i < N; i++)
        {
            x[i] = x[i] * x[i];
        }
    }

    // Check results
    for(int i = 0; i < N; i++)
    {
        float expected = ((float)i * (float)i);
        if(x[i] != expected)
        {
            fprintf(stderr, "Error: x[%d] = %f, but expected = %f\n", i, x[i], expected);
            return 1;
        }
    }

    printf("OpenACC declare link test passed\n");
    return 0;
}