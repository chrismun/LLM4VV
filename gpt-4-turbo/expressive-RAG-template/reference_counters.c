#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#ifndef SEED
#define SEED 12345
#endif

#ifndef NUM_TEST_CALLS
#define NUM_TEST_CALLS 10
#endif

// Test for verifying correct behavior of reference counters through data presence
int test_reference_counters() {
    int err = 0;
    int *host_array = NULL;
    int array_size = 1024;
    int i;

    // Allocating memory on the host
    host_array = (int *)malloc(array_size * sizeof(int));
    if (host_array == NULL) {
        fprintf(stderr, "Failed to allocate host memory\n");
        return 1;
    }

    // Initialize host array
    for(i = 0; i < array_size; ++i) {
        host_array[i] = rand() / (RAND_MAX / 100);
    }

    // First level data region: Increases structured reference counter
    #pragma acc data copy(host_array[0:array_size])
    {
        // Modifying the data within the first data region
        #pragma acc parallel loop
        for(i = 0; i < array_size; ++i) {
            host_array[i] += 1;
        }

        // Nested data region: Further increases the structured reference counter
        #pragma acc data copy(host_array[0:array_size])
        {
            // Modifying the data within the nested data region
            #pragma acc parallel loop
            for(i = 0; i < array_size; ++i) {
                host_array[i] += 1;
            }
        }
        // Exiting the nested data region should decrement the structured reference counter
    }
    // Exiting the first data region should decrement the structured reference counter to zero and deallocate device memory

    // Verifying data modifications to check if data regions were entered and exited correctly
    for(i = 0; i < array_size; ++i) {
        if(host_array[i] != (rand() / (RAND_MAX / 100)) + 2) {
            err = 1; // Error, the reference counters did not behave as expected
            printf("Data validation failed at index %d\n", i);
            break;
        }
    }

    free(host_array);

    return err;
}

int main() {
    int failcode = 0;
    int failed = 0;
    
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed += test_reference_counters();
    }
    
    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }
    
    return failcode;
}