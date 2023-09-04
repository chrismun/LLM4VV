#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Allocate memory on the device
    void *data_dev = acc_malloc(sizeof(int) * 10);

    // Map the device memory to the host memory
    int *data_arg = acc_map_data(data_dev, sizeof(int) * 10);

    // Verify that the data is mapped correctly
    for (int i = 0; i < 10; i++) {
        if (data_arg[i] != data_dev[i]) {
            err = 1;
            break;
        }
    }

    // Unmap the device memory
    acc_unmap_data(data_dev);

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