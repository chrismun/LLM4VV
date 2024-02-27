#include <stdio.h>
#include <stdlib.h>
#include <openacc.h> // Include OpenACC support

// Define constants for simplicity and reproducibility
#define SEED 123
#define NUM_ELEMENTS 1024
#define NUM_TEST_CALLS 10

// Helper function to initialize array
void init_array(int *a, int n) {
    for (int i = 0; i < n; i++) {
        a[i] = rand() % 100; // Assign a random value between 0 and 99
    }
}

// Test function to evaluate acc_wait
int test_acc_wait() {
    int err = 0;
    int* a = (int*) malloc(NUM_ELEMENTS * sizeof(int));
    
    // Initialize random seed and array
    srand(SEED);
    init_array(a, NUM_ELEMENTS);

    // Begin asynchronous region on device
    #pragma acc kernels async(1) copy(a[0:NUM_ELEMENTS])
    for (int i = 0; i < NUM_ELEMENTS; i++) {
        a[i] += 1; // A simple operation to verify
    }

    // Employ acc_wait to ensure completion of asynchronous region
    acc_wait(1);

    // Verify the operation is complete
    for (int i = 0; i < NUM_ELEMENTS; i++) {
        if (a[i] % 100 == 0) { // Based on initialization, success implies not 0 mod 100
            err++;
            break;
        }
    }

    free(a);
    return err;
}

// Main function to orchestrate tests
int main() {
    int failcode = 0;
    int failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed += test_acc_wait();
    }
    if (failed != 0) {
        failcode += 1; // Set first bit if failed
    }
    return failcode; // Return 0 if all tests passed
}