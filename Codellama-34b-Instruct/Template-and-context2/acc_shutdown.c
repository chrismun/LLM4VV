#include "acc_testsuite.h"

#ifndef T1
//T1:acc shutdown,V:2.7-3.3
int test1(){
    int err = 0;

    // Set up the device and data
    acc_device_t dev_type = acc_device_default;
    int dev_num = 0;
    int *data = (int *)acc_malloc(sizeof(int) * 10);

    // Shut down the device
    acc_shutdown(dev_type);

    // Check that the data is no longer present in the device memory
    int *data_ptr = (int *)acc_deviceptr(data, dev_num);
    if (data_ptr != NULL) {
        err = 1;
    }

    // Free the data
    acc_free(data);

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