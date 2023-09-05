#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    int *data;
    int *deviceptr;

    // Allocate memory on the device
    deviceptr = (int *)acc_malloc(sizeof(int));

    // Initialize the data on the host
    data = (int *)malloc(sizeof(int));
    data[0] = 1;

    // Copy the data to the device
    acc_memcpy_to_device(deviceptr, data, sizeof(int));

    // Verify that the data has been copied correctly
    if (deviceptr[0] != data[0]){
        err = 1;
    }

    // Free the memory on the device
    acc_free(deviceptr);

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