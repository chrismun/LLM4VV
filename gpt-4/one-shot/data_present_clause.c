#include "acc_testsuite.h"

// Test function
int test() {
    int err = 0;
    int present = 0;

    // We'll use an array to test the query
    double *arr = (double *)malloc(1000 * sizeof(double));

    // Initialize the array
    for (int i = 0; i < 1000; ++i) {
        arr[i] = (double)i;
    }

    // Explicitly copy the array to the device
    #pragma acc enter data copyin(arr[:1000])

    // Check if the array is present on the device
    #pragma acc on_device
    {
        present = acc_is_present(arr, 1000 * sizeof(double));
    }

    // The array should be present
    if (!present) {
        err++;
    }

    // Now we'll delete the array from the device
    #pragma acc exit data delete(arr)

    // Check again if the array is present on the device
    #pragma acc on_device
    {
        present = acc_is_present(arr, 1000 * sizeof(double));
    }

    // This time, the array should not be present
    if (present) {
        err++;
    }

    // Free the array
    free(arr);

    return err;
}

int main() {
    int errorCount = 0;

    // Call the test function
    errorCount += test();

    // Print the test result
    if (errorCount == 0) {
        printf("PASSED\n");
    } else {
        printf("FAILED\n");
    }

    return errorCount;
}