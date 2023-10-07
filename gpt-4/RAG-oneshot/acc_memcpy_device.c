#include <stdio.h>
#include <openacc.h>
#include <assert.h>

#define SIZE 1024

int main() {
    // Allocate host memory
    float *h_a = (float*) malloc(SIZE * sizeof(float));
    float *h_b = (float*) malloc(SIZE * sizeof(float));
    assert(h_a && h_b);
    
    // Initialize host arrays
    for(int i = 0; i < SIZE; i++) {
        h_a[i] = i;
        h_b[i] = 0.0f;
    }
    
    // Allocate device memory
    float *d_a = (float*) acc_malloc(SIZE * sizeof(float));
    float *d_b = (float*) acc_malloc(SIZE * sizeof(float));
    assert(d_a && d_b);
    
    // Copy data from host to device
    acc_memcpy_to_device(d_a, h_a, SIZE * sizeof(float));
    
    // Use acc_memcpy_device to copy data between memory locations on the device
    acc_memcpy_device(d_b, d_a, SIZE * sizeof(float));
    
    // Copy data back to host
    acc_memcpy_from_device(h_b, d_b, SIZE * sizeof(float));

    // Validate results
    int errors = 0;
    for(int i = 0; i < SIZE; i++) {
        if(h_b[i] != i){
            errors++;
        }
    }

    // Cleanup
    acc_free(d_a);
    acc_free(d_b);
    free(h_a);
    free(h_b);

    // Output result
    if(errors == 0) {
        printf("Test passed\n");
    } else {
        printf("Test failed: %d errors\n", errors);
    }

    return 0;
}