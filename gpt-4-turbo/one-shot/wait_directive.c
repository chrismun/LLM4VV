#include "acc_testsuite.h"
#ifndef T2
//T2:wait,V:1.0-2.7
int test2(){
    int err = 0;
    srand(SEED);
    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * b = (real_t *)malloc(n * sizeof(real_t));

    // Initialize array 'a' with random values and 'b' with zeros.
    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = 0;
    }

    // Create a data region for 'a' and 'b'
    #pragma acc data copyin(a[0:n]) copyout(b[0:n])
    {
        // Implement a asynchronous compute construct with an 'async' clause
        #pragma acc kernels async(1)
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                b[x] = a[x];
            }
        }
        
        // Use the 'wait' directive to ensure compute construct completion.
        #pragma acc wait(1)
    }

    // Verify the data
    for (int x = 0; x < n; ++x){
        if (fabs(b[x] - a[x]) > PRECISION){
            err += 1;
        }
    }

    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed;

#ifndef T2
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test2();
    }
    if (failed != 0){
        failcode = failcode + (1 << 1); // Index for test2 failure.
    }
#endif

    return failcode;
}