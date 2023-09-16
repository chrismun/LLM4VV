#include <openacc.h>
#include <stdio.h>
#include <stdlib.h>

#define ARRAY_SIZE 1024
#define ERROR_THRESHOLD 1e-6

// Function to check if the arrays are equal
int check(float* a, float* b, size_t size) {
    for (int i = 0; i < size; i++) {
        if (abs(a[i] - b[i]) > ERROR_THRESHOLD) {
            return 0;
        }
    }
    return 1;
}

int main() {
    // Allocate host memory
    float* h_a = (float*)malloc(ARRAY_SIZE * sizeof(float));
    float* h_b = (float*)malloc(ARRAY_SIZE * sizeof(float));
    
    // Initialize arrays
    for (int i = 0; i < ARRAY_SIZE; i++) {
        h_a[i] = rand()/(float)RAND_MAX;
    }

    // Allocate device memory
    float* d_a = (float*)acc_malloc(ARRAY_SIZE * sizeof(float));
    
    // Copy data to device
    acc_memcpy_to_device(d_a, h_a, ARRAY_SIZE * sizeof(float));

    // Copy data back to host
    acc_memcpy_from_device(h_b, d_a, ARRAY_SIZE * sizeof(float));

    // Check if the memory transfers were successful
    if (check(h_a, h_b, ARRAY_SIZE)) {
        printf("Test passed!\n");
        return EXIT_SUCCESS;
    } else {
        printf("Test failed\n");
        return EXIT_FAILURE;
    }

    // Free both host and device memory
    acc_free(d_a);
    free(h_a);
    free(h_b);

    return 0;
}