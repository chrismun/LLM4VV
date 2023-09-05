#include "acc_testsuite.h"
#ifndef T1
// T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1()
{
    int err = 0;
    srand(SEED);

    int *arr = (int *)malloc(N * sizeof(int));
    int *arr_copy = (int *)malloc(N * sizeof(int));

    // Initialize the array
    for (int i = 0; i < N; ++i)
    {
        arr[i] = rand() % 100;
    }

    // Copy the array to the GPU memory
    #pragma acc enter data copyin(arr[0:N])
    
    // Perform some operations on the GPU
    #pragma acc parallel loop
    for (int i = 0; i < N; ++i)
    {
        arr[i] *= 2;
    }

    // Copy the array back to the CPU memory
    #pragma acc exit data copyout(arr_copy[0:N])

    // Verify the correctness of the results
    for (int i = 0; i < N; ++i)
    {
        if (arr[i] * 2 != arr_copy[i])
        {
            err = 1;
            break;
        }
    }

    free(arr);
    free(arr_copy);

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
        failed = failed + test1();
    }
    if (failed != 0)
    {
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}