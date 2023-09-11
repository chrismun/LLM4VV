#include "acc_testsuite.h"

#ifndef T1
//T1:serial construct vector_length clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    int vector_length = 4;
    int num_workers = 10;
    int num_vectors = 10;

    // Create a serial construct with a vector_length clause
    #pragma acc serial vector_length(vector_length)
    {
        // Create a loop construct with a vector clause
        #pragma acc loop vector
        for (int i = 0; i < num_workers; i++) {
            // Do some work
        }
    }

    // Check that the vector length was set correctly
    if (vector_length != acc_get_vector_length()) {
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