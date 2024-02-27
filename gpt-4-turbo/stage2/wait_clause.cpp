#include <iostream>
#include <stdlib.h>
#include <vector>

// This is where the OpenACC support is checked and included
#ifdef _OPENACC
#include <openacc.h>
#endif

#ifndef SEED
#define SEED 42
#endif

#ifndef NUM_TEST_CALLS
#define NUM_TEST_CALLS 5
#endif

// Simple function to initialize an array.
void init_array(std::vector<float> &arr) {
    for (size_t i = 0; i < arr.size(); ++i) {
        arr[i] = static_cast<float>(rand()) / RAND_MAX;
    }
}

// T1: wait clause, V:2.7-3.3
int test_wait_clause() {
    int err = 0;
    srand(SEED);

    constexpr size_t ARRAY_SIZE = 1024;
    std::vector<float> a(ARRAY_SIZE), b(ARRAY_SIZE);

    init_array(a); // Initialize the array with random values.

    // Task: Increment each element in 'a' and store in 'b', ensuring 'b' is calculated after 'a' is fully ready.
    #pragma acc data copyin(a[0:ARRAY_SIZE]) copyout(b[0:ARRAY_SIZE])
    {
        #pragma acc parallel loop async(1)
        for (size_t i = 0; i < ARRAY_SIZE; ++i) {
            b[i] = a[i] + 1.0f;
        }
        
        // Wait for the completion of the previous computation
        #pragma acc wait(1)
        
        #pragma acc parallel loop async(2)
        for (size_t i = 0; i < ARRAY_SIZE; ++i) {
            b[i] += 1.0f; // Further increment each element to verify that wait worked as intended.
        }
    }

    // Verify the results. After both operations, each element in 'b' should be the initial value in 'a' + 2.0.
    for (size_t i = 0; i < ARRAY_SIZE; ++i) {
        if (b[i] - (a[i] + 2.0f) > 1e-5) {
            err += 1;
            break;
        }
    }

    return err;
}

int main() {
    int failcode = 0;
    int failed;

    // Test the wait clause functionality
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed += test_wait_clause();
    }
    if (failed != 0) {
        failcode += (1 << 0);
    }

    return failcode;
}