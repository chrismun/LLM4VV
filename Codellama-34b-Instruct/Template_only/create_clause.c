#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Create a new array on the device
    int *a = (int *)acc_malloc(10 * sizeof(int));
    if (a == NULL) {
        err = 1;
    }

    // Initialize the array on the device
    for (int i = 0; i < 10; i++) {
        a[i] = i;
    }

    // Copy the array back to the host
    int *b = (int *)acc_malloc(10 * sizeof(int));
    if (b == NULL) {
        err = 1;
    }
    acc_memcpy(b, a, 10 * sizeof(int));

    // Check that the array was copied correctly
    for (int i = 0; i < 10; i++) {
        if (b[i] != i) {
            err = 1;
        }
    }

    // Free the memory on the device
    acc_free(a);
    acc_free(b);

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