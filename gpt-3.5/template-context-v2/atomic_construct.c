#include "acc_testsuite.h"
#include <stdlib.h>
#include <stdio.h>

#ifndef T1
// T1:atomic construct, V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    int atomic_var = 0;
    #pragma acc parallel loop
    for (int i = 0; i < 1000; i++){
        #pragma acc atomic update
        atomic_var += 1;
    }

    if (atomic_var != 1000){
        err = 1;
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
        failed += test1();
    }

    if (failed != 0){
        failcode += (1 << 0);
    }
#endif

    return failcode;
}