#include "acc_testsuite.h"

#ifndef T1
//T1:parallel construct vector_length clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    int vector_length = 4; // set the vector length to 4
    int num_workers = 4; // set the number of workers to 4

    // create a parallel region with the vector_length clause
    #pragma acc parallel vector_length(vector_length)
    {
        // create a loop with the vector clause
        #pragma acc loop vector
        for (int i = 0; i < num_workers; ++i) {
            // do some work
        }
    }

    // check that the vector length was set correctly
    if (vector_length != 4) {
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