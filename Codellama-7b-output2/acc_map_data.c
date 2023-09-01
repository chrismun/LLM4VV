#include "acc_testsuite.h"
#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Create an array of integers on the host
    int *h_data = (int *)malloc(N * sizeof(int));
    for (int i = 0; i < N; i++) {
        h_data[i] = i;
    }

    // Create an array of integers on the device
    int *d_data = (int *)malloc(N * sizeof(int));

    // Map the host array to the device array
    #pragma acc map(h_data[0:N])
    {
        // Copy the host array to the device array
        #pragma acc update host(h_data[0:N])
        #pragma acc update device(d_data[0:N])
    }

    // Verify that the device array contains the same values as the host array
    for (int i = 0; i < N; i++) {
        if (d_data[i] != h_data[i]) {
            err = 1;
            break;
        }
    }

    // Free the host and device arrays
    free(h_data);
    free(d_data);

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