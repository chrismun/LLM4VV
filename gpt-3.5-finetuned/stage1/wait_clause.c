#include "acc_testsuite.h"
#ifndef T1
//T1:wait clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    real_t *a = (real_t *)malloc(n * sizeof(real_t));
    real_t *b = (real_t *)malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = 0.0;
    }

    #pragma acc data copyin(a[0:n]) copyout(b[0:n]) present(a[0:n]) wait(2)
    {
        #pragma acc parallel loop async
        for (int x = 0; x < n; ++x){
            a[x] = a[x] * a[x];
        }
        #pragma acc parallel loop async(2)
        for (int x = 0; x < n; ++x){
            b[x] = a[x] / 2;
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