#include "acc_testsuite.h"

#ifndef T1
//T1:kernels construct private clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    int num_gangs = 10;
    int num_workers = 10;
    int num_private = 10;

    // Create a kernel with the private clause
    #pragma acc kernels private(num_private)
    {
        // Initialize the private variable
        num_private = 0;

        // Loop over the gangs and workers
        #pragma acc loop gang, worker
        for (int i = 0; i < num_gangs; i++) {
            for (int j = 0; j < num_workers; j++) {
                // Increment the private variable
                num_private++;
            }
        }
    }

    // Check that the private variable has the correct value
    if (num_private != num_gangs * num_workers) {
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