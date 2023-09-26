#include "acc_testsuite.h"
#ifndef T2
//T2:kernels,data,data-region,loop-collapse,V:2.0-2.7
int test2(){
    int err = 0;
    srand(SEED);
    real_t * a = (real_t *)malloc(n * m * sizeof(real_t));
    real_t * b = (real_t *)malloc(n * m * sizeof(real_t));

    for (int x = 0; x < n * m; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = 0;
    }

    #pragma acc data copyin(a[0:n*m])
    {
        #pragma acc kernels loop collapse(2) copyout(b[0:n*m])
        for (int x = 0; x < n; ++x){
            for (int y = 0; y < m; ++y){
                b[x * m + y] = a[x * m + y];
            }
        }
    }

    for (int x = 0; x < n * m; ++x){
        if (fabs(b[x] - a[x]) > PRECISION){
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