#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define SEED 42
#define NUM_ELEMENTS 1024
#define NUM_TEST_CALLS 10

int test1(){
    int err = 0;
    srand(SEED);

    float *a = (float *)malloc(NUM_ELEMENTS * sizeof(float));
    float *b = (float *)malloc(NUM_ELEMENTS * sizeof(float));
    float *c = (float *)malloc(NUM_ELEMENTS * sizeof(float));
    float *seq_c = (float *)malloc(NUM_ELEMENTS * sizeof(float));

    // Initialize arrays
    for(int i = 0; i < NUM_ELEMENTS; ++i){
        a[i] = rand() / (float)RAND_MAX;
        b[i] = rand() / (float)RAND_MAX;
        seq_c[i] = a[i] + b[i]; // Expected outcome
    }

    // Perform vector addition in parallel and wait for completion
#pragma acc parallel loop copyin(a[0:NUM_ELEMENTS],b[0:NUM_ELEMENTS]) copyout(c[0:NUM_ELEMENTS]) async(1)
    for(int i = 0; i < NUM_ELEMENTS; ++i){
        c[i] = a[i] + b[i];
    }

#pragma acc wait(1)

    // Verify results
    for(int i = 0; i < NUM_ELEMENTS; ++i){
        if(abs(c[i] - seq_c[i]) > 1e-5){
            err++;
            break;
        }
    }

    free(a);
    free(b);
    free(c);
    free(seq_c);

    return err;
}

int main(){
    int failcode = 0;
#ifndef T1
    int failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed += test1();
    }
    if (failed != 0){
        failcode |= (1 << 0);
    }
#endif
    if (failcode == 0){
        printf("All tests passed.\n");
    } else {
        printf("Some tests failed.\n");
    }
    return failcode;
}