#include <stdio.h>
#include <stdlib.h>
#include "acc_testsuite.h"
#ifndef T1
//T1:declare,V:2.7-3.3
int test1(){
    int err = 0;
    int test_var = 1;
    srand(SEED);
    // Use declare directive to create a copy of test_var in GPU memory
    #pragma acc declare copyin(test_var)
    
    // Running a parallel region to attempt utilizing test_var
    #pragma acc parallel num_workers(1)
    {
        // Assuming test_var is a simple flag. If present and properly initialized, flip its value.
        if (test_var == 1) {
            test_var = 2;
        }
    }

    // Checking if test_var was correctly modified.
    // Ideally, test_var should remain unchanged in host memory if the directive worked correctly
    // But since no direct data transfer is involved back to host memory, the verification should focus on error catching
    if (test_var != 1) {
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