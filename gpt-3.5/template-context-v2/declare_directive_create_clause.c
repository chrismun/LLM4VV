#include "acc_testsuite.h"
#ifndef T1
//T1:declare directive create clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    // Create clause to allocate and initialize an array on the device
    acc_create((void *restrict *)&dev_ptr, sizeof(int) * ARRAY_SIZE);
    for (int i = 0; i < ARRAY_SIZE; i++) {
        dev_ptr[i] = rand() % 100;
    }

    // Perform operations on the device array
    #pragma acc kernels
    for (int i = 0; i < ARRAY_SIZE; i++) {
        dev_ptr[i] *= 2;
    }

    // Check if the operations were correctly performed on the device array
    for (int i = 0; i < ARRAY_SIZE; i++) {
        if (dev_ptr[i] != 2 * (rand() % 100)) {
            err = 1;
            break;
        }
    }

    // Free the device array
    acc_delete((void *restrict *)&dev_ptr, sizeof(int) * ARRAY_SIZE);

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