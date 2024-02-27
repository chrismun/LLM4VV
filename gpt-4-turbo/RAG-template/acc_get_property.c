#include "acc_testsuite.h"
#include <stdlib.h>
#include <stdio.h>
#include <openacc.h>

#ifndef T1
// T1:{feature},V:2.7-3.3
int test1() {
    int err = 0;
    srand(SEED);

    // Initialize OpenACC runtime (may not be needed depending on the framework)
    acc_init(acc_device_default);

    // Get the number of devices of the default type (adjust as needed)
    int num_devices = acc_get_num_devices(acc_device_default);
    if (num_devices == 0) {
        printf("No OpenACC devices found.\n");
        return 1; // Error: no devices found
    }

    // Check memory size for each device
    for (int dev_num = 0; dev_num < num_devices; ++dev_num) {
        // Get the property value
        size_t memory_size = acc_get_property(dev_num, acc_device_default, acc_property_memory);
        
        // Check the returned value. Since we cannot verify without actual device info, we just ensure it's not zero.
        if (memory_size == 0) {
            printf("Failed to get device memory size for device %d.\n", dev_num);
            err++;
        } else {
            printf("Device %d memory size: %zu bytes\n", dev_num, memory_size);
        }
    }

    // Finalize OpenACC runtime (may not be needed depending on the framework)
    acc_shutdown(acc_device_default);

    return err;
}
#endif

int main() {
    int failcode = 0;
    int failed = 0;
#ifndef T1
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed += test1();
    }
    if (failed != 0) {
        failcode += (1 << 0);
    }
#endif
    // Report the result of the tests
    if (failcode == 0) {
        printf("All tests passed successfully.\n");
    } else {
        printf("Some tests failed. Failcode: %d\n", failcode);
    }
    return failcode;
}