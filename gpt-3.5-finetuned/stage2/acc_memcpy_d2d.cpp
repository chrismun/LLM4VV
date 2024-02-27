#include "acc_testsuite.h"
#ifndef T1
//T1:acc memcpy d2d,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    real_t *a = new real_t[n];
    real_t *b = new real_t[n];
    real_t *c = new real_t[n];

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = rand() / (real_t)(RAND_MAX / 10);
        c[x] = 0.0;
    }

    #pragma acc enter data create(a[0:n], b[0:n])
    #pragma acc data copyin(a[0:n], b[0:n]) deviceptr(a, b)
    {
        #pragma acc parallel
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                a[x] = a[x] * a[x];
            }
        }
        #pragma acc enter data create(a[0:n], b[0:n])
        #pragma acc data copyin(a[0:n], b[0:n]) deviceptr(a, b)
        {
            #pragma acc parallel
            {
                #pragma acc loop
                for (int x = 0; x < n; ++x){
                    b[x] = b[x] * b[x];
                }
            }
            #pragma acc exit data copyout(a[0:n], b[0:n])
            #pragma acc enter data copyin(a[0:n]) create(b[0:n]) deviceptr(a, b)
            #pragma acc parallel
            {
                #pragma acc loop
                for (int x = 0; x < n; ++x){
                    b[x] = b[x] * b[x];
                }
            }
            #pragma acc exit data copyout(b[0:n])
            #pragma acc exit data copyout(a[0:n], b[0:n]) delete(a[0:n], b[0:n])
        }
        #pragma acc exit data copyout(a[0:n]) delete(a[0:n], b[0:n])
    }
    #pragma acc exit data delete(a[0:n], b[0:n]) copyout(a[0:n], b[0:n])

    for (int x = 0; x < n; ++x){
        if (fabs(a[x] - c[x]) > PRECISION){
            err += 1;
            break;
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