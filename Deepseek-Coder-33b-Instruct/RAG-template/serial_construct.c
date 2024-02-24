#include <stdio.h>
#include "acc_testsuite.h"

#ifndef T1
//T1:serial,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    #pragma acc parallel num_gangs(1) copyin(err)
    {
        #pragma acc loop worker
        for(int i = 0; i < 100; i++) {
            #pragma acc serial
            {
                printf("Hello from thread %d\n", i);
            }
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