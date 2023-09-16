#include <openacc.h>
#include <stdio.h>
#include <stdlib.h>
#define SIZE 1024

void initialize(float* data, int size) {
    for(unsigned int i = 0; i < size; i++)
        data[i] = (float)rand() / (float)RAND_MAX;
}

// Test function: checks if memory is freed
int is_memory_freed(){
    int err = 0;
    float* h_data = (float*)malloc(sizeof(float)*SIZE);
    initialize(h_data, SIZE);

    // Allocate and copy data to device
    float* d_data = (float*)acc_malloc(sizeof(float)*SIZE);
    acc_memcpy_to_device(d_data, h_data, sizeof(float)*SIZE);

    // Free data from device
    acc_free(d_data);

    // Attempt to access the freed memory; expect an error
    if(acc_get_cuda_stream() != NULL){
        acc_memcpy_from_device(h_data, d_data, sizeof(float)*SIZE);
        if(cudaPeekAtLastError() != cudaErrorInvalidValue){
            err = 1;
        }
        cudaGetLastError(); // Resets the error to avoid propagation
    }

    free(h_data);
    return err;
}

int main(){
    int failcode = 0;
    int NUM_TEST_CALLS = 10;
    int failed = 0;
    
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + is_memory_freed();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
    
    return failcode;
}