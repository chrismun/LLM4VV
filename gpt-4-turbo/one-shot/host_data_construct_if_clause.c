#include <stdlib.h>
#include <stdio.h>
#include <math.h>
// Assume acc_testsuite.h defines necessary types, constants, and utility functions

#ifndef T2
//T2:host_data,V:1.0-2.7
int test2(){
    int err = 0;
    srand(SEED);
    real_t *a = (real_t *)malloc(n * sizeof(real_t));
    real_t *b = (real_t *)malloc(n * sizeof(real_t));
    real_t *dev_ptr;
    int use_device = 1; // This could be set based on a condition

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = 0;
    }

    #pragma acc enter data copyin(a[0:n])
    // Allocate device memory for dev_ptr
    #pragma acc enter data create(dev_ptr[0:n])

    // Conditional use of device memory based on 'use_device'
    #pragma acc host_data use_device(use_device) if(use_device)
    {
        dev_ptr = a; // This should work only if use_device is true
    }

    #pragma acc parallel loop present(dev_ptr[0:n])
    for (int x = 0; x < n; ++x){
        dev_ptr[x] = dev_ptr[x] + 1; // Incrementing each element to test
    }

    #pragma acc exit data copyout(b[0:n]) copy(dev_ptr[0:n])

    // Verify if the increment operation was successful
    for (int x = 0; x < n; ++x){
        if (fabs(b[x] - (a[x] + 1)) > PRECISION){
            err += 1;
        }
    }

    #pragma acc exit data delete(dev_ptr)
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
        failed += test2();
    }
    if (failed != 0){
        failcode += (1 << 1);
    }
#endif
    return failcode;
}