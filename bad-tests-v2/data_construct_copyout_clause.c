#include "acc_testsuite.h"
#ifndef T1
//T1:data construct copyout clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    // Create and initialize input and output arrays
    int size = 10;
    int *in = (int*)malloc(size * sizeof(int));
    int *out = (int*)malloc(size * sizeof(int));
    for (int i = 0; i < size; ++i) {
        in[i] = rand() % 100;
        out[i] = 0;
    }

    // Copy input array to device
    #pragma acc data copyin(in[:size])

    // Perform computation on device
    #pragma acc parallel loop
    for (int i = 0; i < size; ++i) {
        out[i] = in[i] * 2;
    }

    // Copy output array back to host
    #pragma acc update host(out[:size])

    // Verify the result
    for (int i = 0; i < size; ++i) {
        if (out[i] != in[i] * 2) {
            err = 1;
            break;
        }
    }

    // Clean up
    free(in);
    free(out);

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