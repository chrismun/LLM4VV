#include <openacc.h>
#include <stdio.h>
#include <stdlib.h>

#define SEED 12345

#ifndef T1
// T1:kernels,device,V:1.0-2.7
int test1(){
    int err = 0;

    acc_init(acc_device_default);
    int num_devices = acc_get_num_devices(acc_device_nvidia); // Change acc_device_nvidia to your target device type if different

    // Only proceed if there are devices available
    if (num_devices > 0) {
        acc_set_device_type(acc_device_nvidia); // Same here for device type
        acc_device_t dev_type = acc_get_device_type();
        if (dev_type != acc_device_nvidia) { // And here, check against your target device type
            fprintf(stderr, "Device type does not match expected.\n");
            err++;
        }

        int dev_id = acc_get_device_num(dev_type);
        if (dev_id < 0 || dev_id >= num_devices) {
            fprintf(stderr, "Device number is out of valid range.\n");
            err++;
        }

        // Example property check using acc_get_property: query total memory
        size_t total_memory;
        acc_get_property(dev_id, dev_type, acc_property_memory, &total_memory);
        if (total_memory <= 0) {
            fprintf(stderr, "Total memory reported as 0 or negative which is unexpected.\n");
            err++;
        }
    } else {
        fprintf(stderr, "No available devices of the specified type.\n");
        err++;
    }

    acc_shutdown(acc_device_default);

    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed;

    #ifndef T1
    failed = test1();
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
    #endif

    if (failcode) {
        printf("Test FAILED with failcode %d\n", failcode);
    } else {
        printf("All tests passed successfully.\n");
    }

    return failcode;
}