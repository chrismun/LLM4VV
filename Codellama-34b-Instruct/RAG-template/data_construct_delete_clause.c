#include "acc_testsuite.h"

#ifndef T1
//T1:data construct delete clause,V:2.7-3.3
int test1(){
    int err = 0;

    // create a shared memory region
    int *shared_mem = (int *)acc_malloc(sizeof(int));

    // create a pointer to a non-shared memory region
    int *non_shared_mem = (int *)malloc(sizeof(int));

    // set the value of the shared memory region to 1
    *shared_mem = 1;

    // set the value of the non-shared memory region to 2
    *non_shared_mem = 2;

    // attach the non-shared memory region to the shared memory region
    acc_attach(non_shared_mem, shared_mem, sizeof(int));

    // detach the non-shared memory region from the shared memory region
    acc_detach(non_shared_mem, shared_mem, sizeof(int));

    // delete the non-shared memory region
    acc_delete(non_shared_mem);

    // check that the shared memory region has not been modified
    if (*shared_mem != 1) {
        err = 1;
    }

    // check that the non-shared memory region has been deleted
    if (non_shared_mem != NULL) {
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