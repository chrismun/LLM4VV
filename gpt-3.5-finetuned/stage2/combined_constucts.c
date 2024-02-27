#include "acc_testsuite.h"
#ifndef T1
//T1:combined constucts,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    real_t *a = (real_t *)malloc(n * 10 * sizeof(real_t));
    real_t *b = (real_t *)malloc(n * 10 * sizeof(real_t));
    real_t *c = (real_t *)malloc(n * 10 * sizeof(real_t));

    for (int x = 0; x < 10 * n; ++x){
        a[x] = 0;
    }

    for (int x = 0; x < 10 * n; ++x){
        b[x] = rand() / (real_t)(RAND_MAX / 10);
    }

    #pragma acc parallel loop copy(a[0:10*n]), serial loop copyin(b[0:10*n]), kernels loop copyout(c[0:10*n])
    for (int x = 0; x < 10; ++x){
        for (int y = 0; y < n; ++y){
            a[x * n + y] = b[x * n + y];
            c[x * n + y] = a[x * n + y];
        }
    }

    for (int x = 0; x < 10 * n; ++x){
        if (fabs(c[x] - b[x]) > PRECISION){
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