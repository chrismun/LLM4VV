#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define ARRAY_SIZE 1000
#define SEED 42
#define NUM_TEST_CALLS 10

int test_create_clause() {
    int err = 0;
    int *a = (int*) malloc(ARRAY_SIZE * sizeof(int));

    // Initialize array with -1 to clearly distinguish uninitialized values
    // on the device side if they exist.
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        a[i] = -1;
    }

    #pragma acc data create(a[0:ARRAY_SIZE])
    {
        #pragma acc parallel loop
        for (int i = 0; i < ARRAY_SIZE; ++i) {
            a[i] = 0; // This should never happen since 'a' is only created but not copied
        }
    } // End of the data region

    // Check if any value is not -1, which means it got changed erroneously
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (a[i] != -1) {
            err = 1;
            break;
        }
    }

    free(a);
    return err;
}

int main() {
    int failcode = 0;
    int failed = 0;

    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed += test_create_clause();
    }

    if (failed != 0) {
        failcode = 1;
    }

    return failcode;
}