#include "acc_testsuite.h"

#ifndef T1
//T1:compute construct num_gangs clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    int num_gangs = 10;
    int num_workers = 10;
    int num_threads = 10;

    #pragma acc parallel num_gangs(num_gangs)
    {
        int i = 0;
        #pragma acc loop gang
        for (i = 0; i < num_workers; i++) {
            #pragma acc loop worker
            for (int j = 0; j < num_threads; j++) {
                // Do some work
            }
        }
    }

    if (num_gangs != 10) {
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