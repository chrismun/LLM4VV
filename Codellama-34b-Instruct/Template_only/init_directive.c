#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Initialize the data
    int data[10];
    for (int i = 0; i < 10; i++) {
        data[i] = i;
    }

    // Create a device pointer to the data
    int *dev_data = acc_malloc(10 * sizeof(int));
    acc_memcpy_to_device(dev_data, data, 10 * sizeof(int));

    // Initialize the device data
    acc_init(dev_data, 10 * sizeof(int));

    // Check that the data has been initialized
    for (int i = 0; i < 10; i++) {
        if (dev_data[i] != i) {
            err = 1;
            break;
        }
    }

    // Free the device memory
    acc_free(dev_data);

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