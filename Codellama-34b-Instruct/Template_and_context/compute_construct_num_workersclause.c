#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    int num_workers = 4; // set the number of workers to 4
    int num_gangs = 2; // set the number of gangs to 2

    // create a parallel region with 4 workers and 2 gangs
    #pragma acc parallel num_workers(num_workers) num_gangs(num_gangs)
    {
        // do some work
    }

    // check if the number of workers is correct
    if (acc_get_num_workers() != num_workers) {
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