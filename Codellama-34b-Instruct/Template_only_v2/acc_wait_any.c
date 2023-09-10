#include "acc_testsuite.h"

#ifndef T1
//T1:acc wait any,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    // Create a parallel region with 4 threads
    #pragma acc parallel num_threads(4)
    {
        // Create a wait directive that waits for any of the threads to complete
        #pragma acc wait any

        // Do some work in each thread
        #pragma acc loop
        for (int i = 0; i < 10; i++) {
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