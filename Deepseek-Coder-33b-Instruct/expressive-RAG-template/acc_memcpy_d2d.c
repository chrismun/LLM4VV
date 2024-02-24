#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define SIZE 100

int main() {
    int *h_a, *h_b, *d_a, *d_b;
    int i, err = 0;

    // Allocate host memory
    h_a = (int*)malloc(SIZE * sizeof(int));
    h_b = (int*)malloc(SIZE * sizeof(int));

    // Initialize host memory
    for(i = 0; i < SIZE; i++) {
        h_a[i] = i;
    }

    // Allocate device memory
    d_a = (int*)acc_malloc(SIZE * sizeof(int));
    d_b = (int*)acc_malloc(SIZE * sizeof(int));

    // Copy data from host to device
    acc_memcpy_d2d(d_a, h_a, SIZE * sizeof(int), 0, 0);

    // Copy data from device to device
    acc_memcpy_d2d(d_b, d_a, SIZE * sizeof(int), 0, 0);

    // Copy data from device to host
    acc_memcpy_d2d(h_b, d_b, SIZE * sizeof(int), 0, 0);

    // Verify the results
    for(i = 0; i < SIZE; i++) {
        if(h_b[i] != h_a[i]) {
            printf("Error at index %d: %d != %d\n", i, h_b[i], h_a[i]);
            err = 1;
        }
    }

    // Free device memory
    acc_free(d_a);
    acc_free(d_b);

    // Free host memory
    free(h_a);
    free(h_b);

    return err;
}