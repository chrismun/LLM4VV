#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#ifndef SEED
#define SEED 123
#endif

#ifndef NUM_TEST_CALLS
#define NUM_TEST_CALLS 10
#endif

// Function to verify the result of the vector addition
int verify_result(float *a, float *b, float *c, int N, bool executed_in_parallel) {
    for (int i = 0; i < N; ++i) {
        float expected = a[i] + b[i];
        if (c[i] != expected) {
            if (executed_in_parallel) {
                printf("Error: Parallel execution did not produce the expected result at index %d\n", i);
            } else {
                printf("Error: Serial execution did not produce the expected result at index %d\n", i);
            }
            return 1;
        }
    }
    return 0;
}

// Test function to check the OpenACC kernels construct if clause
int test1(){
    int err = 0;
    const int N = 1000; // Size of arrays
    float a[N], b[N], c[N];
    bool condition;

    // Initialize arrays
    for (int i = 0; i < N; i++) {
        a[i] = (float)rand() / RAND_MAX;
        b[i] = (float)rand() / RAND_MAX;
        c[i] = 0.0f; // Important to initialize output array to zero
    }

    // Set condition to true and test parallel execution
    condition = true;
    #pragma acc kernels if(condition)
    for (int i = 0; i < N; i++) {
        c[i] = a[i] + b[i];
    }
    err += verify_result(a, b, c, N, condition);

    // Reset output array and condition
    for (int i = 0; i < N; i++) c[i] = 0.0f;
    condition = false;

    // Set condition to false and re-test, expecting serial execution
    #pragma acc kernels if(condition)
    for (int i = 0; i < N; i++) {
        c[i] = a[i] + b[i];
    }
    err += verify_result(a, b, c, N, condition);

    return err;
}

int main(){
    srand(SEED);
    int failcode = 0;
    int failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed += test1();
    }
    if (failed != 0) {
        failcode += (1 << 0);
    }
    return failcode;
}