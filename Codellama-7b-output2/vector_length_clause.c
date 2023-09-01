#include "acc_testsuite.h"
#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Generate a random vector length
    int vector_length = rand() % 10 + 1;

    // Create a vector with the generated length
    int vector[vector_length];

    // Initialize the vector with random values
    for (int i = 0; i < vector_length; i++){
        vector[i] = rand();
    }

    // Use the vector length clause to specify the length of the vector
    #pragma acc parallel loop vector_length(vector_length)
    for (int i = 0; i < vector_length; i++){
        // Do something with the vector elements
    }

    // Check if the vector length clause is working properly
    if (vector_length != vector_length){
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