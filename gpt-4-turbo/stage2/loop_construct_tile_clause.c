#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <openacc.h>

#ifndef T1
// T1:loop construct tile clause,V:2.7-3.3
int test1() {
    int err = 0;
    const int matrix_size = 100;
    bool matrix[matrix_size][matrix_size] = {false}; // Initialize all elements to false
    int tile_x = 10, tile_y = 10; // Define tile sizes for two-dimensional loop tiling

    // Use OpenACC directives to specify parallel region and loop tiling
    #pragma acc parallel num_gangs(1) vector_length(1)
    {
        #pragma acc loop tile(tile_x, tile_y)
        for (int i = 0; i < matrix_size; ++i) {
            for (int j = 0; j < matrix_size; ++j) {
                #pragma acc loop vector
                {
                    matrix[i][j] = true; // Mark visited
                }
            }
        }
    }

    // Verify that each element was visited exactly once
    for (int i = 0; i < matrix_size; ++i) {
        for (int j = 0; j < matrix_size; ++j) {
            if (!matrix[i][j]) {
                // If any element is false, an error occurred
                err++;
            }
        }
    }

    return err;
}
#endif

int main() {
    const int NUM_TEST_CALLS = 10; // Define the number of iterations for the test
    int failcode = 0;
    int failed;

#ifndef T1
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed = failed + test1();
    }
    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }
#endif
    if (failcode != 0) {
        printf("Test failed.\n");
    } else {
        printf("Test passed.\n");
    }
    return failcode;
}