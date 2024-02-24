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
    #pragma acc data copyin(h_a[0:SIZE], h_b[0:SIZE]) copy(d_a[0:SIZE], d_b[0:SIZE])
    {
        // Copy data from device to device
        #pragma acc kernels
        {
            for(i = 0; i < SIZE; i++) {
                d_a[i] = h_a[i];
                d_b[i] = h_b[i];
            }
        }

        // Copy data from device to host
        #pragma acc update self(h_a[0:SIZE], h_b[0:SIZE])
    }

    // Verify the results
    for(i = 0; i < SIZE; i++) {
        if(h_a[i] != d_a[i] || h_b[i] != d_b[i]) {
            err++;
        }
    }

    // Free device memory
    acc_free(d_a);
    acc_free(d_b);

    // Free host memory
    free(h_a);
    free(h_b);

    if(err) {
        printf("Test failed with %d errors\n", err);
        return 1;
    } else {
        printf("Test passed\n");
        return 0;
    }
}