#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Generate a random number of iterations for the loop
    int num_iterations = rand() % 100 + 1;

    // Create a loop with the auto clause
    #pragma acc loop auto
    for (int i = 0; i < num_iterations; i++) {
        // Do some work
    }

    // Check if the loop iterations are data-independent
    if (acc_is_data_independent(num_iterations)) {
        // If the loop iterations are data-independent, treat the auto clause as if it is an independent clause
        #pragma acc loop independent
        for (int i = 0; i < num_iterations; i++) {
            // Do some work
        }
    } else {
        // If the loop iterations are not data-independent, treat the auto clause as if it is a seq clause
        #pragma acc loop seq
        for (int i = 0; i < num_iterations; i++) {
            // Do some work
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