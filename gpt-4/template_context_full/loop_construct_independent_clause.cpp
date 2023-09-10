#include "acc_testsuite.h"
#include <stdlib.h>
#include <cmath>

#ifndef T1
/*T1:loop construct independent clause,V:2.0-2.7*/
#define NUM_ELEMENTS 100
int test1(){
    int err = 0;
    srand(SEED);

    float *a = new float[NUM_ELEMENTS];
    float *b = new float[NUM_ELEMENTS];
    float *c = new float[NUM_ELEMENTS];
    float *res = new float[NUM_ELEMENTS];

    // Initialize arrays a and b 
    for(int i=0; i< NUM_ELEMENTS; i++){
        a[i] = rand() / (float)RAND_MAX;
        b[i] = rand() / (float)RAND_MAX;
        res[i] = a[i] + b[i];
    }

    // OpenACC parallel loop with independent
    #pragma acc parallel loop copy(a[0:NUM_ELEMENTS], b[0:NUM_ELEMENTS], c[0:NUM_ELEMENTS])
    for (int i=0; i<NUM_ELEMENTS; i++){
        c[i] = a[i] + b[i];  // Each iteration is independent
    }

    // Check if results are correct
    for(int i=0; i< NUM_ELEMENTS; i++){
        if(abs(c[i] - res[i]) > 1e-5){
            err = 1;
            break;
        }
    }

    // Cleanup
    delete[] a;
    delete[] b;
    delete[] c;
    delete[] res;

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