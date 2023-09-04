#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    int vector_length = 4;
    int num_vectors = 10;
    int num_workers = 10;

    // Create a vector of random integers
    int* data = (int*)malloc(sizeof(int) * num_vectors * vector_length);
    for (int i = 0; i < num_vectors * vector_length; i++) {
        data[i] = rand() % 100;
    }

    // Create a parallel region with the vector_length clause
    #pragma acc parallel num_workers(num_workers) vector_length(vector_length)
    {
        // Create a loop with the vector clause
        #pragma acc loop vector
        for (int i = 0; i < num_vectors; i++) {
            // Perform some vector operation on the data
            data[i * vector_length] = data[i * vector_length] + 1;
        }
    }

    // Check that the vector operation was performed correctly
    for (int i = 0; i < num_vectors; i++) {
        if (data[i * vector_length] != data[i * vector_length] + 1) {
            err = 1;
            break;
        }
    }

    free(data);

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