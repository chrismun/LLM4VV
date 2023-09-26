#include "acc_testsuite.h"

#ifndef T1
// T1: data present clause, V: 2.7-3.3
int test1() {
    int err = 0;
    int *dev_ptr = NULL;
    int *host_ptr = (int*)malloc(sizeof(int));

    *host_ptr = 10;

    // Allocate device memory and transfer data from host to device
    #pragma acc data copyin(host_ptr[0:1])
    {
        dev_ptr = (int*)acc_deviceptr(host_ptr);
    
        // Access device memory
        #pragma acc parallel loop
        for (int i = 0; i < 1; i++) {
            dev_ptr[i] *= 2;
        }
    }

    // Transfer data back to host and verify results
    #pragma acc data copyout(host_ptr[0:1])
    {
        // host_ptr should have been updated on the device
        if (*host_ptr != 20) {
            err = 1;
        }
    }

    free(host_ptr);
    return err;
}
#endif

int main() {
    int failcode = 0;
    int failed;
    
#ifndef T1
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed += test1();
    }
    if (failed != 0) {
        failcode += (1 << 0);
    }
#endif

    return failcode;
}