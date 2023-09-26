#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Initialize data
    int *data = (int *)malloc(sizeof(int) * 10);
    for (int i = 0; i < 10; i++) {
        data[i] = i;
    }

    // Copy data to device
    int *device_data = (int *)acc_malloc(sizeof(int) * 10);
    acc_memcpy(device_data, data, sizeof(int) * 10);

    // Verify data on device
    for (int i = 0; i < 10; i++) {
        if (device_data[i] != data[i]) {
            err = 1;
            break;
        }
    }

    // Free device memory
    acc_free(device_data);

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