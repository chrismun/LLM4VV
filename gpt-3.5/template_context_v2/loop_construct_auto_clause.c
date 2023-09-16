#include "acc_testsuite.h"
#ifndef T1
// T1: loop construct auto clause, V: 2.7-3.3
int test1()
{
    int err = 0;

    // Initialize variables and arrays
    int N = 100;
    int *a = (int *)malloc(N * sizeof(int));
    int *b = (int *)malloc(N * sizeof(int));
    int *c = (int *)malloc(N * sizeof(int));

    // Populate arrays with random values
    for (int i = 0; i < N; i++)
    {
        a[i] = rand() % 100;
        b[i] = rand() % 100;
    }

    // Perform vector addition using OpenACC
    #pragma acc parallel loop auto
    for (int i = 0; i < N; i++)
    {
        c[i] = a[i] + b[i];
    }

    // Verify the results
    for (int i = 0; i < N; i++)
    {
        if (c[i] != a[i] + b[i])
        {
            err = 1;
            break;
        }
    }

    // Free memory
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