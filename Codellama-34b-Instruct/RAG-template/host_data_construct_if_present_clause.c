#include "acc_testsuite.h"

#ifndef T1
//T1:host_data construct if_present clause,V:2.7-3.3
int test1(){
    int err = 0;

    // Set up the device memory
    int *device_data = (int *)acc_malloc(sizeof(int));
    *device_data = 123;

    // Set up the host data
    int host_data = 456;

    // Use the host_data construct with the if_present clause
    #pragma acc host_data if_present(device_data)
    {
        // Access the device data
        int device_value = *device_data;

        // Check that the device data is correct
        if (device_value != 123) {
            err = 1;
        }
    }

    // Free the device memory
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