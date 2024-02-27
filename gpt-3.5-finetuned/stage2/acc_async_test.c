#include "acc_testsuite.h"
#ifndef T1
//T1:acc async test,V:2.7-3.3
int test1(){
    int err = 0;
    real_t **a = (real_t **)malloc(n * sizeof(real_t *));
    real_t **b = (real_t **)malloc(n * sizeof(real_t *));
    real_t **c = (real_t **)malloc(n * sizeof(real_t *));

    for (int x = 0; x < n; ++x){
        a[x] = a;
        b[x] = a;
        c[x] = a;
    }

    for(int x = 0; x < n; ++x){
        for (int y = 0; y < n; ++y){
            a[x][y] = 3;
            b[x][y] = 2;
            c[x][y] = 0;
        }
    }

    for (int x = 0; x < n; ++x){
        #pragma acc enter data copyin(a[x:1][0:n]) async(x)
    }

    for(int x = 0; x < n; ++x){
        #pragma acc kernels loop independent async(x)
        for (int y = 0; y < n; ++y){
            c[x][y] = a[x][y] + b[x][y];
        }
    }

    for (int x = 0; x < n; ++x){
        #pragma acc exit data copyout(a[x:1][0:n]) async(x)
    }

    for (int x = 0; x < n; ++x){
        while (acc_async_test(x) == 0);
        for(int y = 0; y < n; ++y){
            if (fabs(a[x][y] - 5) > 0){
                err = 1;
            }
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