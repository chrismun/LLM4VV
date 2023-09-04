#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Initialize data on host
    int* data_host = (int*)malloc(sizeof(int) * 10);
    for (int i = 0; i < 10; i++) {
        data_host[i] = i;
    }

    // Allocate device memory
    int* data_dev = (int*)acc_malloc(sizeof(int) * 10);

    // Copy data from host to device
    acc_memcpy_to_device(data_dev, data_host, sizeof(int) * 10);

    // Copy data from device to host
    acc_memcpy_from_device(data_host, data_dev, sizeof(int) * 10);

    // Check that data was copied correctly
    for (int i = 0; i < 10; i++) {
        if (data_host[i] != i) {
            err = 1;
            break;
        }
    }

    // Free device memory
    acc_free(data_dev);

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