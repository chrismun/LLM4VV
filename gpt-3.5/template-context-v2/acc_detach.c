#include "acc_testsuite.h"
#ifndef T1
// T1: acc detach, V:2.7-3.3
int test1()
{
    int err = 0;
    srand(SEED);

    int N = 1000;
    int *a, *b, *c;

    a = (int *)malloc(N * sizeof(int));
    b = (int *)malloc(N * sizeof(int));
    c = (int *)malloc(N * sizeof(int));

    // Initialize arrays
    for (int i = 0; i < N; i++)
    {
        a[i] = rand() % 100;
        b[i] = rand() % 100;
    }

    // Compute c[i] = a[i] + b[i] on CPU
    for (int i = 0; i < N; i++)
    {
        c[i] = a[i] + b[i];
    }

    // Use OpenACC detach to offload computation to GPU
    #pragma acc parallel loop present(a, b, c)
    for (int i = 0; i < N; i++)
    {
        // detach here
        #pragma acc detach
        c[i] = a[i] + b[i];
    }

    // Compare results
    for (int i = 0; i < N; i++)
    {
        if (c[i] != (a[i] + b[i]))
        {
            err = 1;
            break;
        }
    }

    free(a);
    free(b);
    free(c);

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