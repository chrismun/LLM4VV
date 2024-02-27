#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "acc_testsuite.h"

#ifndef T2
// T2:data,data-region,unmap,V:1.0-2.7
int test2(){
    int n = 1024;
    int err = 0;
    real_t *a = (real_t *)malloc(n * sizeof(real_t));
    real_t *b = (real_t *)malloc(n * sizeof(real_t));
    real_t *a_device_copy = NULL;

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = 0; // Initialize b to zeros
    }

    #pragma acc data copyin(a[0:n]) create(b[0:n])
    {
        #pragma acc parallel loop
        for (int x = 0; x < n; ++x){
            b[x] = a[x];
        }

        // Use unmap to keep a_device_copy for further use
        #pragma acc exit data copyout(a_device_copy[0:n]) unmap(a)
    }

    // Intentionally not using OpenACC for this part to simulate operations in between
    // Here, you might manipulate b or perform other operations

    // Map back to the data for further operations, intending to use the previously unmapped copy
    #pragma acc data copyin(a_device_copy[0:n]) copyout(b[0:n])
    {
        #pragma acc parallel loop
        for (int x = 0; x < n; ++x){
            b[x] = a_device_copy[x] * 2; // Example operation
        }
    }

    for (int x = 0; x < n; ++x){
        if (fabs(b[x] - (a[x] * 2)) > PRECISION){
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
#ifndef T2
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test2();
    }
    if (failed != 0){
        failcode = failcode + (1 << 1); // Adjust the bit position for each test
    }
#endif
    return failcode;
}