#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

int test_acc_create() {
    int err = 0;
    // Create an array of 100 integers in local memory
    int* array = (int*)malloc(100 * sizeof(int));

    // Use acc_create to allocate space for this array on the current device, without initializing data.
    // This does not copy data, just prepares space in the device memory.
#pragma acc enter data create(array[0:100])

    // Check if the array is present on the device after acc_create.
    // This is a simple check to see if acc_create worked, as acc_is_present should return true.
    if (!acc_is_present(array, 100 * sizeof(int))) {
        printf("Error: array should be present on the device after acc_create, but it's not detected.\n");
        err = 1; // Indicate an error condition
    }

    // Clean-up: Release the device memory allocated for the array.
#pragma acc exit data delete(array[0:100])

    free(array); // Free the host memory
    return err;
}

int main() {
    int failcode = 0;
    int failed = test_acc_create();
    if (failed != 0) {
        failcode += 1;
    }

    if (failcode == 0) {
        printf("Test PASSED: acc_create works as expected.\n");
    } else {
        printf("Test FAILED: acc_create does not work as expected. Failcode: %d\n", failcode);
    }

    return failcode;
}