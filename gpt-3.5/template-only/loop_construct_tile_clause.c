#include "acc_testsuite.h"

#ifndef T1

#define WIDTH 1024
#define HEIGHT 1024

// T1:runtime, data, executable-data, construct-independent, V:2.0-2.7
int test1()
{
    int err = 0;
    int i, j;

    // Allocate memory for the input and output arrays
    float *input = (float *)malloc(WIDTH * HEIGHT * sizeof(float));
    float *output = (float *)malloc(WIDTH * HEIGHT * sizeof(float));

    // Initialize the input array
    for (i = 0; i < WIDTH * HEIGHT; i++)
    {
        input[i] = (float)(i);
    }

    // Compute the output array using the OpenACC loop construct tile clause
    #pragma acc parallel loop tile(32,32)
    for (i = 0; i < HEIGHT; i++)
    {
        for (j = 0; j < WIDTH; j++)
        {
            output[i * WIDTH + j] = input[i * WIDTH + j];
        }
    }

    // Verify the output array
    for (i = 0; i < WIDTH * HEIGHT; i++)
    {
        if (output[i] != input[i])
        {
            err = 1;
            break;
        }
    }

    // Free the memory
    free(input);
    free(output);

    return err;
}

#endif

int main()
{
    int failcode = 0;
    int failed;

#ifndef T1
    failed = 0;

    for (int x = 0; x < NUM_TEST_CALLS; ++x)
    {
        failed += test1();
    }

    if (failed != 0)
    {
        failcode = failcode | (1 << 0);
    }
#endif

    return failcode;
}