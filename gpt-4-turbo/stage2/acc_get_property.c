#include <openacc.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef T1
// T1:acc_get_property,V:2.7-3.3
int test1(){
    int err = 0;
    srand(42); // SEED is simply replaced with a fixed seed for reproducibility

    int dev_count = acc_get_num_devices(acc_device_default);
    if (dev_count == 0) {
        printf("No OpenACC devices found.\n");
        return 1; // Error if no devices
    }
    // Assuming using the first available device, or change as needed
    int dev_num = 0;
    
    // Querying size of device memory in bytes
    size_t memory_size = acc_get_property(dev_num, acc_device_default, acc_property_memory);
    if (memory_size == 0) {
        printf("Failed to retrieve device memory size or device does not support this property.\n");
        err = 1; // Fail if 0 (assuming that having 0 bytes memory makes no sense)
    } else {
        printf("Device memory size: %zu bytes\n", memory_size);
    }
    
    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed = 0;
#ifndef T1
    for (int x = 0; x < 1; ++x){ // NUM_TEST_CALLS replaced with 1 for simplicity
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}