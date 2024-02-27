#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <openacc.h>
#include "acc_testsuite.h"

#ifndef T2
// T2:kernels,data,data-region,hostptr,V:1.0-2.7
int test2(){
    int err = 0;
    srand(SEED);
    real_t *a = (real_t *)malloc(n * sizeof(real_t));
    real_t *b_dev_ptr, *b_host_ptr;
    real_t *b = (real_t *)malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = 0; // Initialize b array on host before usage
    }

    #pragma acc enter data copyin(a[0:n])
    #pragma acc enter data create(b[0:n])

    // Obtain device pointer for b
    b_dev_ptr = acc_deviceptr(b);

    #pragma acc parallel present(a[0:n],b[0:n])
    {
        #pragma acc loop
        for (int x = 0; x < n; ++x){
            b[x] = a[x] + 1; // Some operation on a
        }
    }

    // Validate using acc hostptr to access device data on the host
    b_host_ptr = (real_t *)acc_hostptr(b_dev_ptr);
    for (int x = 0; x < n; ++x){
        if (fabs(b_host_ptr[x] - (a[x] + 1)) > PRECISION){
            err += 1;
        }
    }

    #pragma acc exit data delete(a[0:n], b[0:n])

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
        failcode = failcode + (1 << 1); // Mark test2 failed
    }
#endif
    return failcode;
}