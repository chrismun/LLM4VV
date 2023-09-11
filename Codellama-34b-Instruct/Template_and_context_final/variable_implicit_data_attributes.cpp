#include "acc_testsuite.h"

#ifndef T1
//T1:variable implicit data attributes,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    // Create a compute construct with a reduction clause
    #pragma acc parallel reduction(+:sum)
    {
        // Declare a variable that is not private to the scope
        int sum = 0;

        // Expose the variable to the compute construct
        #pragma acc loop reduction(+:sum)
        for (int i = 0; i < 10; i++) {
            sum += i;
        }
    }

    // Check that the variable is treated as if it appears in a copy clause
    if (sum != 45) {
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