#include "acc_testsuite.h"
#ifndef T1
// T1: shutdown directive, V: 2.7-3.3
int test1() {
    int err = 0;

    // Code block to be executed on the accelerator
    #pragma acc parallel shutdown
    {
        // Perform some computations on the accelerator
        // ...

        // Use the shutdown directive to explicitly terminate the accelerator region
    }

    // Code block to be executed on the host
    // ...

    #pragma acc wait

    // Verify if the shutdown directive was properly executed
    if (acc_on_device(acc_device_default) != 0) {
        err = 1;
    }

    return err;
}
#endif

int main() {
    int failcode = 0;
    int failed;
#ifndef T1
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed = failed + test1();
    }
    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}