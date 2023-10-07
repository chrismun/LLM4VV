#include "acc_testsuite.h"

#ifndef T1
// T1: declare directive device_resident clause, V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    // Declare a variable on the device
    int *data;
    #pragma acc declare create(data)

    // Allocate memory for data on the device
    #pragma acc enter data create(data[100])

    // Perform some operations on the device data
    #pragma acc parallel loop present(data)
    for (int i = 0; i < 100; i++) {
        data[i] = i;
    }

    // Explicitly exit data region to free the device memory
    #pragma acc exit data delete(data)

    // Check if data was modified correctly
    for (int i = 0; i < 100; i++) {
        if (data[i] != i) {
            err = 1;
            break;
        }
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