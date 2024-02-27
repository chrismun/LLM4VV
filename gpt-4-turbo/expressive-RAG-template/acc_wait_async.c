#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

// Seed for initialization of random values - ensure reproducibility
#define SEED 12345
#define NUM_TEST_CALLS 1

// Function to test acc_wait_async implementation
int test_acc_wait_async() {
    int err = 0;
    const int size = 1024;
    float *a = (float*) malloc(size * sizeof(float));
    float *b = (float*) malloc(size * sizeof(float));

    // Initialize arrays with dummy data
    for (int i = 0; i < size; i++) {
        a[i] = (float)i;
        b[i] = 0.0f;
    }

    // Begin parallel region, offload to device
    #pragma acc data copy(a[0:size], b[0:size])
    {
        // First computation, async queue 1
        #pragma acc parallel loop async(1)
        for (int i = 0; i < size; i++) {
            b[i] = a[i] + 1;
        }
        
        // Using acc_wait_async to synchronize between queues
        acc_wait_async(1, 2);
        
        // Second computation, depends on the first, async queue 2
        #pragma acc parallel loop async(2)
        for (int i = 0; i < size; i++) {
            b[i] = b[i] * 2;
        }
    }
    
    // Wait for all operations to complete
    acc_wait_all();

    // Verification
    for (int i = 0; i < size; i++) {
        if (b[i] != ((a[i] + 1) * 2)) {
            err++;
        }
    }

    free(a);
    free(b);

    return err;
}

int main() {
    int failcode = 0;
    int failed = 0;

    // Execute the test multiple times if necessary
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed += test_acc_wait_async();
    }
    
    // Encode test result in failcode
    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }
    
    // Zero indicates success, non-zero indicates failure
    return failcode;
}