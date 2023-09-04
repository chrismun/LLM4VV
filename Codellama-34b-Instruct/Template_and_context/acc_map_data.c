#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Allocate some memory on the device
    void *data_dev = acc_malloc(1024);

    // Map the device memory to a host address
    void *data_arg = acc_map_data(data_dev, 1024);

    // Check that the data is mapped correctly
    if (data_arg != data_dev) {
        err = 1;
    }

    // Unmap the data
    acc_unmap_data(data_arg);

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