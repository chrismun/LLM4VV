#include <stdlib.h>
#include <openacc.h>
#include <assert.h>

// Size of vectors
#define N 10000

// Vector addition kernel
#pragma acc routine
void add(int n, float *x, float *y, float *z)
{
    #pragma acc loop
    for (int i = 0; i < n; i++)
        z[i] = x[i] + y[i];
}

int main()
{
    float *x, *y, *z;
    
    // Allocate and initialize device memory
    x = (float*)malloc(N * sizeof(float));
    y = (float*)malloc(N * sizeof(float));
    z = (float*)malloc(N * sizeof(float));
    
    // Initialize vectors
    for (int i = 0; i < N; i++)
    {
        x[i] = rand();
        y[i] = rand();
        z[i] = 0;
    }
    
    // Start computation asynchronously on two different queues
    #pragma acc parallel loop async(0)
    for (int i = 0; i < N/2; i++)
        z[i] = x[i] + y[i];
    
    #pragma acc parallel loop async(1)
    for (int i = N/2; i < N; i++)
        z[i] = x[i] + y[i];
    
    // Wait until both queues have finished computation
    #pragma acc wait

    // Check correctness
    for (int i = 0; i < N; i++)
        assert(z[i] == x[i] + y[i]);
    
    free(x);
    free(y);
    free(z);
    
    return 0;
}