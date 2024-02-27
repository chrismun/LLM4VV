#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <openacc.h>

#define SEED 12345
#define NUM_ELEMENTS 1024
#define NUM_TEST_CALLS 10

// Utility function to generate random data
void generate_random_data(int *data, int size) {
    for (int i = 0; i < size; i++) {
        data[i] = rand() % 100; // Random numbers between 0 and 99
    }
}

// Test function to verify OpenACC loop construct with independent clause
int test_independent_reduction() {
    int err = 0;
    int *data = (int *) malloc(NUM_ELEMENTS * sizeof(int));
    srand(SEED);
    generate_random_data(data, NUM_ELEMENTS);

    int seq_sum = 0;
    for (int i = 0; i < NUM_ELEMENTS; i++) {
        seq_sum += data[i];
    }

    int sum = 0;
    #pragma acc parallel loop reduction(+:sum) independent
    for (int i = 0; i < NUM_ELEMENTS; i++) {
        sum += data[i];
    }

    // Verification
    if (sum != seq_sum) {
        err = 1; // Error if the parallel sum doesn't match sequential sum
    }

    free(data);
    return err;
}

int main() {
    int failcode = 0;
    int failed = 0;

    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed += test_independent_reduction();
    }
    if (failed != 0) {
        failcode = failcode + (1 << 0);
        printf("Test FAILED\n");
    } else {
        printf("All tests PASSED\n");
    }
    return failcode;
}