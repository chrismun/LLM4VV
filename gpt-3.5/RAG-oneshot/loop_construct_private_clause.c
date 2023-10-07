#include "acc_testsuite.h"
#ifndef T1
//T1:parallel,loop,V:1.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * b = (real_t *)malloc(n * sizeof(real_t));
    real_t * c = (real_t *)malloc(n * sizeof(real_t));
    real_t div = 2.0;

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = rand() / (real_t)(RAND_MAX / 10);
        c[x] = rand() / (real_t)(RAND_MAX / 10);
    }

    #pragma acc parallel loop private(div, b[0:n], c[0:n])
    for (int x = 0; x < n; ++x){
        real_t tmp = b[x] + c[x];
        a[x] = a[x] + tmp / div;
    }

    for (int x = 0; x < n; ++x){
        if (fabs(a[x] - (a[x] + (b[x] + c[x]) / div)) > PRECISION){
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