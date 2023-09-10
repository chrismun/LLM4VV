#include <stdlib.h>
#include <stdio.h>
#include <openacc.h>
#include "acc_testsuite.h"

#ifndef T1
/*T1:acc async test,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);
    int data[10];
    int wait_arg = 1;

    #pragma acc parallel async(wait_arg)
    for(int i=0; i<10; i++){
        data[i] = i;
    }

    //check if all acc operations have not completed
    if(acc_async_test(wait_arg) == 0){
        err = 1;
    }

    //wait for all acc operations to complete
    acc_wait(wait_arg);

    //check if all acc operations have completed
    if(acc_async_test(wait_arg) == 0){
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
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}