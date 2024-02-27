#include "acc_testsuite.h"
#ifndef T1
//T1:loop construct reduction clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    real_t  *a = (real_t *)malloc(n * sizeof(real_t));
    real_t reduction = 0.0;

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
    }

	 #pragma acc loop reduction(+:reduction)
     for (int x = 0; x < n; ++x){
        reduction = reduction + a[x];
    }
    for (int x = 0; x < n; ++x){
        host_redux = host_redux + a[x];
    }
    if (fabs(reduction - host_redux) > PRECISION){
        err += 1;
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