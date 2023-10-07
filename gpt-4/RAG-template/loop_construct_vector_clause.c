#include "acc_testsuite.h"

#ifndef T1
//T1:loop construct vector clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    float a[N], b[N], c[N]; 
    int i;
    // initialize the arrays 
    for (i = 0; i < N; i++) {
        a[i] = rand() / (float)RAND_MAX;
        b[i] = rand() / (float)RAND_MAX;
        c[i] = 0;
    }

    #pragma acc parallel
    {
    #pragma acc loop vector
    for (i = 0; i < N; i++)
        c[i] = a[i] + b[i];
    }
  
    // check for errors
    for (i = 0; i < N; i++) {
        if (fabsf((a[i] + b[i]) - c[i]) > TOLERANCE){
            err = 1;
        }
    }
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