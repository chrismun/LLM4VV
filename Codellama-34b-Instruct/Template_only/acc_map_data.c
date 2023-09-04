#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Create a data array
    int data[10];
    for (int i = 0; i < 10; i++) {
        data[i] = rand() % 100;
    }

    // Map the data array to the device
    #pragma acc map(data)

    // Perform some operations on the data array
    for (int i = 0; i < 10; i++) {
        data[i] += 1;
    }

    // Unmap the data array from the device
    #pragma acc unmap(data)

    // Check the results
    for (int i = 0; i < 10; i++) {
        if (data[i] != i + 1) {
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