#include <iostream>
#include <cstdlib>
#include <cmath>

// Define SEED for reproducibility
#define SEED 123
// Define the number of elements in the array and number of test calls
#define N 1024
#define NUM_TEST_CALLS 10

int test1(){
    int err = 0;
    srand(SEED);

    // Create and initialize an array with random values
    double *a = new double[N];
    for (int i = 0; i < N; ++i) {
        a[i] = rand() % 100;  // Random values between 0 and 99
    }

    double reduction_result = 0;
    double expected_result = 0;

    // Calculate expected_result using CPU
    for (int i = 0; i < N; ++i){
        expected_result += a[i];
    }

    // Using OpenACC to perform reduction on the array
#pragma acc kernels copy(reduction_result) create(a[:N]) reduction(+:reduction_result)
    {
        for (int i = 0; i < N; ++i) {
            reduction_result += a[i];
        }
    }

    // Verifying the result of the OpenACC reduction with the expected CPU result
    if (fabs(reduction_result - expected_result) > 1e-5) { // Using a tolerance to account for floating-point arithmetic inaccuracies
        err++;
    }

    // Cleanup
    delete[] a;

    return err;
}

int main(){
    int failcode = 0;
    int failed;

    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }

    if (failcode == 0) {
        std::cout << "PASS: OpenACC kernels construct reduction clause works as expected." << std::endl;
    } else {
        std::cout << "FAIL: OpenACC kernels construct reduction clause does not work as expected. Failures: " << failed << std::endl;
    }

    return failcode;
}