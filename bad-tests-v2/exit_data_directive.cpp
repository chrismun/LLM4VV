#include "acc_testsuite.h"
#ifndef T1
//T1:exit data directive,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    // Create a data array
    int data[10];
    for (int i = 0; i < 10; i++) {
        data[i] = rand() % 100;
    }

    // Create a device array
    int* dev_data;
    acc_malloc(dev_data, 10 * sizeof(int));

    // Copy data to device
    acc_memcpy(dev_data, data, 10 * sizeof(int));

    // Create a host array
    int* host_data;
    acc_malloc(host_data, 10 * sizeof(int));

    // Copy data from device to host
    acc_memcpy(host_data, dev_data, 10 * sizeof(int));

    // Verify that the data was copied correctly
    for (int i = 0; i < 10; i++) {
        if (host_data[i] != data[i]) {
            err = 1;
            break;
        }
    }

    // Free device memory
    acc_free(dev_data);

    // Free host memory
    acc_free(host_data);

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