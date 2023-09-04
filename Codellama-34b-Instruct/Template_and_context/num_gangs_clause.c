#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <openacc.h>

#define NUM_TEST_CALLS 10

int test1() {
    int err = 0;
    srand(SEED);

    // Initialize data
    int num_gangs = 10;
    int num_workers = 10;
    int num_vectors = 10;
    int num_iterations = 100;
    int* data = (int*)malloc(num_iterations * sizeof(int));
    for (int i = 0; i < num_iterations; i++) {
        data[i] = i;
    }

    // Set up OpenACC environment
    acc_init(acc_device_default);
    acc_set_num_gangs(num_gangs);
    acc_set_num_workers(num_workers);
    acc_set_num_vectors(num_vectors);

    // Run kernel
    acc_parallel(num_gangs, num_workers, num_vectors, num_iterations, data);

    // Check results
    for (int i = 0; i < num_iterations; i++) {
        if (data[i] != i) {
            err = 1;
            break;
        }
    }

    // Clean up
    free(data);
    acc_shutdown(acc_device_default);

    return err;
}

int main() {
    int failcode = 0;
    int failed;

    // Run test
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; x++) {
        failed = failed + test1();
    }
    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }

    return failcode;
}