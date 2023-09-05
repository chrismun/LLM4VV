#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define SIZE 10000000

void initialize_array(float *arr, int size) {
    for (int i = 0; i < size; i++) {
        arr[i] = i;
    }
}

int main() {
    float *a = (float *)malloc(SIZE * sizeof(float));
    float *b = (float *)malloc(SIZE * sizeof(float));
    float *c = (float *)malloc(SIZE * sizeof(float));
    
    initialize_array(a, SIZE);
    initialize_array(b, SIZE);
    
    // Transfer data to device asynchronously
    #pragma acc enter data copyin(a[0:SIZE], b[0:SIZE]) async(1)

    // Perform computation on device asynchronously
    #pragma acc parallel loop async(2)
    for (int i = 0; i < SIZE; i++) {
        c[i] = a[i] + b[i];
    }

    // Wait for the async transfer to complete
    if (acc_async_test(1)) {
        printf("Data transfer completed.\n");
    } else {
        printf("Data transfer not completed.\n");
    }

    // Wait for the async kernel computation to complete
    if (acc_async_test(2)) {
        printf("Kernel computation completed.\n");
    } else {
        printf("Kernel computation not completed.\n");
    }

    // Free device data
    #pragma acc exit data delete(a[0:SIZE], b[0:SIZE])
    
    free(a);
    free(b);
    free(c);
    
    return 0;
}