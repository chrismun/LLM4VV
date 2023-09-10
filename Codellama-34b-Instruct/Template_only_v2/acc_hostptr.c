#include "acc_testsuite.h"

#ifndef T1
//T1:acc hostptr,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    int *host_ptr = (int *)malloc(sizeof(int));
    int *device_ptr = (int *)malloc(sizeof(int));

    // Initialize host and device pointers
    *host_ptr = 1;
    *device_ptr = 2;

    // Attach host pointer to device
    acc_attach(host_ptr, device_ptr, sizeof(int));

    // Modify host pointer
    *host_ptr = 3;

    // Check that device pointer has been updated
    if (*device_ptr != 3) {
        err = 1;
    }

    // Detach host pointer from device
    acc_detach(host_ptr, device_ptr);

    // Check that device pointer has been updated
    if (*device_ptr != 3) {
        err = 1;
    }

    free(host_ptr);
    free(device_ptr);

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