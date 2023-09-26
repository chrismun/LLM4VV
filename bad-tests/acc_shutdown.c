#include "acc_testsuite.h"
#include <stdlib.h>
#include <openacc.h>

#ifndef T1
/*T1:acc shutdown,V:2.0-2.7*/
int test1(){
    int err = 0;
    acc_device_t device_type = acc_device_nvidia;
    srand(SEED);
    int device_count = acc_get_num_devices(device_type);

    for(int dev_num = 0; dev_num < device_count; ++dev_num) {
        if(acc_set_device_num(dev_num, device_type) == 0){
            // if there is a problem setting the device, store an error
            err = 1;
        }
        // Shut down the device
        acc_shutdown_device(dev_num, device_type);
    }

    // Try to allocate and reference some memory on the device, if it's shutdown, it should cause an error
    float* test_array_device = (float*)acc_malloc(sizeof(float)*10);
    if(test_array_device != NULL){
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