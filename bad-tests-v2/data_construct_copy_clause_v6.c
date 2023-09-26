#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Create a data array
    int data[10];
    for (int i = 0; i < 10; i++) {
        data[i] = rand();
    }

    // Copy the data array to the device
    #pragma acc enter data copyin(data[:10])

    // Modify the data array on the device
    #pragma acc parallel loop
    for (int i = 0; i < 10; i++) {
        data[i] += 1;
    }

    // Copy the modified data array back to the host
    #pragma acc exit data copyout(data[:10])

    // Check that the data array has been modified correctly
    for (int i = 0; i < 10; i++) {
        if (data[i] != rand() + 1) {
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