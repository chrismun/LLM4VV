#include "acc_testsuite.h"
#ifndef T1
//T1:declare directive create clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    real_t *a = (real_t *)malloc(n * sizeof(real_t));
    real_t *b = (real_t *)malloc(n * sizeof(real_t));
    real_t c = 0;

    for (int x = 0; x < n; ++x){
        a[x] = 1;
        b[x] = 2;
    }

    #pragma acc declare create(c)
    #pragma acc parallel loop present(a[0:n], b[0:n])
    for (int x = 0; x < n; ++x){
        #pragma acc atomic
            c = c + a[x] + b[x];
    }

    real_t host_c = 0;
    for (int x = 0; x < n; ++x){
        host_c += a[x] + b[x];
    }

    if (fabs(host_c - c) > PRECISION){
        err = 1;
    }

    #pragma acc exit data copyin(c)
    free(a);
    free(b);

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