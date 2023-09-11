#include "acc_testsuite.h"

#ifndef T1
//T1:parallel construct num_gangs clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    int num_gangs = 1;
    int num_workers = 1;
    int num_vectors = 1;

    #pragma acc parallel num_gangs(num_gangs) num_workers(num_workers) num_vectors(num_vectors)
    {
        // Do some work
    }

    if (num_gangs != 1 || num_workers != 1 || num_vectors != 1) {
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