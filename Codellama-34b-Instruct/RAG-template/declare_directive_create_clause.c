#include "acc_testsuite.h"

#ifndef T1
//T1:declare directive create clause,V:2.7-3.3
int test1(){
    int err = 0;
    int *ptr = NULL;

    // create a pointer to a variable in shared memory
    #pragma acc declare create(ptr)

    // check that the pointer is not null
    if (ptr == NULL) {
        err = 1;
    }

    // increment the structured reference counter for the pointer
    #pragma acc present(ptr)

    // check that the structured reference counter is now 1
    if (ptr->structured_reference_counter != 1) {
        err = 1;
    }

    // decrement the structured reference counter for the pointer
    #pragma acc present(ptr)

    // check that the structured reference counter is now 0
    if (ptr->structured_reference_counter != 0) {
        err = 1;
    }

    // delete the pointer
    #pragma acc delete(ptr)

    // check that the pointer is now null
    if (ptr != NULL) {
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