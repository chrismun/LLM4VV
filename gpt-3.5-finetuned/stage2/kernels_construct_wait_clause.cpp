#include "acc_testsuite.h"
#ifndef T1
//T1:kernels,V:2.7-3.3
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
    #pragma acc enter data copyin(a[0:n], b[0:n])
    #pragma acc kernels loop independent async(1) wait(2)
    for (int x = 0; x < n; ++x){
        c[x] = a[x] + b[x];
    }
    #pragma acc kernels loop independent async(2) wait(1)
    for (int x = 0; x < n; ++x){
        c[x] = c[x] + a[x];
    }
    #pragma acc exit data delete(a[0:n], b[0:n])
    for (int x = 0; x < n; ++x){
        if (fabs(c[x] - (real_t)(2 * a[x])) > PRECISION){
            err = 1;
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