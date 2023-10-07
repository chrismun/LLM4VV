#include "acc_testsuite.h"
#ifndef T1
/*T1:serial construct num_workersclause,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);

    int num_workers = rand() % 10 + 1; // Random number between 1 and 10

    #pragma acc serial num_workers(num_workers)
    {
        // Do some work here
    }

    if (/* Check if the num_workers clause is not working properly */){
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