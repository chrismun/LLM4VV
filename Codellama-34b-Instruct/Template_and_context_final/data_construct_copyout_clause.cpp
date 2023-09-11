#include "acc_testsuite.h"

#ifndef T1
//T1:data construct copyout clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    // Create a shared memory region
    int *shared_mem = (int *)acc_malloc(sizeof(int));
    *shared_mem = 0;

    // Create a non-shared memory region
    int *non_shared_mem = (int *)malloc(sizeof(int));
    *non_shared_mem = 0;

    // Create a compute construct with a copyout clause
    #pragma acc parallel copyout(shared_mem)
    {
        // Increment the shared memory region
        *shared_mem += 1;
    }

    // Check that the shared memory region has been incremented
    if (*shared_mem != 1) {
        err = 1;
    }

    // Create a compute construct with a copyout clause and a zero modifier
    #pragma acc parallel copyout(non_shared_mem, zero)
    {
        // Increment the non-shared memory region
        *non_shared_mem += 1;
    }

    // Check that the non-shared memory region has been incremented
    if (*non_shared_mem != 1) {
        err = 1;
    }

    // Create an exit data directive with a copyout clause
    #pragma acc exit data copyout(shared_mem)

    // Check that the shared memory region has been copied out
    if (*shared_mem != 1) {
        err = 1;
    }

    // Create an exit data directive with a copyout clause and a finalize clause
    #pragma acc exit data copyout(non_shared_mem, finalize)

    // Check that the non-shared memory region has been copied out
    if (*non_shared_mem != 1) {
        err = 1;
    }

    // Free the memory regions
    acc_free(shared_mem);
    free(non_shared_mem);

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