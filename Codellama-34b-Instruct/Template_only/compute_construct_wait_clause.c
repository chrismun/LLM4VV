#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Create a device array
    int *a = (int *)acc_malloc(sizeof(int) * N);

    // Initialize the device array with random values
    for (int i = 0; i < N; i++) {
        a[i] = rand();
    }

    // Create a host array
    int *b = (int *)malloc(sizeof(int) * N);

    // Initialize the host array with random values
    for (int i = 0; i < N; i++) {
        b[i] = rand();
    }

    // Create an OpenACC compute construct with the wait clause
    #pragma acc parallel loop copy(a[0:N]) wait(b[0:N])
    for (int i = 0; i < N; i++) {
        a[i] += b[i];
    }

    // Check that the device array has been updated
    for (int i = 0; i < N; i++) {
        if (a[i] != b[i]) {
            err = 1;
            break;
        }
    }

    // Free the device and host arrays
    acc_free(a);
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