#include <stdlib.h>
#include <stdio.h>
#include <openacc.h>

#define n 1000 // Define the size of the array

int test_acc_is_present() {
    int err = 0;
    float *a = (float *)malloc(n * sizeof(float));

    // Initialize the array
    for (int i = 0; i < n; ++i) {
        a[i] = i;
    }

    // Allocate memory on the device and copy data to the device
    #pragma acc enter data copyin(a[0:n])

    // Test if 'a' is present on the current device
    if (!acc_is_present(a, n * sizeof(float))) {
        printf("Data is not present on the device as expected.\n");
        err++;
    } else {
        printf("Data is present on the device as expected.\n");
    }

    // Cleanup: Release device memory
    #pragma acc exit data delete(a[0:n])

    free(a); // Free host memory
    return err;
}

int main() {
    int fail = test_acc_is_present();

    if (fail) {
        printf("Test failed with %d errors.\n", fail);
    } else {
        printf("Test passed.\n");
    }
    return fail;
}