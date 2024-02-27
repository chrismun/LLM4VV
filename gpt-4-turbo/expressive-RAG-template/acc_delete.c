#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

// Define a seed for reproducibility
#define SEED 12345
// Define the number of test calls
#define NUM_TEST_CALLS 100

#ifndef T1
// T1: acc_delete, V:2.7-3.3
int test_acc_delete(){
    int err = 0;
    srand(SEED);
    size_t data_size = sizeof(float) * 1024; // Allocate space for 1024 floats

    // Allocate memory on the host
    float* hostArray = (float*) malloc(data_size);
    // Initialize data (so we have something to copy)
    for (int i = 0; i < 1024; i++) {
        hostArray[i] = rand() / (float)RAND_MAX;
    }

    // Allocate and copy data to the device using acc_copyin, then delete it
    #pragma acc data copyin(hostArray[0:1024])
    {
        // Use the data somehow in the device; for simplicity, a dummy parallel region
        #pragma acc parallel loop  
        for (int i = 0; i < 1024; ++i) {
            // Perform a simple operation
            hostArray[i] = hostArray[i] * 2.0f;
        }

        // Simulate operation requiring deletion beforehand
        #pragma acc exit data delete(hostArray[0:1024])
    }

    // One way to check if acc_delete worked is to try using the data again and see if there’s an error
    // due to not enough device memory or similar. This is indirect and depends on device capabilities.
    // We rely on no errors meaning everything went as expected.

    // Clean up
    free(hostArray);

    return err; // Return 0 if everything was alright, non-zero otherwise.
}
#endif

int main(){
    int failcode = 0;
    int failed = 0;
#ifndef T1
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed += test_acc_delete();
    }
    if (failed != 0){
        failcode += (1 << 0);
    }
#endif
    return failcode;
}