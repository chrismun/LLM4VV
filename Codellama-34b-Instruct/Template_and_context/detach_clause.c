#include <openacc.h>

#define NUM_TEST_CALLS 10

int test1(){
    int err = 0;
    srand(SEED);

    // Create a shared memory region
    acc_shared_memory_region_t region;
    acc_shared_memory_region_create(&region, sizeof(int));

    // Create a pointer to the shared memory region
    int *ptr = (int *)acc_shared_memory_region_get_pointer(region);

    // Initialize the shared memory region
    *ptr = 0;

    // Create a device memory region
    acc_device_memory_region_t device_region;
    acc_device_memory_region_create(&device_region, sizeof(int));

    // Create a pointer to the device memory region
    int *device_ptr = (int *)acc_device_memory_region_get_pointer(device_region);

    // Initialize the device memory region
    *device_ptr = 0;

    // Update the shared memory region with the device memory region
    acc_update_device(region, device_region, sizeof(int));

    // Check that the shared memory region has been updated
    if (*ptr != *device_ptr) {
        err = 1;
    }

    // Update the device memory region with the shared memory region
    acc_update_self(device_region, region, sizeof(int));

    // Check that the device memory region has been updated
    if (*device_ptr != *ptr) {
        err = 1;
    }

    // Clean up
    acc_shared_memory_region_destroy(region);
    acc_device_memory_region_destroy(device_region);

    return err;
}

int main(){
    int failcode = 0;
    int failed;

    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }

    return failcode;
}