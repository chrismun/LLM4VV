#include <stdio.h>
#include "acc_testsuite.h"

#ifndef T1
// T1: kernels construct num_gangs clause, V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    const int size = 100;
    int a[size];
    int expected = 0;
    int actual = 0;

    // Initialize data
    for (int i = 0; i < size; ++i){
        a[i] = rand() % 100;
        expected += a[i];
    }

    // Using OpenACC to parallelize and specify number of gangs
    #pragma acc kernels num_gangs(64)
    for (int i = 0; i < size; ++i){
        #pragma acc atomic
        actual += a[i];
    }

    // Compare results
    if (actual != expected){
        err++;
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