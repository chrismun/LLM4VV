#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Create a device memory region
    void *data_dev = acc_malloc(sizeof(int));
    if (data_dev == NULL) {
        err = 1;
    }

    // Create a host memory region
    int data_host = 0;

    // Copy data from device to host
    acc_memcpy_from_device(data_host, data_dev, sizeof(int));

    // Check if the data was copied correctly
    if (data_host != 0) {
        err = 1;
    }

    // Free the device memory region
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