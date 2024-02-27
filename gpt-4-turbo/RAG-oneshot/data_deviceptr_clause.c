#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "acc_testsuite.h"

#ifndef T1
// T1:kernels,data,data-region,V:1.0-2.7
int test_deviceptr(){
    int err = 0;
    srand(SEED);
    real_t *a_host = (real_t *)malloc(n * sizeof(real_t));
    real_t *b_host = (real_t *)malloc(n * sizeof(real_t));
    real_t *a_device, *b_device;

    // Initialize host data
    for (int x = 0; x < n; ++x){
        a_host[x] = rand() / (real_t)(RAND_MAX / 10);
        b_host[x] = 0;
    }

    // Allocate memory on the device
    a_device = (real_t *)acc_malloc(n * sizeof(real_t));
    b_device = (real_t *)acc_malloc(n * sizeof(real_t));

    // Copy data to the device
    acc_memcpy_to_device(a_device, a_host, n * sizeof(real_t));

    #pragma acc data present(a_device[0:n]), deviceptr(b_device)
    {
        #pragma acc parallel loop
        for (int x = 0; x < n; ++x){
            b_device[x] = a_device[x] + 1; // Simple operation to differentiate
        }
    }

    // Copy result back to host
    acc_memcpy_from_device(b_host, b_device, n * sizeof(real_t));

    // Verify the result
    for (int x = 0; x < n; ++x){
        if (fabs(b_host[x] - (a_host[x] + 1)) > PRECISION){
            err += 1;
        }
    }

    // Cleanup
    acc_free(a_device);
    acc_free(b_device);
    free(a_host);
    free(b_host);

    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed;
#ifndef T1
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test_deviceptr();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}