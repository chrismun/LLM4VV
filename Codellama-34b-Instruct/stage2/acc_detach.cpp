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

    // Create a device pointer
    int *dev_ptr = (int *)acc_malloc(sizeof(int));
    assert(dev_ptr != NULL);

    // Attach the device pointer to the host pointer
    int *host_ptr = (int *)acc_attach(dev_ptr);
    assert(host_ptr != NULL);

    // Detach the device pointer from the host pointer
    acc_detach(dev_ptr);

    // Check that the device pointer is no longer attached to the host pointer
    assert(acc_is_attached(dev_ptr) == 0);

    // Free the device pointer
    acc_free(dev_ptr);

    return err;
}

int main() {
    int failcode = 0;
    int failed;

    // Run the test 100 times
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed = test1();
        if (failed != 0) {
            failcode = failcode + (1 << x);
        }
    }

    // Print the result
    if (failcode == 0) {
        std::cout << "Test passed" << std::endl;
    } else {
        std::cout << "Test failed" << std::endl;
    }

    return failcode;
}