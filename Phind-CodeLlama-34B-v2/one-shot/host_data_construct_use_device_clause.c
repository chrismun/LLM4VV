#include "acc_testsuite.h"
#ifndef T2
//T2:kernels,data,data-region,V:2.0-2.7
int test2(){
    int err = 0;
    srand(SEED);
    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * b = (real_t *)malloc(n * sizeof(real_t));
    real_t * c = (real_t *)malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = 0;
        c[x] = 0;
    }

    #pragma acc enter data copyin(a[0:n])
    #pragma acc enter data create(b[0:n])
    #pragma acc enter data create(c[0:n])

    #pragma acc host_data use_device(a, b, c)
    {
        #pragma acc kernels
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                b[x] = a[x] * 2;
            }
        }

        #pragma acc kernels
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                c[x] = b[x] * 2;
            }
        }
    }

    #pragma acc exit data copyout(b[0:n])
    #pragma acc exit data copyout(c[0:n])

    for (int x = 0; x < n; ++x){
        if (fabs(c[x] - (a[x] * 4)) > PRECISION){
            err += 1;
        }
    }

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