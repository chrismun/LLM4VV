#include "acc_testsuite.h"
#ifndef T1
//T1:declare,data,data-region,dev_resident,V:1.0-2.7
int test1(){
    int err = 0;
    real_t* a = (real_t*)malloc(n * sizeof(real_t));
    real_t* b = (real_t*)malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        a[x] = (real_t) x;
    }

    #pragma acc data copyin(a[0:n])
    {
        #pragma acc parallel
        {
            real_t sum = 0.0;
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                sum += a[x];
            }

            #pragma acc loop
            for (int x = 0; x < n; ++x){
                b[x] = sum;
            }
        }
    }

    for (int x = 0; x < n; ++x){
        if (b[x] != (real_t)(n*x)){
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
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}