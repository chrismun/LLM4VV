#include "acc_testsuite.h"
#ifndef T1
/*T1:data construct no_create clause,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);

    real_t *a = (real_t *)malloc(n * sizeof(real_t));
    real_t *devPtrA = (real_t *)acc_malloc(n * sizeof(real_t));

    #pragma acc data copyout(a[0:n]) no_create(devPtrA[0:n])
    {
        #pragma acc kernels
        {
            for (int x = 0; x < n; ++x) {
                devPtrA[x] = x * 2.0;
            }
        }
    }

    if (acc_is_present(devPtrA, n * sizeof(real_t))){
        err = 1;
    }

    acc_free(devPtrA);
    free(a);

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