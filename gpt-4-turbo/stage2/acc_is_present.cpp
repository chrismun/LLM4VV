#include <iostream>
#include <cstdlib>
#include <openacc.h>

// Define constants for the test, such as random seed and number of iterations for the test.
#define SEED 12345
#define NUM_TEST_CALLS 10

// Test function to check if 'acc_is_present' works as expected.
int test_acc_is_present(){
    int err = 0;
    // Initialize a variable
    int hostVar = 42;

    // Ensure the variable is not allocated in the device memory before proceeding:
    // This should return 0 since hostVar is initially not present in the device memory.
    if(acc_is_present(&hostVar, sizeof(hostVar))){
        std::cerr << "Error: hostVar unexpectedly present in device memory before explicit allocation." << std::endl;
        err++;
    }

    // Now, explicitly allocate 'hostVar' in the device using acc_malloc and check again.
    int *deviceVar = static_cast<int*>(acc_malloc(sizeof(int)));
    *deviceVar = hostVar; // Copy hostVar to device memory.

    // This should now return non-zero as the data is explicitly present in the device memory.
    if(!acc_is_present(deviceVar, sizeof(int))){
        std::cerr << "Error: deviceVar not present in device memory after explicit allocation." << std::endl;
        err++;
    }

    // Free the allocated device memory as good practice.
    acc_free(deviceVar);

    // Return 0 if test passed, or the number of errors if failed.
    return err;
}

// Main function orchestrating the test.
int main(){
    // Seed random number generator for consistency
    srand(SEED);

    int failcode = 0;
    int failed = 0;

    // Run the `test_acc_is_present` function NUM_TEST_CALLS times to check for consistency.
    for(int x = 0; x < NUM_TEST_CALLS; ++x){
        failed += test_acc_is_present();
    }

    // If any of the test calls failed, adjust the failcode accordingly.
    if(failed != 0){
        failcode += (1 << 0);
    }

    // Return the failcode: 0 if all tests passed, nonzero otherwise.
    return failcode;
}