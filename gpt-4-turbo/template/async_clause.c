#include "acc_testsuite.h"
#ifndef T1
//T1:async,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    const int size = 1024;
    int a[size], b[size], c[size], result[size];
    int async_test_value = 213; // A random value for validation.

    // Initialize the arrays
    for (int i = 0; i < size; ++i){
        a[i] = rand() % 100;
        b[i] = rand() % 100;
        c[i] = 0;
    }

    // Parallel region for vector addition using async queue 1
#pragma acc parallel loop async(1) copyin(a[0:size],b[0:size]) copyout(c[0:size])
    for(int i = 0; i < size; ++i){
        c[i] = a[i] + b[i];
    }

    // Parallel region for modifying the result using async queue 2
#pragma acc parallel loop async(2) copy(c[0:size]) copyout(result[0:size])
    for(int i = 0; i < size; ++i){
        result[i] = c[i] + async_test_value;
    }

    // Wait for all asynchronous operations to complete
#pragma acc wait

    // Check results
    for (int i = 0; i < size; ++i){
        if (result[i] != a[i] + b[i] + async_test_value){
            err += 1;
        }
    }

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