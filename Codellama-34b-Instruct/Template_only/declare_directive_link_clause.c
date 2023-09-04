#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Declare a variable that will be used to store the result of the link clause
    int result;

    // Use the link clause to link the variable to a specific device
    #pragma acc declare link(result) device(device_type)

    // Use the device to perform some computation
    #pragma acc parallel loop device(device_type)
    for (int i = 0; i < N; i++) {
        result += i;
    }

    // Check the result
    if (result != N * (N - 1) / 2) {
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