#include "acc_testsuite.h"

#ifndef T1
//T1:data construct detach clause,V:2.7-3.3
int test1(){
    int err = 0;

    // create a shared memory region
    int *shared_mem = (int *)acc_malloc(sizeof(int));

    // create a pointer to a variable in shared memory
    int *ptr = (int *)acc_attach(shared_mem, sizeof(int));

    // detach the pointer from shared memory
    acc_detach(ptr);

    // check that the pointer is no longer attached to shared memory
    if (acc_is_attached(ptr)) {
        err = 1;
    }

    // free the shared memory region
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