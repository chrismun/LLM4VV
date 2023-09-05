#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Initialize the device
    acc_init(acc_device_default);

    // Create a data array on the device
    int *data;
    acc_malloc(data, sizeof(int) * 10);

    // Initialize the data array on the device
    acc_init(data, sizeof(int) * 10);

    // Verify that the data array is initialized correctly
    for (int i = 0; i < 10; i++) {
        if (data[i] != 0) {
            err = 1;
            break;
        }
    }

    // Free the data array
    acc_free(data);

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