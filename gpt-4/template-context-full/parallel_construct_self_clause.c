#include "acc_testsuite.h"
#include <stdlib.h>
#include <stdio.h>

int test1(){
    int err = 0;
    srand(SEED);

    int a = rand();
    _Bool condition = (a % 2 == 0);

    #pragma acc parallel self(condition)
    {
        if(condition != acc_on_device(acc_device_host)){
            err = 1;
        }
    }
    return err;
}

int main(){
    int failcode = 0;
    int failed;
    
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
   
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }

    return failcode;
}