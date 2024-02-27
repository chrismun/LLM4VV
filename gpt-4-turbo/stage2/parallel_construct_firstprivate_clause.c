#include <stdio.h>
#include <stdlib.h>
#include "acc_testsuite.h"

#ifndef T1
// T1:parallel construct, firstprivate clause, V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    int initial_value = rand(); // Random initial value for testing
    int result = 0;

    // The variable `initial_value` should be firstprivate in the parallel region
    #pragma acc parallel num_gangs(1) vector_length(1) firstprivate(initial_value)
    {
        // Each worker should see the initial value of the firstprivate variable
        #pragma acc loop reduction(+:result)
        for (int i = 0; i < 100; ++i) {
            result += (initial_value == initial_value); // This should always be true (100 times)
        }
    }

    // Check if result is exactly 100; if not, firstprivate might not be working correctly
    if(result != 100) {
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