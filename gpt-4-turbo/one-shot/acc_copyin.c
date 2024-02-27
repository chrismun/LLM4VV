#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "acc_testsuite.h" // Assuming this header file contains relevant declarations like NUM_TEST_CALLS, SEED, real_t, PRECISION, and n.

#ifndef T2
//T2:kernels,data,data-region,copyin,V:1.0-2.7
int test2(){
    int err = 0;
    srand(SEED);
    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * result_on_host = (real_t *)malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        result_on_host[x] = a[x] + 1; // Expected result after computation on the device
    }

    #pragma acc data copyin(a[0:n])
    {
        #pragma acc kernels
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                a[x] = a[x] + 1; // Simple computation to verify copyin
            }
        }
    }

    // Verifying that the computation was done correctly
    for (int x = 0; x < n; ++x){
        if (fabs(result_on_host[x] - a[x]) > PRECISION){
            err += 1;
        }
    }

    free(a);
    free(result_on_host);
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
        failcode = failcode + (1 << 1);
    }
#endif

    return failcode;
}