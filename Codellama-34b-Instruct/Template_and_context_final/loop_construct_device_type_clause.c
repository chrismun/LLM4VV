#include "acc_testsuite.h"

#ifndef T1
//T1:loop construct device_type clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    // Create a device_type clause for the loop construct
    #pragma acc loop device_type(gpu)
    for (int i = 0; i < 10; i++) {
        // Do some work on the GPU
        #pragma acc parallel loop device_type(gpu)
        for (int j = 0; j < 10; j++) {
            // Do some work on the GPU
        }
    }

    // Check that the device_type clause was correctly applied
    #pragma acc loop device_type(cpu)
    for (int i = 0; i < 10; i++) {
        // Do some work on the CPU
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