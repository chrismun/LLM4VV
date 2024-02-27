#include <iostream>
#include <vector>
#include <cmath>
#include <omp.h>

// Assuming OpenACC support in the environment and including OpenACC header
#include <openacc.h>

// Simple test to verify correctness of the OpenACC atomic construct
int test_atomic_update() {
    int err = 0; // Error flag, 0 indicates no error
    const int num_iterations = 10000; // Number of iterations for the atomic operation
    int shared_var = 0; // Shared variable to be updated atomically

    // Perform atomic updates on 'shared_var' in parallel
    #pragma acc parallel num_gangs(1) vector_length(256)
    #pragma acc loop
    for (int i = 0; i < num_iterations; ++i) {
        #pragma acc atomic update
        shared_var += 1;
    }

    // Check if the final value of 'shared_var' is correct
    if (shared_var != num_iterations) {
        std::cerr << "Test failed: Expected " << num_iterations << ", got " << shared_var << std::endl;
        err = 1; // Incorrect result, set error flag
    }

    return err;
}

int main() {
    int failcode = 0; // Failure code, 0 indicates success
    int failed; // Indicates if the test failed (non-zero)

    // Execute the atomic update test
    failed = test_atomic_update();
    if (failed != 0) {
        failcode = failcode + 1;
    }

    if (failcode == 0) {
        std::cout << "All tests passed successfully." << std::endl;
    } else {
        std::cout << "Some tests failed." << std::endl;
    }

    return failcode;
}