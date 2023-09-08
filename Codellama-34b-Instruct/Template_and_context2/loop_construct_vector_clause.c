#include "acc_testsuite.h"

#ifndef T1
//T1:loop construct vector clause,V:2.7-3.3
int test1(){
    int err = 0;
    int vector_length = 4;
    int num_iterations = 100;

    // Set up the data
    int* data = (int*)malloc(sizeof(int) * num_iterations);
    for (int i = 0; i < num_iterations; i++) {
        data[i] = i;
    }

    // Run the loop with the vector clause
    #pragma acc parallel loop vector(vector_length)
    for (int i = 0; i < num_iterations; i++) {
        data[i] += 1;
    }

    // Check the results
    for (int i = 0; i < num_iterations; i++) {
        if (data[i] != i + 1) {
            err++;
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