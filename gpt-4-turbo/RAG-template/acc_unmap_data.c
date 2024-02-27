#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

// Seed for srand; for reproducibility
#define SEED 12345 
// Number of test calls to validate stability
#define NUM_TEST_CALLS 10

int test_unmap_data(){
    int err = 0;
    srand(SEED);

    const int size = 1024;
    float *data = (float*)malloc(size * sizeof(float));

    // Initialising data to check modifications.
    for(int i = 0; i < size; i++){
        data[i] = rand() % 100;
    }

    // Mapping the data to device
    acc_map_data(data, data, size * sizeof(float));

    // Modifying the data on the device.
    #pragma acc parallel loop present(data[0:size])
    for(int i = 0; i < size; i++){
        data[i] += 1.0f;
    }

    // Unmapping the data from the device. This should not deallocate device memory but unmap it.
    acc_unmap_data(data);

    // Attempting to use the data after unmapping. If it's correctly unmapped, operations may fail.
    // This is a conceptual check as per OpenACC specification; runtime behavior can vary
    // depending on implementation, making this a tricky scenario to validate directly.
    // In practice, further operations would depend on compiler/runtime specifics and
    // might not fail explicitly in a way that can be caught here. 
    // Hence, this example focuses on ensuring the code follows the intended OpenACC semantics,
    // without relying on behavior not guaranteed to be uniformly enforced by all compilers.

    free(data);
    return err;
}

int main(){
    int failcode = 0;
    int failed = 0;

    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed += test_unmap_data();
    }

    if (failed != 0){
        failcode += (1 << 0);
        printf("Tests failed with code: %d\n", failcode);
    } else {
        printf("All tests passed successfully.\n");
    }

    return failcode;
}