#include "acc_testsuite.h"
#ifndef T1
//T1:wait directive,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    int * a = (int *)malloc(n * sizeof(int));
    real_t * b = (real_t *)malloc(n * sizeof(real_t));
    real_t * c = (real_t *)malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        a[x] = 0;
        b[x] = rand() / (real_t)(RAND_MAX / 10);
        c[x] = 0;
    }

    #pragma acc data copyin(b[0:n]) copy(a[0:n], c[0:n])
    {
        #pragma acc parallel loop async(1) present(a[0:n])
        for (int x = 0; x < n; ++x){
            a[x] = 2;
        }
        #pragma acc parallel loop async(2) present(c[0:n])
        for (int x = 0; x < n; ++x){
            c[x] = 2 * b[x];
        }
        #pragma acc wait(1, 2)
    }

    for (int x = 0; x < n; ++x){
        if (a[x] != 2 && c[x] != 2 * b[x]){
            err += 1;
        }
    }

    free(a);
    free(b);
    free(c);

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