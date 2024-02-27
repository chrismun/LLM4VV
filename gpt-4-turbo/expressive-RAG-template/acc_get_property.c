#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

// Assuming acc_testsuite.h defines SEED and NUM_TEST_CALLS
#include "acc_testsuite.h"

#ifndef T1
//T1:acc_get_property,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    // Initialize OpenACC runtime
    acc_init(acc_device_default);

    // Assuming there is at least one device, use device 0 for this test.
    int dev_num = 0;
    acc_device_t dev_type = acc_get_device_type();
    size_t memory_size = acc_get_property(dev_num, dev_type, acc_property_memory);

    // Checking the retrieved memory size to indicate a failure if it returns 0
    // as this would likely indicate that the property is not correctly retrieved.
    if (memory_size == 0) {
        printf("Error: acc_get_property failed to retrieve device memory size.\n");
        err = 1; // Set error flag
    } else {
        printf("Success: Device memory size is %zu bytes.\n", memory_size);
    }

    // Finalize OpenACC runtime (optional, for cleanliness)
    acc_shutdown(acc_device_default);

    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed = 0;
#ifndef T1
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed += test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    // Return failcode indicating success (0) or failure (non-zero)
    return failcode;
}