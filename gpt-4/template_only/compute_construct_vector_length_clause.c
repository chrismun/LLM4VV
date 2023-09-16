#include "acc_testsuite.h"
#ifndef T1
//T1:compute construct vector_length clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    // Initialize test vector
    int vector_length = 10;
    float a[vector_length];
    for (int i=0; i<vector_length; ++i) {
        a[i] = (float)i;
    }

    // Use OpenACC compute construct with vector_length clause
    #pragma acc parallel loop vector_length(128)
    for (int i=0; i<vector_length; ++i) {
        a[i] *= a[i];
    }

    // Check results (should be square of initial values)
    for (int i=0; i<vector_length; ++i) {
        if(a[i] != ((float)(i*i))){
            err = 1;
            break;
        }
    }
    return err;
}
#endif

int main(){
    int failcode = 0;
#ifndef T1
    int failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed += test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}