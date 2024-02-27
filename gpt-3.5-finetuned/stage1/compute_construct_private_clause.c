#include "acc_testsuite.h"
#ifndef T1
//T1:compute construct private clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    real_t* restrict a = (real_t *)malloc(n * sizeof(real_t));
    real_t* restrict b = (real_t *)malloc(n * sizeof(real_t));
    real_t* restrict c = (real_t *)malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = rand() / (real_t)(RAND_MAX / 10);
        c[x] = 0.0;
    }

    #pragma acc data copyin(a[0:n], b[0:n]) copyout(c[0:n])
    {
        #pragma acc compute
        {
            #pragma acc loop
            for (int x = 0; x < 128; ++x){
                real_t a_private[64];
                real_t b_private[64];
                for (int y = 0; y < 64; ++y){
                    a_private[y] = a[(x * 64) + y];
                    b_private[y] = b[(x * 64) + y];
                }
                #pragma acc loop
                for (int y = 0; y < 64; ++y){
                    c[(x * 64) + y] = a_private[y] + b_private[y];
                }
            }
        }
    }

    for (int x = 0; x < n; ++x){
        if (fabs(c[x] - (a[x] + b[x])) > (2 * PRECISION)){
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