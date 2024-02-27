#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "acc_testsuite.h"

#ifndef TEST_HOST_DATA_IF
// TEST_HOST_DATA_IF: host_data, data, data-region, if clause, V:1.0-2.7

int test_host_data_if(){
    int err = 0;
    const int n = 1000;
    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * b = (real_t *)malloc(n * sizeof(real_t));
    real_t * c = (real_t *)malloc(n * sizeof(real_t)); // Host copy

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = 0;
    }

    // Condition true for the if clause
    #pragma acc data copyin(a[0:n]) copyout(b[0:n])
    {
        #pragma acc host_data use_device(a) if(1)
        {
            // Expected to utilize device pointers
            for (int x = 0; x < n; ++x){
                b[x] = a[x] + 1;
            }
        }
    }

    // Condition false for the if clause
    #pragma acc data copyin(a[0:n]) copyout(c[0:n])
    {
        #pragma acc host_data use_device(a) if(0)
        {
            // Fallback to host pointers, b will not be updated with device data
            for (int x = 0; x < n; ++x){
                c[x] = a[x] + 1;
            }
        }
    }

    for (int x = 0; x < n; ++x){
        // b is expected to be updated with device data, so should be different than c
        if (fabs(b[x] - c[x]) > PRECISION){
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

#ifndef TEST_HOST_DATA_IF
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed += test_host_data_if();
    }
    if (failed != 0){
        printf("TEST FAIL: test_host_data_if failed %d times.\n", failed);
        failcode += (1 << 0);
    } else {
        printf("TEST PASS: test_host_data_if passed.\n");
    }
#endif

    return failcode;
}