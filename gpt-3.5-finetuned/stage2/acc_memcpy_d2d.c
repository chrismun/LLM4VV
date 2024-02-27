#include "acc_testsuite.h"
#ifndef T1
//T1:acc memcpy d2d,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    real_t *a = (real_t *)malloc(n * sizeof(real_t));
    real_t *b = (real_t *)malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(n * 10);
    }

    acc_create(b, n * sizeof(real_t));
    acc_copyin(a, n * sizeof(real_t));
    acc_memcpy_d2d(b, a, n * sizeof(real_t), 1, 0);

    #pragma acc data pcopyout(b[0:n]) present(a[0:n])
    {
        #pragma acc parallel
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                b[x] += a[x];
            }
        }
    }

    acc_memcpy_d2d(a, b, n * sizeof(real_t), 0, 1);
    for (int x = 0; x < n; ++x){
        if (fabs(a[x] - b[x]) > PRECISION){
            err += 1;
        }
    }

    acc_delete(b, n * sizeof(real_t));

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