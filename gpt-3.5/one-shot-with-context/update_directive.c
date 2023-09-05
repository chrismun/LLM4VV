#include "acc_testsuite.h"

#define SIZE 1024

#ifndef T1
//T1:update,loop,construct-independent,construct-independent,V:2.0+,E:file-acc-update
int test1()
{
    int err = 0;

    int *a = (int *)malloc(SIZE * sizeof(int));
    int *b = (int *)malloc(SIZE * sizeof(int));
    int *c = (int *)malloc(SIZE * sizeof(int));
    int *d = (int *)malloc(SIZE * sizeof(int));

    for (int i = 0; i < SIZE; ++i)
    {
        a[i] = i;
        b[i] = i;
        c[i] = 0;
        d[i] = 0;
    }

#pragma acc data copyin(a[0:SIZE], b[0:SIZE]) copy(c[0:SIZE]) copyout(d[0:SIZE])
    {
#pragma acc update self(a[0:SIZE]) async(1)
#pragma acc update device(b[0:SIZE]) async(2)
#pragma acc update host(c[0:SIZE]) async(3) wait(1)
#pragma acc update device(c[0:SIZE]) async(4) wait(2)
#pragma acc update self(d[0:SIZE]) async(5) wait(3,4)
    }

    for (int i = 0; i < SIZE; ++i)
    {
        if (c[i] != a[i] || d[i] != b[i])
        {
            err += 1;
            break;
        }
    }

    free(a);
    free(b);
    free(c);
    free(d);

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
        failcode = failcode + (1 << 0);
    }
#endif

    return failcode;
}