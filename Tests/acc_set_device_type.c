#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>

#define NUM_TEST_CALLS 100
#define SEED 42

int test1() {
    int err = 0;
    srand(SEED);

    // Generate a random device type
    int device_type = rand() % 3;

    // Set the device type
    #pragma acc set device_type(device_type)

    // Check if the device type was set correctly
    if (omp_get_device_type() != device_type) {
        err = 1;
    }

    return err;
}

int main() {
    int failcode = 0;
    int failed;

    // Test the feature
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed = failed + test1();
    }

    // Check if the feature passed
    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }

    return failcode;
}