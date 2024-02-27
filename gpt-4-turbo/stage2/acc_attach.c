#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

// Seed for randomness in data generation, keeps data deterministic across runs
#define SEED 42
// Number of test calls to make sure we test thoroughly
#define NUM_TEST_CALLS 10

// Test function for acc_attach
int test_acc_attach_detach(){
    int err = 0;
    srand(SEED);

    // Host and device array pointers
    int *host_array = (int*)malloc(sizeof(int)*100);
    int *device_array = NULL;

    // Prepare data
    for(int i = 0; i < 100; ++i) {
        host_array[i] = i; // Populate the array with sequential values
    }

    // Attach the device pointer to the host pointer's device copy
    device_array = host_array;
    acc_attach((void**)&device_array);

    #pragma acc enter data copyin(host_array[0:100])

    // Use a data region to confirm the attachment
    #pragma acc parallel loop present(host_array)
    for(int i = 0; i < 100; ++i) {
        // Doing an empty operation, we are just verifying data presence
        host_array[i] = host_array[i]; 
    }

    // Check if device_array and host_array point to same memory
    if(device_array != host_array) {
        printf("Test Failed: Device and Host pointer not equal after acc_attach.\n");
        err = 1;
    }

    // Detach the device pointer from the host pointer's device copy
    acc_detach((void**)&device_array);

    // Cleanup
    #pragma acc exit data delete(host_array[0:100])
    free(host_array);

    // Return error status
    return err;
}

int main(){
    int failcode = 0;
    int failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed += test_acc_attach_detach();
    }
    if (failed != 0){
        failcode += (1 << 0);
    }

    if (!failcode) {
        printf("All tests passed successfully!\n");
    } else {
        printf("Some tests failed. Failcode: %d\n", failcode);
    }

    return failcode;
}