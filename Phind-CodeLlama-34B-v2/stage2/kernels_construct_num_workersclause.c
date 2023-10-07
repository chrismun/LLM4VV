#include "acc_testsuite.h"
#ifndef T1
/*T1:kernels construct num_workersclause,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);
    int num_workers = rand() % 100; // Random number between 0 and 99

    #pragma acc kernels num_workers(num_workers)
    {
        // Empty kernel to test num_workers clause
    }

    if (num_workers != 0){
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