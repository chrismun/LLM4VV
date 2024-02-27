#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include "acc_testsuite.h"

#ifndef T1
// T1:kernels,async,V:1.0-2.7
int test_async(){
    int err = 0;
    srand(SEED);
    real_t *a = (real_t*)malloc(n * sizeof(real_t));
    real_t *b = (real_t*)malloc(n * sizeof(real_t));
    real_t *c = (real_t*)malloc(n * sizeof(real_t));
    
    // Initialize the arrays
    for(int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = rand() / (real_t)(RAND_MAX / 10);
        c[x] = 0; // This will hold the result of a simple operation on a and b
    }
    
    // We use two different async queues for operations
    int async1 = 1;
    int async2 = 2;
    
    #pragma acc data copyin(a[0:n], b[0:n]) copyout(c[0:n])
    {
        // Perform a simple operation on array a and b in an async way
        // Using async1
        #pragma acc kernels async(async1)
        {
            #pragma acc loop
            for(int x = 0; x < n; ++x){
                c[x] = a[x] + b[x];
            }
        }
        
        // Copy data b back to the host in parallel (asynchronously) without waiting for the above computation to finish
        // This utilizes the async2 queue
        #pragma acc update host(b[0:n]) async(async2)
    }
    
    // Wait for all async operations to complete
    #pragma acc wait(async1)
    #pragma acc wait(async2)
    
    // Test the correctness of the operation
    for(int x = 0; x < n; ++x){
        if(fabs((a[x] + b[x]) - c[x]) > PRECISION){
            err += 1;
        }
    }

    free(a);
    free(b);
    free(c);
    
    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed;
#ifndef T1
    failed = 0;
    for(int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test_async();
    }
    if(failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}