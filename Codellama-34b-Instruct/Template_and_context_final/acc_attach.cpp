#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <cassert>
#include <openacc.h>

#define NUM_TEST_CALLS 100
#define SEED 12345

int test1() {
    int err = 0;
    srand(SEED);

    // Create a host pointer to a device memory region
    int *host_ptr = (int *)acc_malloc(sizeof(int));
    assert(host_ptr != NULL);

    // Attach the host pointer to the device memory region
    acc_attach(host_ptr);

    // Perform some operations on the device memory region
    int *device_ptr = (int *)acc_deviceptr(host_ptr);
    assert(device_ptr != NULL);
    device_ptr[0] = 123;

    // Detach the host pointer from the device memory region
    acc_detach(host_ptr);

    // Check that the host pointer is still valid
    assert(host_ptr != NULL);

    // Free the device memory region
    acc_free(host_ptr);

    return err;
}

int main() {
    int failcode = 0;
    int failed;

    // Run the test multiple times to ensure it passes consistently
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed = test1();
        if (failed != 0) {
            failcode = failcode + (1 << x);
        }
    }

    return failcode;
}