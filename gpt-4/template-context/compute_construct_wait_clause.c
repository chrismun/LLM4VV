#include "acc_testsuite.h"
#include <stdlib.h>
#include <stdio.h>

// T1: compute construct wait clause
int test1(){
    int err = 0;

    // Create large arrays to increase execution time 
    int N = 1<<20;
    float* a = (float*) malloc(N * sizeof(float));
    float* b = (float*) malloc(N * sizeof(float));
    float* res1 = (float*) malloc(N * sizeof(float));
    float* res2 = (float*) malloc(N * sizeof(float));

    srand(SEED);
    
    // Seed the arrays with random values
    for(int i=0; i<N; i++){
        a[i] = (float) rand() / RAND_MAX;
        b[i] = (float) rand() / RAND_MAX;
    }

    // Compute on host
    for(int i = 0; i < N; ++i){
        res1[i] = a[i] + b[i];
    }
    
    // Compute on device
    #pragma acc parallel loop wait deviceptr(a,b)
    for(int i = 0; i < N; ++i){
        res2[i] = a[i] + b[i];
    }

    // Compare results
    for (int i = 0; i < N; ++i){
        if (abs(res1[i] - res2[i]) > 1e-5){
            err = 1;
            break;
        }
    }

    // Free allocated memory
    free(a);
    free(b);
    free(res1);
    free(res2);
    
    return err;
}

int main(){
    int failcode = 0;
    int failed = 0;
    
    // Repeated NUM_TEST_CALLS times to check consistency
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed += test1();
    }
    
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }

    return failcode;
}