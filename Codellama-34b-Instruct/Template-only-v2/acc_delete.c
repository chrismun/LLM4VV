#include "acc_testsuite.h"

#ifndef T1
//T1:acc delete,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    // Create a new device
    acc_device_t device = acc_create_device(ACC_DEVICE_TYPE_GPU, 0);

    // Allocate memory on the device
    acc_mem_t mem = acc_malloc(device, 1024);

    // Delete the memory on the device
    acc_delete(mem);

    // Check that the memory has been deleted
    if (acc_mem_get_device(mem) != NULL) {
        err = 1;
    }

    // Free the device
    acc_free(device);

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