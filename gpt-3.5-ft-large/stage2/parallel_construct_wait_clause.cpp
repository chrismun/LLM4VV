#include "acc_testsuite.h"
#ifndef T1
//T1:parallel construct wait clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    acc_init(acc_device_nvidia);

    real_t *host_ptr = new real_t[n];
    real_t *a = new real_t[n];
    real_t *b = new real_t[n];

    for (int x = 0; x < n; ++x){
        a[x] = 0;
        b[x] = 1;
    }

    #pragma acc data copy(a[0:n]) create(host_ptr[0:n])
    {
            #pragma acc parallel
            {
                #pragma acc loop
                for (int x = 0; x < n; ++x){
                    a[x] = b[x] * b[x];
                }
                #pragma acc loop wait
                for (int x = 0; x < n; ++x){
                    host_ptr[x] = a[x];
                }
            }
    }

    for (int x = 0; x < n; ++x){
        if (fabs(host_ptr[x] - (b[x] * b[x] + PRECISION)) > 0){
            err += 1;
        }
    }

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