#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>
#include "acc_testsuite.h"

#ifndef T1
//T1:compute construct num_workersclause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    int num_workers = rand() % 10 + 1;

    #pragma acc parallel num_workers(num_workers)
    {
        int worker = acc_get_worker_num();
        if (worker >= num_workers) {
            err = 1;
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