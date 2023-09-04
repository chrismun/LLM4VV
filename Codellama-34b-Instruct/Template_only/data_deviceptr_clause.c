#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    int *a = (int *)acc_malloc(sizeof(int) * 10);
    int *b = (int *)acc_malloc(sizeof(int) * 10);

    // Initialize the data on the host
    for (int i = 0; i < 10; i++) {
        a[i] = i;
        b[i] = i;
    }

    // Copy the data to the device
    acc_memcpy_to_device(a, b, sizeof(int) * 10);

    // Use the data on the device
    for (int i = 0; i < 10; i++) {
        a[i] += b[i];
    }

    // Copy the data back to the host
    acc_memcpy_from_device(a, b, sizeof(int) * 10);

    // Verify the results
    for (int i = 0; i < 10; i++) {
        if (a[i] != 2 * i) {
            err = 1;
            break;
        }
    }

    // Free the device memory
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