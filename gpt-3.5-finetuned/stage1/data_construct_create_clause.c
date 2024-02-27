#include "acc_testsuite.h"
#ifndef T1
//T1:data,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    if(a == NULL){
        err = err + 1;
    }
    real_t * b = (real_t *)malloc(n * sizeof(real_t));
    if(b == NULL){
        err = err + 1;
    }

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(n);
    }

    #pragma acc data create(b[0:n]) copyin(a[0:n])
    {
        #pragma acc parallel
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                b[x] = a[x];
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