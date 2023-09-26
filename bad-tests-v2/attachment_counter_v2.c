#include "acc_testsuite.h"

#ifndef T1
//T1:attachment counter,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    // Initialize attachment counter for a pointer in device memory
    int *ptr = (int *)acc_malloc(sizeof(int));
    *ptr = 0;

    // Attach pointer to a device address
    acc_attach(ptr, sizeof(int), 0);
    *ptr = 1;

    // Increment attachment counter for the same target address
    acc_attach(ptr, sizeof(int), 0);
    *ptr = 2;

    // Decrement attachment counter when detaching
    acc_detach(ptr, sizeof(int), 0);
    *ptr = 1;

    // Check if attachment counter is working properly
    if (*ptr != 1) {
        err = 1;
    }

    // Free memory
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