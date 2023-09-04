#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Create a vector of random numbers
    int *vec = (int *)malloc(sizeof(int) * 10);
    for (int i = 0; i < 10; i++) {
        vec[i] = rand() % 100;
    }

    // Create a device vector
    int *dev_vec = (int *)acc_malloc(sizeof(int) * 10);
    acc_memcpy(dev_vec, vec, sizeof(int) * 10);

    // Create a host vector
    int *host_vec = (int *)malloc(sizeof(int) * 10);
    acc_memcpy(host_vec, dev_vec, sizeof(int) * 10);

    // Verify that the host and device vectors are equal
    for (int i = 0; i < 10; i++) {
        if (host_vec[i] != dev_vec[i]) {
            err = 1;
            break;
        }
    }

    // Free the device and host vectors
    acc_free(dev_vec);
    free(host_vec);

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