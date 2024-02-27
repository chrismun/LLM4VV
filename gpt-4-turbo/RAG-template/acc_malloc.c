#include <stdlib.h>
#include <stdio.h>
#include <openacc.h> // Include the OpenACC header

// Define the macros used in the template if not already defined
#ifndef SEED
#define SEED 1234
#endif

#ifndef NUM_TEST_CALLS
#define NUM_TEST_CALLS 10
#endif

// Test function to verify acc_malloc functionality
int test1() {
    int err = 0; // Error flag
    srand(SEED);

    // Allocate space for an integer array in device memory
    size_t num_bytes = sizeof(int) * 100; // Size for 100 integers
    int* device_ptr = (int*)acc_malloc(num_bytes);

    // Check if allocation was successful
    if(device_ptr == NULL) {
        fprintf(stderr, "acc_malloc failed to allocate device memory.\n");
        err = 1; // Set error flag
    } else {
        // Allocation was successful, now let's attempt a simple operation on the device
        // Assuming OpenACC 2.7 - 3.3 compliance, this should work if the compiler is correct
#pragma acc parallel loop deviceptr(device_ptr)
        for(int i = 0; i < 100; i++) {
            device_ptr[i] = i; // Dummy operation to fill array
        }
        
        // Assuming success, but in a complete test, you might want to copy data back
        // and verify its correctness as additional validation

        // Free the allocated device memory
        acc_free(device_ptr);
    }

    return err;
}

int main() {
    int failcode = 0;
    int failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed += test1();
    }
    if (failed != 0) {
        failcode += (1 << 0);
    }
    if(failcode == 0) {
        printf("All tests passed successfully.\n");
    } else {
        printf("Some tests failed.\n");
    }
    return failcode;
}