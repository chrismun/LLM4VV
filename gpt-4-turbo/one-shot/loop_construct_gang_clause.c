#include "acc_testsuite.h"
#ifndef T1
//T1:parallel,loop,gang,V:1.0-2.7
int test1(){
    int err = 0;
    const int n = 10000;  // Example array size
    real_t *a = (real_t *)malloc(n * sizeof(real_t));
    real_t *b = (real_t *)malloc(n * sizeof(real_t));

    // Initialize data
    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = 0;
    }

    #pragma acc data copyin(a[0:n]) copyout(b[0:n])
    {
        #pragma acc parallel
        {
            #pragma acc loop gang
            for (int x = 0; x < n; ++x){
                b[x] = a[x] * 2;  // Example operation to verify correct gang execution
            }
        }
    }

    // Verification
    for (int x = 0; x < n; ++x){
        if (fabs(b[x] - (a[x] * 2)) > PRECISION){  // Use appropriate precision for real_t
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
    int failed = 0;
#ifndef T1
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed += test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}