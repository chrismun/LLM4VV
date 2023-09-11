c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <acc/acc.h>

#define NUM_TEST_CALLS 100
#define SEED 12345

int test1() {
    int err = 0;
    srand(SEED);

    // Define a simple function that can be compiled for the accelerator
    void acc_func(int *a, int *b) {
        *a = *b + 1;
    }

    // Define a routine directive for the function
    #pragma acc routine(acc_func) gang

    // Call the function in a compute region
    #pragma acc parallel
    {
        int a = 0;
        int b = 1;
        acc_func(&a, &b);
    }

    // Check the result
    if (a != 2) {
        err = 1;
    }

    return err;
}

int main() {
    int failcode = 0;
    int failed;

    // Run the test function multiple times
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed = test1();
        if (failed != 0) {
            failcode = failcode + (1 << 0);
        }
    }

    // Return the failure code
    return failcode;
}