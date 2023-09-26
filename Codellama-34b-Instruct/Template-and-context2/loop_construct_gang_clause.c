#include "acc_testsuite.h"

#ifndef T1
//T1:loop construct gang clause,V:2.7-3.3
int test1(){
    int err = 0;

    // Set up the loop construct
    int num_gangs = 4;
    int num_iterations = 100;
    int gang_size = 25;
    int iteration_size = 10;

    // Create a parallel region with the gang clause
    #pragma acc parallel num_gangs(num_gangs)
    {
        // Create a loop construct with the gang clause
        #pragma acc loop gang(num_gangs)
        for (int i = 0; i < num_iterations; i += iteration_size) {
            // Do some work
            #pragma acc loop
            for (int j = 0; j < gang_size; j++) {
                // Do some work
            }
        }
    }

    // Check that the loop construct was executed correctly
    for (int i = 0; i < num_iterations; i += iteration_size) {
        for (int j = 0; j < gang_size; j++) {
            // Check that the work was done correctly
            if (/* check work here */) {
                err++;
            }
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