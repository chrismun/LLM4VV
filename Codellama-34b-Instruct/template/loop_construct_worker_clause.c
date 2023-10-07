#include "acc_testsuite.h"

#ifndef T1
//T1:loop construct worker clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    int num_workers = 4;
    int num_iterations = 10;
    int num_threads = 2;

    #pragma acc parallel num_workers(num_workers) num_threads(num_threads)
    {
        #pragma acc loop worker(num_iterations)
        for (int i = 0; i < num_iterations; i++) {
            // Do some work here
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