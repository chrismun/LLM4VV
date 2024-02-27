#include <stdlib.h>
#include <math.h>
#include "acc_testsuite.h"

#ifndef T2
// T2:kernels,data,data-region,update,V:1.0-2.7
int test2(){
    int err = 0;
    srand(SEED);
    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * b = (real_t *)malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = 0;
    }

    // Copy data to device
    #pragma acc data copy(a[0:n])
    {
        // Perform computation on device
        #pragma acc kernels
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                a[x] = a[x] * 2.0;
            }
        }
        
        // Update computed data back to host
        #pragma acc update host(a[0:n])
    }

    // Verify the updated data
    for (int x = 0; x < n; ++x){
        if (fabs(a[x] - 2.0*b[x]) > PRECISION){
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
        failcode = failcode + (1 << 1);
    }
#endif
    return failcode;
}