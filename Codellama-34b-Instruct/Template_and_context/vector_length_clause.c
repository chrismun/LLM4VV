#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Create a vector of random integers
    int *vec = (int *)malloc(sizeof(int) * 10);
    for (int i = 0; i < 10; i++) {
        vec[i] = rand();
    }

    // Create a compute region with the vector length clause
    #pragma acc parallel loop vector_length(10)
    for (int i = 0; i < 10; i++) {
        // Do some computation on the vector
        vec[i] = vec[i] + 1;
    }

    // Check that the vector length is correct
    if (vec[0] != 11) {
        err = 1;
    }

    // Free the vector
    free(vec);

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