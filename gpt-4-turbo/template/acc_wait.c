#include "acc_testsuite.h"
#ifndef T1
//T1:runtime,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    
    const int array_size = 1024;
    float *a = (float *)malloc(array_size * sizeof(float));
    float *b = (float *)malloc(array_size * sizeof(float));
    
    // Initialize arrays
    for(int i = 0; i < array_size; ++i) {
        a[i] = (float)rand() / (float)(RAND_MAX);
        b[i] = 0.0f;
    }
    
    // Dispatch first operation to device asynchronously using async(1)
    #pragma acc kernels copyin(a[0:array_size]) copy(b[0:array_size]) async(1)
    for (int i = 0; i < array_size; ++i) {
        b[i] = a[i] * 2.0f;
    }
    
    // Dispatch second operation that depends on the first, modifying 'b', using a different async queue to ensure it waits for the first to finish
    #pragma acc kernels copy(b[0:array_size]) async(2)
    for (int i = 0; i < array_size; ++i) {
        b[i] = b[i] + 1.0f;
    }
    
    // Ensure that the first operation is completed before the second
    acc_wait(1);
    acc_wait(2);
    
    // Verify the results
    for(int i = 0; i < array_size; ++i) {
        if(b[i] != (a[i] * 2.0f) + 1.0f) {
            err += 1;
        }
    }

    free(a);
    free(b);
    
    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed;
#ifndef T1
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed = failed + test1();
    }
    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}