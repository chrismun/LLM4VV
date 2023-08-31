#include "acc_testsuite.h"

#ifndef T1
// T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1() {
    int err = 0;
    srand(SEED);

    // Create a data region that will be used by the wait directive
    int data[10];
    for (int i = 0; i < 10; i++) {
        data[i] = i;
    }

    // Create a kernel that will wait for the data region to be updated
    #pragma acc parallel num_gangs(1) num_workers(1) vector_length(10)
    {
        #pragma acc loop gang(1) worker(1) vector(10)
        for (int i = 0; i < 10; i++) {
            data[i] = data[i] + 1;
        }
    }

    // Use the wait directive to wait for the data region to be updated
    #pragma acc wait(data)

    // Check that the data region has been updated
    for (int i = 0; i < 10; i++) {
        if (data[i] != i + 1) {
            err = 1;
        }
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