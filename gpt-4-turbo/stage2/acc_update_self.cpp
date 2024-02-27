#include <iostream>
#include <stdlib.h>
#include <openacc.h>

#define SEED 42
#define NUM_ELEMENTS 1024
#define NUM_TEST_CALLS 5

// Utility function to initialize array
void init_array(int *array, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        array[i] = rand() % 100; // Example initialization
    }
}

int test1(){
    int err = 0;
    srand(SEED);

    // Host array
    int *a = new int[NUM_ELEMENTS];
    init_array(a, NUM_ELEMENTS);
    
    // Copy data to device
    #pragma acc enter data copyin(a[0:NUM_ELEMENTS])

    // Modify the data in the device memory in some way
    // Note: This step would typically involve additional OpenACC parallelism constructs
    #pragma acc parallel loop
    for(int i = 0; i < NUM_ELEMENTS; ++i) {
        a[i] += 1; // Simple operation for demonstration
    }

    // Update the data in local memory from the corresponding device memory
    #pragma acc update self(a[0:NUM_ELEMENTS])
    
    // Verify the update
    for(int i = 0; i < NUM_ELEMENTS; ++i) {
        if(a[i] != (rand() % 100) + 1) { // Check against expected value after modification
            err++;
            break;
        }
    }

    // Cleanup
    #pragma acc exit data delete(a[0:NUM_ELEMENTS])
    delete[] a;
  
    return err;
}

int main(){
    int failcode = 0;
    int failed;

    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }

    if(failcode == 0) {
        std::cout << "Test passed successfully" << std::endl;
    } else {
        std::cout << "Test failed with code: " << failcode << std::endl;
    }

    return failcode;
}