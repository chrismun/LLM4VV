#include <stdio.h>
#include <stdlib.h>
#include "acc_testsuite.h"

#ifndef T1
#define T1 1
// T1: {routine}, V:2.7-3.3
int test1() {
    int err = 0;
    int host_data = 5;
    int device_data = 0;

    // A function meant only for accelerator
    #pragma acc routine seq nohost
    void accelerator_only_function(int *data) {
        *data += 5; // Some operation
    }

    // Binding function for host, calling the accelerator function with bind
    #pragma acc routine seq bind(accelerator_only_function)
    void bound_function(int *data) {
        // This is a dummy placeholder to check bind clause functionality.
    }

    // Execution
    #pragma acc data copy(device_data)
    {
        #pragma acc parallel
        {
            #pragma acc loop seq
            for(int i = 0; i < 1; ++i) {
                accelerator_only_function(&device_data); // Expected to run on device
            }
        }
    }

    // Checking whether the device operation was successful
    if (device_data != 5){
        err += 1;
    }

    // Attempting to call the bound function from host to see if it compiles or not.
    // Note: This code should not compile due to the 'nohost' clause on 'accelerator_only_function'.
    // bound_function(&host_data);

    return err;
}
#endif

int main() {
    int failcode = 0;

    int failed = test1();
    if (failed != 0) {
        failcode = failcode + (1 << 0);
        printf("Test1 failed with %d errors.\n", failed);
    } else {
        printf("Test1 passed.\n");
    }

    return failcode;
}