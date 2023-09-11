#include "acc_testsuite.h"

#ifndef T1
//T1:parallel construct private clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    int num_gangs = 10;
    int num_workers = 10;
    int num_private_vars = 10;

    // Create a parallel region with num_gangs gangs and num_workers workers
    #pragma acc parallel num_gangs(num_gangs) num_workers(num_workers)
    {
        // Declare a private variable for each gang
        int private_var[num_private_vars];

        // Initialize the private variables
        for (int i = 0; i < num_private_vars; i++) {
            private_var[i] = i;
        }

        // Perform some computation on the private variables
        for (int i = 0; i < num_private_vars; i++) {
            private_var[i] = private_var[i] + 1;
        }
    }

    // Check that the private variables were properly initialized and computed
    for (int i = 0; i < num_private_vars; i++) {
        if (private_var[i] != i + 1) {
            err = 1;
            break;
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