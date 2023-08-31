#include "acc_testsuite.h"
#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    int num_gangs = 2;
    int num_workers = 4;
    int num_gangs_expected = 2;

    #pragma acc parallel num_gangs(num_gangs) num_workers(num_workers)
    {
        #pragma acc loop gang(num_gangs_expected)
        for (int i = 0; i < num_gangs_expected; i++) {
            // Do some work
        }
    }

    if (num_gangs != num_gangs_expected) {
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