#include <stdlib.h>
#include "acc_testsuite.h"

#ifndef T1
//T1:wait clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    float* h_a = (float*) malloc(SIZE * sizeof(float));
    float* h_b = (float*) malloc(SIZE * sizeof(float));
    float* h_c = (float*) malloc(SIZE * sizeof(float));

    // Initialize arrays
    for(int i = 0; i < SIZE; i++) {
        h_a[i] = (float)i;
        h_b[i] = (float)i;
    }

    // Process first vector addition without waiting
    #pragma acc kernels async(1) 
    for(int i = 0; i < SIZE; i++) {
        h_c[i] = h_a[i] + h_b[i];
    }

    // Process second vector addition and make it wait for completion of async queue 1
    #pragma acc kernels async(2) 
    for(int i = 0; i < SIZE; i++) {
        h_c[i] = h_c[i] + h_a[i];
    }
    #pragma acc wait(1,2)
    
    // Validate result
    for(int i = 0; i < SIZE; i++) {
        if( h_c[i] != (3 * (float)i) ){
            err = 1;
            break;
        }
    }

    free(h_a);
    free(h_b);
    free(h_c);

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
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}