#include "acc_testsuite.h"
#include <stdlib.h>

// Define a constant for the size of the test data
#define DATA_SIZE 1000

// Define a constant for the seed of the random number generator
#define SEED 1234

/* Function to test acc_copyout */
int test_acc_copyout(){
    int err = 0;

    // Allocate memory for the data on host memory
    float *data_host = (float*) malloc(DATA_SIZE * sizeof(float)); 

    // Allocate memory for the data on the device
    float *data_device = (float*)acc_malloc(DATA_SIZE * sizeof(float)); 

    // Initialize data on host memory with random numbers
    srand(SEED);
    for (int i=0; i<DATA_SIZE; i++){
        data_host[i] = (float) rand() / RAND_MAX;
    }
 
    // Copy data from host memory to device memory
    acc_memcpy_to_device(data_device, data_host, DATA_SIZE * sizeof(float)); 

    // Copy data from device memory back to host with acc_copyout
    acc_copyout(data_device, DATA_SIZE * sizeof(float)); 

    // Check if the data has been correctly copied from device memory to host memory
    for (int i=0; i<DATA_SIZE; i++){
        if(data_host[i] != data_device[i]){
            err += 1;
        }
    }

    // Clean up the memory allocations
    acc_free(data_device);
    free(data_host);

    return err;
}

int main(){
    int failcode = 0;
#ifndef T1
    int failed = test_acc_copyout();
    if (failed != 0){
        failcode = (1 << 0);
    }
#endif
    return failcode;
}