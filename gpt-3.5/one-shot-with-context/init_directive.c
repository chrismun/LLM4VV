#include "acc_testsuite.h"

#ifndef T1
// T1: host+device init
int test1()
{
    int err = 0;

    // Initialize all available devices
    #pragma acc init

    // Perform computations on devices
    #pragma acc parallel loop
    for (int i = 0; i < 100; i++)
    {
        // Loop body
    }

    // Shutdown all devices before exiting
    #pragma acc shutdown

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