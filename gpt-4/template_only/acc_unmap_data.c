#include <openacc.h>
#include <stdlib.h>
#include <stdio.h>
#include "acc_testsuite.h"

#define N 1024
#define NUM_TEST_CALLS 10
#define SEED 12345

// Test function: perform a vector addition
void vector_add(float* a, float* b, float* c, int n) {
    #pragma acc data copyin(a[0:n], b[0:n]) copyout(c[0:n])
    {
        #pragma acc parallel loop
        for(int i=0; i<n; ++i) {
            c[i] = a[i] + b[i];
        }
    }
}

// Test: check if the vector addition is computed correctly
int test() {
    float *a = (float*) malloc(sizeof(float) * N);
    float *b = (float*) malloc(sizeof(float) * N);
    float *c = (float*) malloc(sizeof(float) * N);

    // Initialize vectors a and b
    for(int i=0; i<N; ++i) {
        a[i] = rand()/(float)RAND_MAX;
        b[i] = rand()/(float)RAND_MAX;
    }

    // Call vector_add
    vector_add(a, b, c, N);

    // Check the result
    for(int i=0; i<N; ++i) {
        if(c[i] != a[i] + b[i]) {
            // An error occurred
            return 1;
        }
    }

    // No error
    return 0;
}

int main() {
    srand(SEED);

    int failcode = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        if(test() != 0){
            failcode += 1;
        }
    }

    return failcode;
}