#include "acc_testsuite.h"

#ifndef T1
// T1: async-test,async,device,V:2.6-2.7
int test1(){
    int err = 0;
    int n = 1000;

    real_t *a = (real_t *)malloc(n * sizeof(real_t));
    real_t *b = (real_t *)malloc(n * sizeof(real_t));

    for (int i = 0; i < n; ++i){
        a[i] = i;
        b[i] = 0.0;
    }

    #pragma acc enter data copyin(a[0:n]) create(b[0:n])

    #pragma acc parallel async(1)
    {
        #pragma acc loop
        for (int i = 0; i < n; ++i){
            b[i] = a[i];
        }
    }

    int asyncStatus = acc_async_test(1);

    #pragma acc exit data copyout(b[0:n]) delete(a[0:n])

    if (asyncStatus != 1){
        err += 1;
    }

    for (int i = 0; i < n; ++i){
        if (b[i] != a[i]){
            err += 1;
            break;
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
    for (int i = 0; i < NUM_TEST_CALLS; ++i){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif

    return failcode;
}