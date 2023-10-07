#include "acc_testsuite.h"

#ifndef T1
//T1:data construct copyin clause,V:2.7-3.3
int test1(){
    int err = 0;

    // create a shared memory region
    int *shared_mem = (int *)acc_malloc(sizeof(int));

    // create a copy of the shared memory region
    int *copy_mem = (int *)acc_malloc(sizeof(int));

    // initialize the shared memory region
    *shared_mem = 1;

    // create a compute construct with a copyin clause
    #pragma acc parallel copyin(shared_mem)
    {
        // increment the shared memory region
        *shared_mem += 1;
    }

    // check that the shared memory region has been incremented
    if (*shared_mem != 2) {
        err = 1;
    }

    // free the memory
    acc_free(shared_mem);
    acc_free(copy_mem);

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