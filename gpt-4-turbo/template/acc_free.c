#include "acc_testsuite.h"
#ifndef T1
//T1:runtime,V:2.7-3.3
int test1(){
    int err = 0;
    int *a;
    size_t n = 1024; // Size of the array
    srand(SEED);

    a = (int *)malloc(n * sizeof(int));
    // Initialize array
    for (size_t i = 0; i < n; ++i) {
        a[i] = rand() % 100;
    }
    // Allocate and transfer data to GPU
    #pragma acc enter data copyin(a[0:n])
    // Freeing memory on the device
    #pragma acc exit data delete(a[0:n])
    // Trying to use the freed memory to trigger an error
    int error_detected = 0;
    #pragma acc parallel loop present(a[0:n]) reduction(+:error_detected)
    for (size_t i = 0; i < n; ++i) {
        if (a[i] != 0) { // Ideally, we should not reach here as a[] is not present
            error_detected += 1;
        }
    }
    if (error_detected > 0) {
        err = 1; // If we've reached here, there's an error with acc free implementation
    }

    free(a);
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