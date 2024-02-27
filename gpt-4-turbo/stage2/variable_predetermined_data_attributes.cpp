#include <iostream>
#include <cstdlib>
#include <openacc.h>

// Assuming acc_testsuite.h defines constants such as SEED and NUM_TEST_CALLS
// For simplicity, let's define them here, assuming they're not defined anywhere
#ifndef SEED
#define SEED 42
#endif

#ifndef NUM_TEST_CALLS
#define NUM_TEST_CALLS 10
#endif

// T1 Test: Variable predetermined data attributes.
int test1() {
    int error_count = 0;
    srand(SEED);

    int data[100];
    int host_accumulator = 0;

    // Initialize data with some values.
    for (int i = 0; i < 100; ++i) {
        data[i] = rand() % 100;
        host_accumulator += data[i]; // Accumulate values to check against later.
    }

    // The accumulator for the device.
    int device_accumulator = 0;

    // OpenACC parallel block.
    #pragma acc parallel loop reduction(+:device_accumulator)
    for (int i = 0; i < 100; ++i) {
        device_accumulator += data[i];
    }

    // At this point, 'device_accumulator' should equal 'host_accumulator' if the loop carried out as expected.
    if (host_accumulator != device_accumulator) {
        error_count++;
        std::cerr << "Test failed: Host accumulator (" << host_accumulator 
                  << ") does not match device accumulator (" << device_accumulator << ")." << std::endl;
    }

    return error_count;
}

int main() {
    int failcode = 0;
    int failed = 0;

    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed += test1();
    }

    if (failed != 0) {
        failcode += (1 << 0);
    }

    if (failcode == 0) {
        std::cout << "All tests passed." << std::endl;
    } else {
        std::cerr << "Some tests failed." << std::endl;
    }

    return failcode;
}