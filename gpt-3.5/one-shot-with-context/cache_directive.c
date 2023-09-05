#include "acc_testsuite.h"

#ifndef T1
// T1: kernel data cache // different loop structure is tested in kernel loop directive testing 
int test1()
{
    int fail = 0;
    int i, a[100], b[100];
    for (i = 0; i < 100; ++i)
    {
        a[i] = i;
        b[i] = 0;
    }

    #pragma acc data copyin(a[0:100]) copyout(b[0:100])
    {
        #pragma acc parallel loop cache(a[0:50])
        for (i = 0; i < 100; ++i)
        {
            b[i] = a[i];
        }
    }

    for (i = 0; i < 100; ++i)
    {
        if (b[i] != a[i])
        {
            fail = 1;
        }
    }

    return fail;
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