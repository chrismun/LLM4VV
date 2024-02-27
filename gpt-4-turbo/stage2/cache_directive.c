#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <openacc.h>

#ifndef SEED
#define SEED 12345
#endif

#ifndef NUM_TEST_CALLS
#define NUM_TEST_CALLS 10
#endif

// Test verification for OpenACC cache directive
int test_cache_directive() {
    int err = 0;
    const int size = 1024;
    int *data = (int*)malloc(size * sizeof(int));
    bool is_cached_correctly = true;

    // Initialize data
    for (int i = 0; i < size; ++i) {
        data[i] = i;
    }

    // Cache part of the array and perform operations
    #pragma acc data copy(data[0:size])
    {
        #pragma acc parallel loop
        for (int i = 0; i < size; ++i) {
            // Cache the middle segment of the array
            if (i == size / 4) {
                #pragma acc cache(data[size/4: size/2])
            }
            // Perform some dummy operations to mimic workload
            if (i >= size / 4 && i < (size / 4 + size / 2)) {
                data[i] += 1;
            }
        }
    }

    // Check if the data has been updated correctly,
    // assuming cache would help in faster data access and correct updates
    for (int i = size / 4; i < (size / 4 + size / 2); ++i) {
        if (data[i] != i + 1) {
            is_cached_correctly = false;
            break;
        }
    }

    if (!is_cached_correctly) {
        err = 1;
    }

    free(data);
    return err;
}

int main(){
    int failcode = 0;
    int failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed += test_cache_directive();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
    return failcode;
}