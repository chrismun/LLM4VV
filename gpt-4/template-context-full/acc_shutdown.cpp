#include "acc_testsuite.h"
#include <openacc.h>

#ifndef T1
/*T1:acc shutdown,V:2.0-2.7*/
int test1(){
    int err = 0;

    // Define the device type to use
    acc_device_t dev_type = acc_device_nvidia;

    // Initialize a device of type `dev_type`
    acc_init(dev_type);

    // Check if initialization was successful
    if (acc_get_num_devices(dev_type) <= 0) {
        err = 1;
        printf("Error: No devices of type %d available\n", dev_type);
        return err;
    }

    // Shutdown the device
    acc_shutdown(dev_type);

    // Check if shutdown was successful
    if (acc_get_num_devices(dev_type) > 0) {
        err = 2;
        printf("Error: Device of type %d was not shutdown properly\n", dev_type);
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