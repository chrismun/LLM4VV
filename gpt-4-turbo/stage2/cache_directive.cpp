#include <iostream>
#include <cstdlib>
#include <chrono>
#include <openacc.h>

#define N 100000
#define SEED 42
#define NUM_TEST_CALLS 10

int test_cache_directive() {
    int err = 0;
    int* largeArray = new int[N];
    srand(SEED);

    // Initialize the array with random data
    for (int i = 0; i < N; i++) {
        largeArray[i] = rand();
    }

    // Measure time without cache directive
    auto start1 = std::chrono::high_resolution_clock::now();
    #pragma acc parallel loop 
    for (int i = 0; i < N; i++) {
        largeArray[i] += 1;
    }
    auto end1 = std::chrono::high_resolution_clock::now();
    
    // Measure time with cache directive
    auto start2 = std::chrono::high_resolution_clock::now();
    #pragma acc parallel loop cache(largeArray[0:N])
    for (int i = 0; i < N; i++) {
        largeArray[i] += 1;
    }
    auto end2 = std::chrono::high_resolution_clock::now();

    // Compare execution times
    auto durationWithoutCache = std::chrono::duration_cast<std::chrono::microseconds>(end1 - start1).count();
    auto durationWithCache = std::chrono::duration_cast<std::chrono::microseconds>(end2 - start2).count();

    if (durationWithCache >= durationWithoutCache) {
        std::cout << "No observable performance improvement with cache directive.\n";
        err = 1;
    }
    else {
        std::cout << "Performance improvement observed with cache directive.\n";
    }

    delete[] largeArray;
    return err;
}

int main() {
    int failcode = 0;
    int failed = 0;

    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed += test_cache_directive();
    }
    
    if (failed != 0) {
        failcode += (1 << 0);
    }

    if (failcode == 0) {
        std::cout << "Test passed.\n";
    } else {
        std::cout << "Test failed.\n";
    }

    return failcode;
}