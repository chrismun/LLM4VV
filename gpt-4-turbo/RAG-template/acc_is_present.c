#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

// Define constants for test configuration
#define SEED 123
#define NUM_TEST_CALLS 10
#define ARRAY_SIZE 100

// Test function to check if the memory is present on the device.
int test1(){
    int err = 0; // Error flag, 0 means no errors
    int *array = (int *)malloc(ARRAY_SIZE * sizeof(int)); // Dynamically allocate an array

    // Initialize the array with some values
    for (int i = 0; i < ARRAY_SIZE; i++) {
        array[i] = rand() % 100; // Assign random values
    }

    // Transfer data to device to ensure it's really there
    #pragma acc enter data copyin(array[0:ARRAY_SIZE])

    // Now check if the array is present on the device
    if(acc_is_present(array, ARRAY_SIZE * sizeof(int))){
        printf("Array is present on the device.\n");
    } else {
        printf("ERROR: Array not present on the device.\n");
        err = 1; // Set an error occurred
    }

    // Cleanup: Release the data from device
    #pragma acc exit data delete(array[0:ARRAY_SIZE])

    // Free the dynamically allocated memory
    free(array);

    return err;
}

int main(){
    int failcode = 0; // Overall test fail code
    int failed = 0; // Count of failed tests

    // Seed the random number generator
    srand(SEED);

    // Run test1 NUM_TEST_CALLS times
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed += test1();
    }

    // If any of the tests failed, update the failcode
    if (failed != 0) {
        failcode |= (1 << 0); // Mark the first bit if a test failed
    }

    // Return the failcode (0 means all tests have passed)
    return failcode;
}