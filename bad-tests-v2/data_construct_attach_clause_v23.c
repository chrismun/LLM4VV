#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Create a pointer to a variable in shared memory
    int *ptr = (int *)malloc(sizeof(int));
    *ptr = 1234;

    // Create a pointer to a variable in private memory
    int *ptr2 = (int *)malloc(sizeof(int));
    *ptr2 = 5678;

    // Attach the private variable to the shared variable
    acc_attach(ptr, ptr2);

    // Check that the private variable is now in shared memory
    if (*ptr != *ptr2) {
        err = 1;
    }

    // Detach the private variable from the shared variable
    acc_detach(ptr, ptr2);

    // Check that the private variable is no longer in shared memory
    if (*ptr == *ptr2) {
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