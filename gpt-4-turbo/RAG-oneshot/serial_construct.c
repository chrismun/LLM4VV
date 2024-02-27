#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "acc_testsuite.h"

#ifndef SERIAL_TEST
// SERIAL_TEST:serial,execution,V:1.0-2.7
int test_serial(){
    int err = 0;
    srand(SEED);
    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * result = (real_t *)malloc(n * sizeof(real_t));
    
    // Initialize the array with random values
    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        result[x] = 0.0;
    }
    
    // Perform the computation using the serial construct
    #pragma acc serial copyin(a[0:n]) copyout(result[0:n])
    {
        for (int x = 0; x < n; ++x){
            result[x] = sqrt(a[x]); // Example operation
        }
    }
    
    // Validate the results
    for (int x = 0; x < n; ++x){
        if (!isClose(result[x], sqrt(a[x]), PRECISION)){
            err += 1;
        }
    }

    free(a);
    free(result);
    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed = 0;
#ifndef SERIAL_TEST
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed += test_serial();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0); // Mark this test case as failed.
    }
#endif
    return failcode;
}

// Define the 'isClose' function for floating point comparison if it's not already defined.
#ifndef isClose
#define isClose(x,y,tolerance) (fabs((x) - (y)) <= (tolerance))
#endif