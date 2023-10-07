#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

int main() {
    // Size of array
    int n = 1000;
    
    // Allocate host memory
    float *a = (float*)malloc(n*sizeof(float));
    
    // Initialize host array
    for (int i = 0; i < n; i++) {
        a[i] = i;
    }
    
    // Allocate device memory
    float *a_device = (float*)acc_malloc(n*sizeof(float));
    // Test if the allocation is successful
    if(a_device == NULL){
        printf("Failed to allocate memory on device\n");
        return -1;
    }
    
    // Copy host memory to device memory
    acc_memcpy_to_device(a_device, a, n*sizeof(float));
    
    // Free device memory
    acc_free(a_device);
    a_device = NULL;
    
    // Check if a_device is NULL after acc_free
    if(a_device != NULL){
        printf("Failed to free memory on device\n");
        return -1;
    }
    printf("Memory successfully freed on device\n");
    
    // Free host memory
    free(a);
    a = NULL;

    return 0;
}