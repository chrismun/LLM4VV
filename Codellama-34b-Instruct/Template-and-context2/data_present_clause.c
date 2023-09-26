#include "acc_testsuite.h"

#ifndef T1
//T1:data present clause,V:2.7-3.3
int test1(){
    int err = 0;

    // create a pointer to a shared memory region
    int *ptr = (int *)acc_malloc(sizeof(int));

    // create a data present clause for the pointer
    acc_data_present(ptr, sizeof(int));

    // perform an attach action on the pointer
    acc_attach(ptr, sizeof(int));

    // increment the structured reference counter for the pointer
    acc_present_increment(ptr, sizeof(int));

    // perform a detach action on the pointer
    acc_detach(ptr, sizeof(int));

    // decrement the structured reference counter for the pointer
    acc_present_decrement(ptr, sizeof(int));

    // check if the structured reference counter is zero
    if (acc_present_get_count(ptr, sizeof(int)) == 0) {
        // perform a delete action on the pointer
        acc_delete(ptr, sizeof(int));
    }

    // free the shared memory region
    acc_free(ptr);

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