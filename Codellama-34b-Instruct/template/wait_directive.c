#include "acc_testsuite.h"

#ifndef T1
//T1:wait directive,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    // Create a parallel region with 2 threads
    #pragma acc parallel num_threads(2)
    {
        // Create a wait directive that waits for all threads to reach this point
        #pragma acc wait

        // Do some work
        int i = 0;
        #pragma acc loop
        for (i = 0; i < 10; i++) {
            printf("Thread %d: %d\n", acc_thread_id(), i);
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