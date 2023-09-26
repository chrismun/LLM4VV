#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <acc_runtime.h>

#define NUM_TEST_CALLS 10

int test1(){
    int err = 0;
    srand(SEED);

    // Create a shared memory region
    void *shared_mem = acc_malloc(1024);
    if (shared_mem == NULL) {
        fprintf(stderr, "Failed to allocate shared memory\n");
        return 1;
    }

    // Create a device memory region
    void *device_mem = acc_malloc(1024);
    if (device_mem == NULL) {
        fprintf(stderr, "Failed to allocate device memory\n");
        return 1;
    }

    // Initialize the shared memory region
    memset(shared_mem, 0, 1024);

    // Initialize the device memory region
    memset(device_mem, 0, 1024);

    // Update the device memory from the shared memory
    acc_update_device(shared_mem, 1024);

    // Update the shared memory from the device memory
    acc_update_self(device_mem, 1024);

    // Check that the shared memory and device memory are equal
    if (memcmp(shared_mem, device_mem, 1024) != 0) {
        fprintf(stderr, "Shared memory and device memory are not equal\n");
        err = 1;
    }

    // Free the shared memory and device memory
    acc_free(shared_mem);
    acc_free(device_mem);

    return err;
}

int main(){
    int failcode = 0;
    int failed;

    // Run the test 10 times
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = test1();
        if (failed != 0){
            failcode = failcode + (1 << x);
        }
    }

    return failcode;
}