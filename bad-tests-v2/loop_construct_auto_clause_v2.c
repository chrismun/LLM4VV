#include <openacc.h>
#include <stdlib.h>
#include <stdbool.h>
#include "acc_testsuite.h"

#define NUM_TEST_CALLS 100

// Test the implementation of 'auto' clause in OpenACC loop construct
bool test_auto_clause() {
    int n = 100;
    int a[n], b[n], c[n];

    // Initialize arrays
    for (int i = 0; i < n; i++) {
        a[i] = rand() % 100;
        b[i] = rand() % 100;
        c[i] = 0;
    }

    // Add arrays a and b, the result stored in array c
    // Here, 'auto' clause tells the compiler to analyze the loop and decide
    // the parallelization factor
    #pragma acc parallel loop auto
    for (int i = 0; i < n; i++) {
        c[i] = a[i] + b[i];
    }

    // Verify the results
    for (int i = 0; i < n; i++) {
        if (c[i] != (a[i] + b[i])) {
            return false;
        }
    }

    return true;
}

int main() {
    srand(SEED);
    int failcode = 0;
    
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        if (!test_auto_clause()){
            failcode = 1;
            break;
        }
    }

    // Return failcode
    // 0: all tests passed
    // 1: one or more tests failed
    return failcode;
}