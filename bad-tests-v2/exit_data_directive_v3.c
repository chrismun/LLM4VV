#include <stdlib.h>
#include <stdio.h>
#include <openacc.h>
#include <stdbool.h>

#define N 100
#define TOL 1.0e-6

void init(float* a, int n) 
{
    for (int i = 0; i < n; i++)
        a[i] = (float)(1.0 * rand() / RAND_MAX);
}

bool check(float* a, float* b, int n) 
{
    for (int i = 0; i < n; i++)
        if (abs(a[i] - b[i]) > TOL) return false;
    
    return true;
}

int main() 
{
    float *a = (float*) malloc(N * sizeof(float));
    float *a_copy = (float*) malloc(N * sizeof(float));
    
    init(a, N);

    // Make a copy of data
    for (int i = 0; i < N; i++)
        a_copy[i] = a[i];

    // Enter data, copy in
    #pragma acc enter data copyin(a[0:N])

    // Parallel region
    #pragma acc parallel loop
    for (int i = 0; i < N; i++) {
        a[i] = a[i] * 2.0f;
    }

    // Exit data, copy out
    #pragma acc exit data copyout(a[0:N])

    // CPU calculation
    for (int i = 0; i < N; i++)
        a_copy[i] = a_copy[i] * 2.0f;

    // Verify if GPU results are equivalent to CPU results
    if (check(a, a_copy, N))
        printf("Verification: Passed\n");
    else
        printf("Verification: Failed\n");

    // Free memory
    free(a);
    free(a_copy);

    return 0;