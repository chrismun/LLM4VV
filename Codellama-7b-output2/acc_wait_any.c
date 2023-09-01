#include "acc_testsuite.h"
#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Create a data region that will be used by the wait any directive
    int data[10];
    for (int i = 0; i < 10; i++) {
        data[i] = rand();
    }

    // Create a kernel that will be executed by the wait any directive
    int kernel[10];
    for (int i = 0; i < 10; i++) {
        kernel[i] = rand();
    }

    // Create a wait any directive that will wait for any of the kernel to complete
    #pragma acc wait any(kernel)

    // Check if the wait any directive has completed
    if (kernel[0] != 0) {
        err = 1;
    }

    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed;
#ifndef T1
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}