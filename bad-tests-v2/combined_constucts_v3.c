#include <stdio.h>
#include <stdlib.h>
#define N 1000000
#define ERR_THRESHOLD 0.001

int main()
{
    float *a = (float*)malloc(sizeof(float)*N);
    float *b = (float*)malloc(sizeof(float)*N);
    float total = 0.0;

    // Initialize arrays
    for(int i = 0; i < N; i++)
    {
        a[i] = (float)rand()/(float)(RAND_MAX);
        b[i] = (float)rand()/(float)(RAND_MAX);
    }

    // Multiply arrays in parallel
    #pragma acc parallel loop reduction(+:total)
    for(int i = 0; i < N; i++)
    {
        total += a[i] * b[i];
    }

    printf("Total: %f\n", total);

    // Verify result
    float expected_total = 0.0;
    for(int i = 0; i < N; i++)
    {
        expected_total += a[i] * b[i];
    }

    if(abs(total - expected_total) > ERR_THRESHOLD)
    {
        printf("Test failed! Expected %f but got %f\n", expected_total, total);
        return -1;
    }

    printf("Test passed!\n");
    return 0;
}