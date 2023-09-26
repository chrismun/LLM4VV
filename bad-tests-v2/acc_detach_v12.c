#include "acc_testsuite.h"

#ifndef T1
//T1:acc detach,V:2.7-3.3
int test1(){
    int err = 0;
    int *host_ptr = (int *)malloc(sizeof(int));
    int *device_ptr = (int *)acc_malloc(sizeof(int));

    // attach the host pointer to the device pointer
    acc_attach(host_ptr, device_ptr);

    // detach the host pointer from the device pointer
    acc_detach(host_ptr);

    // check that the host pointer is no longer attached to the device pointer
    if (acc_is_attached(host_ptr, device_ptr) != 0) {
        err = 1;
    }

    // free the device memory
    acc_free(device_ptr);

    // free the host memory
    free(host_ptr);

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