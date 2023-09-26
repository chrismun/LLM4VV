#include "acc_testsuite.h"

#ifndef T1
//T1:acc update device,V:2.7-3.3
int test1(){
    int err = 0;

    // create a shared memory region
    int *shared_data = (int *)acc_malloc(sizeof(int));
    *shared_data = 1;

    // create a device memory region
    int *device_data = (int *)acc_malloc(sizeof(int));
    *device_data = 2;

    // update the device memory from the shared memory
    acc_update_device(shared_data, sizeof(int));

    // check that the device memory has been updated
    if (*device_data != 1) {
        err = 1;
    }

    // free the memory regions
    acc_free(shared_data);
    acc_free(device_data);

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