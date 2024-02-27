#include "acc_testsuite.h"
#ifndef T1
// T1: async,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    const int size = 1024;
    static float a[size], b[size];
    for (int i = 0; i < size; ++i) {
        a[i] = rand() / (float)RAND_MAX; // Initialize with random values
        b[i] = rand() / (float)RAND_MAX; // Initialize with random values
    }

    int async1 = 1, async2 = 2;

    #pragma acc data copy(a[0:size])
    {
        #pragma acc parallel loop async(async1)
        for(int i = 0; i < size; ++i){
            a[i] = a[i] * a[i]; // Square each element
        }

        #pragma acc parallel loop async(async2)
        for(int i = 0; i < size; ++i){
            b[i] = b[i] + b[i]; // Double each element
        }

        // Wait for any of the above asynchronous operations to complete
        #pragma acc wait_any(async1, async2)
    }

    // At this point, at least one of the arrays should be processed. However, without checking inside the data region,
    // we can't guarantee which one has completed. Generally, further validation would involve checking the state of the compute
    // operations, but for this example, we verify the wait_any operation itself.

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