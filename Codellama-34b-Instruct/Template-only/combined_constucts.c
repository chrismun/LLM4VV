#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Create a random number between 1 and 10
    int num = rand() % 10 + 1;

    // Create a parallel region with the num threads
    #pragma acc parallel num_threads(num)
    {
        // Create a data region with the num threads
        #pragma acc data num_threads(num)
        {
            // Create a loop with the num threads
            #pragma acc loop num_threads(num)
            for (int i = 0; i < num; i++) {
                // Do some work
                #pragma acc loop num_threads(num)
                for (int j = 0; j < num; j++) {
                    // Do some work
                }
            }
        }
    }

    // Check if the data region was executed correctly
    if (acc_get_num_threads() != num) {
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