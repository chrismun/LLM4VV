#include "acc_testsuite.h"
#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Allocate memory for the source and destination arrays
    int *src = (int *)malloc(sizeof(int) * N);
    int *dst = (int *)malloc(sizeof(int) * N);

    // Initialize the source and destination arrays
    for (int i = 0; i < N; i++) {
        src[i] = i;
        dst[i] = 0;
    }

    // Copy the source array to the destination array using the acc_memcpy device
    #pragma acc parallel loop device_type(acc_memcpy)
    for (int i = 0; i < N; i++) {
        dst[i] = src[i];
    }

    // Check if the destination array is equal to the source array
    for (int i = 0; i < N; i++) {
        if (dst[i] != src[i]) {
            err = 1;
            break;
        }
    }

    // Free the memory for the source and destination arrays
    free(src);
    free(dst);

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