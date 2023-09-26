#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openacc.h>

#define NUM_TEST_CALLS 10
#define SEED 12345

int test1() {
    int err = 0;
    srand(SEED);

    // Get the device number and device type
    int dev_num = rand() % 10;
    acc_device_t dev_type = acc_get_device_type(dev_num);

    // Get the memory size and free memory size
    size_t mem_size = acc_get_property(dev_num, dev_type, acc_property_memory);
    size_t free_mem_size = acc_get_property(dev_num, dev_type, acc_property_free_memory);

    // Get the device name, vendor, and driver version
    const char* name = acc_get_property_string(dev_num, dev_type, acc_property_name);
    const char* vendor = acc_get_property_string(dev_num, dev_type, acc_property_vendor);
    const char* driver = acc_get_property_string(dev_num, dev_type, acc_property_driver);

    // Print the results
    printf("Device %d (%s):\n", dev_num, name);
    printf("  Memory size: %zu\n", mem_size);
    printf("  Free memory size: %zu\n", free_mem_size);
    printf("  Device name: %s\n", name);
    printf("  Device vendor: %s\n", vendor);
    printf("  Device driver version: %s\n", driver);

    // Check if the device supports shared memory
    if (acc_get_property(dev_num, dev_type, acc_property_shared_memory_support) != 0) {
        printf("  Shared memory is supported\n");
    } else {
        printf("  Shared memory is not supported\n");
    }

    return err;
}

int main() {
    int failcode = 0;
    int failed;

    // Run the test 10 times
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed = test1();
        if (failed != 0) {
            failcode = failcode + (1 << x);
        }
    }

    return failcode;
}