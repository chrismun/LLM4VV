#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Create a new array on the device
    int *a = (int *)acc_malloc(sizeof(int) * N);

    // Initialize the array on the device
    for (int i = 0; i < N; i++) {
        a[i] = i;
    }

    // Create a new array on the host
    int *b = (int *)malloc(sizeof(int) * N);

    // Copy the array from the device to the host
    acc_memcpy(b, a, sizeof(int) * N);

    // Free the device array
    acc_free(a);

    // Check that the arrays are equal
    for (int i = 0; i < N; i++) {
        if (b[i] != a[i]) {
            err = 1;
            break;
        }
    }

    // Free the host array
    free(b);

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