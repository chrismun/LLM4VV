#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#define SEED 12345
#define NUM_ELEMENTS 1024
#define NUM_TEST_CALLS 10

int test1(){
    int err = 0;
    srand(SEED);
    float *a, *b, *c, *d, *result_ab, *result_cd;
    a = (float *)malloc(NUM_ELEMENTS * sizeof(float));
    b = (float *)malloc(NUM_ELEMENTS * sizeof(float));
    c = (float *)malloc(NUM_ELEMENTS * sizeof(float));
    d = (float *)malloc(NUM_ELEMENTS * sizeof(float));
    result_ab = (float *)malloc(NUM_ELEMENTS * sizeof(float));
    result_cd = (float *)malloc(NUM_ELEMENTS * sizeof(float));

    // Initialize arrays
    for (int i = 0; i < NUM_ELEMENTS; i++) {
        a[i] = rand() / (float)RAND_MAX;
        b[i] = rand() / (float)RAND_MAX;
        c[i] = rand() / (float)RAND_MAX;
        d[i] = rand() / (float)RAND_MAX;
    }

    // Perform asynchronous vector addition on two different streams
#pragma acc parallel loop async(1) copyin(a[0:NUM_ELEMENTS], b[0:NUM_ELEMENTS]) copyout(result_ab[0:NUM_ELEMENTS])
    for (int i = 0; i < NUM_ELEMENTS; i++) {
        result_ab[i] = a[i] + b[i];
    }

#pragma acc parallel loop async(2) copyin(c[0:NUM_ELEMENTS], d[0:NUM_ELEMENTS]) copyout(result_cd[0:NUM_ELEMENTS])
    for (int i = 0; i < NUM_ELEMENTS; i++) {
        result_cd[i] = c[i] + d[i];
    }

    // Wait for all asynchronous operations to complete 
#pragma acc wait

    // Validation
    for (int i = 0; i < NUM_ELEMENTS; i++) {
        if (result_ab[i] != a[i] + b[i] || result_cd[i] != c[i] + d[i]) {
            err++;
        }
    }

    free(a);
    free(b);
    free(c);
    free(d);
    free(result_ab);
    free(result_cd);

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
        printf("Test FAILED\n");
    } else {
        printf("Test PASSED\n");
    }
    return failcode;
}