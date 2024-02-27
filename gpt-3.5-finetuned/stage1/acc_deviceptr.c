#include "acc_testsuite.h"
#ifndef T1
//T1:acc deviceptr,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    int * dev_a = (int *)acc_malloc(n*sizeof(real_t))

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
    }
    acc_copyin(a, n * sizeof(real_t));
    dev_a = acc_deviceptr(a);
    #pragma acc parallel loop present(dev_a[0:n]) reduction(+:err)
    for (int x = 0; x < n; ++x){
        dev_a[x] = x;
    }


    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }

    return err;
}
#endif


int main(){
    int failed = 0;
    int failcode = 0;
    failed = failed + test1();
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
    return failcode;
}