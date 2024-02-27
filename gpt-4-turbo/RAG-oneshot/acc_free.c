#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define N 1024  // Size of the array

// Function to test acc_malloc and acc_free
int test_acc_free() {
    int err = 0;
    size_t size = N * sizeof(float);

    // Allocate memory on the device and get a device pointer
    float *d_ptr = (float *)acc_malloc(size);
    if (d_ptr == NULL) {
        fprintf(stderr, "Error in acc_malloc\n");
        return 1;
    }

    // Copy data from host to device
    float *h_ptr = (float *)malloc(size);
    for (int i = 0; i < N; ++i) {
        h_ptr[i] = i;
    }
    acc_memcpy_to_device(d_ptr, h_ptr, size);

    // Free the device memory
    acc_free(d_ptr);

    // Attempt to reallocate: this should work if acc_free has correctly freed the memory
    float *new_d_ptr = (float *)acc_malloc(size);
    if (new_d_ptr == NULL) {
        fprintf(stderr, "Re-allocation failed after acc_free\n");
        err = 1;
    }

    // Clean up
    free(h_ptr);
    if (new_d_ptr != NULL) {
        acc_free(new_d_ptr);
    }

    return err;
}

int main() {
    int err;

    err = test_acc_free();
    if (err != 0) {
        printf("Test failed\n");
        return 1;
    } else {
        printf("Test passed\n");
        return 0;
    }
}