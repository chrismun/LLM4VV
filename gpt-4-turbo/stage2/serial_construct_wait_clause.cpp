#include <iostream>
#include <stdlib.h>
#include <openacc.h>
#include <chrono>
#include <thread>

// Assuming these are defined in acc_testsuite.h or similar.
// For the sake of this example, let's mock their behavior.
#define SEED 1234
#define NUM_TEST_CALLS 1

int test1() {
    int err = 0;
    srand(SEED);

    const int size = 10000;
    float *a = new float[size];
    float *b = new float[size];

    // Initialize vectors
    for(int i = 0; i < size; ++i) {
        a[i] = static_cast<float>(rand()) / RAND_MAX;
        b[i] = 0.0f;
    }

    // Perform some work in an OpenACC region and wait for its completion
    #pragma acc data copyin(a[0:size]) copyout(b[0:size])
    {
        #pragma acc parallel loop
        for(int i = 0; i < size; ++i) {
            b[i] = a[i] * 2.0f; // Some work that should be done in parallel
        }

        // Wait for all preceding asynchronous activities in this construct to complete
        #pragma acc wait
    }

    // After waiting, check if the work was done correctly
    for(int i = 0; i < size; ++i) {
        if(b[i] != a[i] * 2.0f) {
            err++;
        }
    }

    delete[] a;
    delete[] b;

    return err;
}

int main() {
    int failcode = 0;
    int failed;
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed = failed + test1();
    }
    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }

    return failcode;
}