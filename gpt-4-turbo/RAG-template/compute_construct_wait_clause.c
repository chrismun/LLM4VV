#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <openacc.h>

#define SEED 123
#define NUM_TEST_CALLS 10
#define N 1024

// Mock acc_testsuite for simplicity. Implement as required.
#define acc_testsuite_h
int NUM_TEST_CALLS = 10;

#ifndef T1
// T1:{compute_construct_wait_clause},V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    float *a = (float *)malloc(N * sizeof(float));
    float *b = (float *)malloc(N * sizeof(float));
    float *c = (float *)malloc(N * sizeof(float));

    // Initialize arrays
    for(int i = 0; i < N; ++i) {
        a[i] = rand() / (float)RAND_MAX;
        b[i] = rand() / (float)RAND_MAX;
        c[i] = 0.0f; // initialize to 0
    }

    // Perform vector addition in parallel and asynchronously.
    #pragma acc kernels async(1) copyin(a[0:N],b[0:N]) copyout(c[0:N])
    for(int i = 0; i < N; ++i) {
        c[i] = a[i] + b[i];
    }

    // Wait for the asynchronous compute to complete
    #pragma acc wait(1)

    // Verify results
    for(int i = 0; i < N; ++i) {
        if(abs(c[i] - (a[i] + b[i])) > 1e-5) {
            err++;
            break;
        }
    }

    free(a);
    free(b);
    free(c);

    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed;
#ifndef T1
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode | (1 << 0);
    }
#endif
    return failcode;
}