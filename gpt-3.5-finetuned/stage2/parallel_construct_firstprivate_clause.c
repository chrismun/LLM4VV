#include "acc_testsuite.h"
#ifndef T1
//T1:parallel,firstprivate,V:2.7-3.3
int test1(){
    int err = 0;
    int firstprivate_raised_error = 0;

    srand(SEED);
    real_t * restriction a = (real_t *)malloc(n * sizeof(real_t));
    real_t * restriction b = (real_t *)malloc(n * sizeof(real_t));
    real_t device_firstpriv;

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = 0.0;
    }

    device_firstpriv = rand() / (real_t)(RAND_MAX / 10.0);

    #pragma acc data copyin(a[0:n]) copyout(b[0:n])
    {
        #pragma acc parallel firstprivate(device_firstpriv)
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x) {
                b[x] = a[x] + device_firstpriv;
            }
        }
    }

    for (int x = 0; x < n; ++x){
        if (fabs(b[x] - (a[x] + device_firstpriv)) > PRECISION){
            err += 1;
        }
    }
    if (err || firstprivate_raised_error){
        err = 1;
    }
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