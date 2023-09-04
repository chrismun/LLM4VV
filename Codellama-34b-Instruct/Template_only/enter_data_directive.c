#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Create a data array
    int data[10];

    // Initialize the data array with random values
    for (int i = 0; i < 10; i++) {
        data[i] = rand();
    }

    // Enter the data array into the OpenACC runtime
    acc_enter_data(data, 10, 10);

    // Verify that the data array is now accessible on the device
    for (int i = 0; i < 10; i++) {
        if (data[i] != acc_get_data(i)) {
            err = 1;
            break;
        }
    }

    // Exit the data array from the OpenACC runtime
    acc_exit_data(data, 10, 10);

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