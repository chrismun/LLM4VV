#include "acc_testsuite.h"
#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Create a buffer to store the data
    int *data = (int *)malloc(sizeof(int) * N);

    // Initialize the data
    for (int i = 0; i < N; i++) {
        data[i] = i;
    }

    // Create a kernel to perform the computation
    void kernel(int *data) {
        #pragma acc parallel async(data)
        for (int i = 0; i < N; i++) {
            data[i] = data[i] * data[i];
        }
    }

    // Call the kernel
    kernel(data);

    // Check if the data has been modified correctly
    for (int i = 0; i < N; i++) {
        if (data[i] != i * i) {
            err = 1;
            break;
        }
    }

    // Free the buffer
    free(data);

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