#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Create a device memory region
    int *dev_mem = acc_malloc(sizeof(int) * 10);

    // Copy data from host to device
    acc_memcpy(dev_mem, &host_data, sizeof(int) * 10);

    // Verify that the data was copied correctly
    for (int i = 0; i < 10; i++) {
        if (dev_mem[i] != host_data[i]) {
            err = 1;
            break;
        }
    }

    // Free the device memory region
    acc_free(dev_mem);

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