#include "acc_testsuite.h"

#ifndef T1
//T1:data construct no_create clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    // Create a shared memory region
    int *shared_mem = (int *)acc_malloc(sizeof(int));

    // Create a pointer to the shared memory region
    int *ptr = shared_mem;

    // Set the value of the shared memory region to 0
    *shared_mem = 0;

    // Create a compute construct with the no_create clause
    #pragma acc parallel num_gangs(1) num_workers(1) no_create(ptr)
    {
        // Increment the value of the shared memory region
        *shared_mem += 1;
    }

    // Check that the value of the shared memory region has been incremented
    if (*shared_mem != 1) {
        err = 1;
    }

    // Free the shared memory region
    acc_free(shared_mem);

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