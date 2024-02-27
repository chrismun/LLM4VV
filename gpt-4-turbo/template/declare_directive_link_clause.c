#include <stdlib.h>
#include <stdio.h>
#include "acc_testsuite.h"

#ifndef T1
// T1: declare directive, link clause, V:2.7-3.3
int global_var = 0;

#pragma acc declare create(global_var)

int test1(){
    int err = 0;
    int host_var = 0;
    srand(SEED);

    #pragma acc parallel num_gangs(1) vector_length(1)
    {
        #pragma acc loop gang vector
        for (int i = 0; i < 1; ++i){
            global_var += 1;
        }
    }

    // Copying data back to the host
    #pragma acc update host(global_var)

    // Verifying the result
    if (global_var != 1) {
        err = 1;
        printf("Test1 failed: global_var expected 1, got %d\n", global_var);
    }

    // Reset global_var for next call
    global_var = 0;
    
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