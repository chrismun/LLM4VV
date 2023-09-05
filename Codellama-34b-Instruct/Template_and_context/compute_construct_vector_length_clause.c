#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    int vector_length = 4;
    int num_workers = 4;
    int num_vectors = 16;

    // Create a parallel region with the vector_length clause
    #pragma acc parallel num_workers(num_workers) vector_length(vector_length)
    {
        // Create a loop with the vector clause
        #pragma acc loop vector
        for (int i = 0; i < num_vectors; i++) {
            // Do some work
        }
    }

    // Check that the vector length was set correctly
    if (acc_get_vector_length() != vector_length) {
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