#include "acc_testsuite.h"
#ifndef T1
//T1:kernels,data,data-region,validate copyout mechanism,V:1.0-2.7
int test1(){
    int err = 0;
    srand(SEED);
    // Allocate dynamic memory
    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * b = (real_t *)malloc(n * sizeof(real_t));

    // Fill the array 'a' with random real numbers, initialise array 'b' to 0
    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = 0;
    }

    #pragma acc data copyin(a[0:n])
    {
        // Test copyout mechanism
        #pragma acc kernels copyout(b[0:n])
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                b[x] = a[x];
            }
        }
    }

    // Check correctness of results
    for (int x = 0; x < n; ++x){
        if (fabs(b[x] - a[x]) > PRECISION){
            err += 1;
        }
    }

    // Cleanup
    free(a);
    free(b);

    return err;
}

#endif

int main(){
    int failcode = 0;
    int failed;
#ifndef T1
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}