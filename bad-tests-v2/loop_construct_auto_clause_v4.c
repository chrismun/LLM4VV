#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    int num_devices = acc_get_num_devices(acc_device_default);
    int device_id = acc_get_device_id(acc_device_default);

    // Create a random number of iterations for the loop
    int num_iterations = rand() % 100;

    // Create a loop with the auto clause
    #pragma acc loop auto
    for (int i = 0; i < num_iterations; i++) {
        // Do some work
    }

    // Check that the loop was executed on the correct device
    if (acc_get_device_id(acc_device_default) != device_id) {
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