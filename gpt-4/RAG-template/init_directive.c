#include "acc_testsuite.h"
#include <stdlib.h>

int test_parallel_directive(){
    int err = 0;
    srand(SEED);

    int a = 5;
    int b = 0;

    #pragma acc parallel copyin(a) copyout(b)
    {
        b = a;
    }
    if(b != a){
        err = 1;
    }

    return err;
}

int test_data_directive(){
    int err = 0;
    srand(SEED);

    int a = 5;
    int b = 0;

    #pragma acc data copyin(a) copyout(b)
    {
        b = a;
    }
    if(b != a){
        err = 1;
    }

    return err;
}

int main(){
    int failcode = 0;
    int failed;
    
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test_parallel_directive();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
    
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test_data_directive();
    }
    if (failed != 0){
        failcode = failcode + (1 << 1);
    }

    return failcode;
}