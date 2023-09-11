#include <iostream>
#include <cstdlib>
#include <cstring>

#ifndef T1
//T1:acc hostptr,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    // Create a device pointer
    void* data_dev = acc_deviceptr(malloc(100));

    // Get the host pointer associated with the device pointer
    void* host_ptr = acc_hostptr(data_dev);

    // Check if the host pointer is the same as the incoming address
    if (host_ptr != data_dev) {
        err = 1;
    }

    // Check if the data is in shared memory or data_dev is a null pointer
    if (acc_is_shared(data_dev) || data_dev == NULL) {
        err = 1;
    }

    // Check if the data corresponds to a host address which is present in the current device memory
    if (acc_is_present(data_dev)) {
        err = 1;
    }

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