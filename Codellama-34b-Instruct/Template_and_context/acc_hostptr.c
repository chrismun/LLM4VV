#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <acc_testsuite.h>

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Create a device pointer
    void *data_dev = acc_deviceptr(malloc(1024));

    // Get the host pointer associated with the device pointer
    void *data_host = acc_hostptr(data_dev);

    // Check if the host pointer is the same as the incoming address
    if (data_host != data_dev) {
        err = 1;
    }

    // Free the device memory
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