#include "acc_testsuite.h"
#ifndef T1
//T1:serial construct wait clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    int * a = (int *)malloc(n * sizeof(int));
    int * b = (int *)malloc(n * sizeof(int));

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = 0;
    }

    #pragma acc data copyin(a[0:n]) copyout(b[0:n])
    {
        #pragma acc serial loop
        for (int x = 0; x < n; ++x){
            b[x] = a[x];
        }
        #pragma acc serial loop vector(4) wait(0)
        for (int x = 1; x < n; ++x){
            b[x] = b[x] + b[x-1];
        }
    }

    for (int x = 0; x < n; ++x){
        if (b[x] > (x + 1) * 10){
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