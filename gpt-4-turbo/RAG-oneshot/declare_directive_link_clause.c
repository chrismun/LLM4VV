#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "acc_testsuite.h"

#ifndef SEED
#define SEED 12345
#endif

#ifndef PRECISION
#define PRECISION 0.01
#endif

#ifndef N
#define N 1024
#endif

// Declare the global array to be linked.
#pragma acc declare link(global_array)

real_t global_array[N];

// Test function to validate the operation on the linked array.
int test_link_clause(){
    int err = 0;
    real_t *b = (real_t *)malloc(N * sizeof(real_t));

    // Initialize global_array with some values.
    for (int i = 0; i < N; ++i){
        global_array[i] = (real_t)rand() / (real_t)(RAND_MAX / 100);
        b[i] = 0.0;
    }

    // Use the global_array in a data region with a compute construct.
    #pragma acc data copy(global_array[0:N])
    {
        #pragma acc parallel loop
        for (int i = 0; i < N; ++i){
            global_array[i] = sqrt(global_array[i]);
        }

        #pragma acc update host(global_array[0:N])
    }

    // Validate the operation was conducted correctly.
    for (int i = 0; i < N; ++i){
        b[i] = sqrt(b[i]);
        if (fabs(global_array[i] - b[i]) > PRECISION){
            err += 1;
        }
    }
    
    free(b);
    return err;
}

int main(){
    int failcode = 0;
    srand(SEED);

    failcode |= test_link_clause();

    if (failcode) {
        printf("Test FAILED\n");
    } else {
        printf("Test PASSED\n");
    }
    return failcode;
}