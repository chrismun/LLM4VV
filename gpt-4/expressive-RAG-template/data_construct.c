#include "acc_testsuite.h"
#ifndef T1
// T1:data construct,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    int a[NUM_TEST_CALLS];
    int b[NUM_TEST_CALLS];
    int c[NUM_TEST_CALLS];

    //Initialize data
    for (int i = 0; i < NUM_TEST_CALLS; ++i){
        a[i] = i;
        b[i] = NUM_TEST_CALLS - i;
        c[i] = 0;
    }

    #pragma acc data copyin(a, b), copyout(c) 
    {
         #pragma acc parallel loop
         for ( int i = 0; i < NUM_TEST_CALLS; ++i){
             c[i] = a[i] + b[i];
         }
    }

    //verify data
    for (int i = 0; i < NUM_TEST_CALLS; ++i){
        if (c[i] != NUM_TEST_CALLS){
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