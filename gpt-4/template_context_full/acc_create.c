#include "acc_testsuite.h"
#include <stdlib.h>

// Test the functionality of acc create
int validate_acc_create() {
    int err = 0;
    int *data;
    size_t size;

    // Initialize random seed
    srand(SEED);

    // Pick a random size for allocation from 1 to 1024
    size = rand() % 1024 + 1;

    // Allocate memory on host
    data = (int*)malloc(size * sizeof(int));

    // Allocate similarly sized memory on device
    void *deviceData = acc_create((void*)data, size * sizeof(int));

    // Check if the pointer to device memory is non-null
    if (deviceData == NULL) {
        err = 1;
    }

    // Free memory
    free(data);

    return err;
}

int main() {
    int returnCode = 0;

    // We will run the test a number of times defined by NUM_TEST_CALLS 
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        returnCode += validate_acc_create();
    }

    // If any test failed, return a non-zero exit code
    if (returnCode != 0) {
        return 1;
    }

    // If all tests passed, return 0
    return 0;
}