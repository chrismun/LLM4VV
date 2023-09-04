#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Create a data array
    int data[10];

    // Initialize the data array
    for (int i = 0; i < 10; i++) {
        data[i] = i;
    }

    // Create a copy of the data array
    int data_copy[10];
    memcpy(data_copy, data, sizeof(data));

    // Create an OpenACC region with the async clause
    #pragma acc parallel async(data_copy)
    {
        // Perform some computation on the data array
        for (int i = 0; i < 10; i++) {
            data[i] = data[i] + 1;
        }
    }

    // Check that the data array has been updated correctly
    for (int i = 0; i < 10; i++) {
        if (data[i] != data_copy[i] + 1) {
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