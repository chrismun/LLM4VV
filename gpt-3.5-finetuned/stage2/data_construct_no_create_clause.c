#include "acc_testsuite.h"
#ifndef T1
//T1:data construct no_create clause,V:2.7-3.3
int test1(){
    int err = 0;
    int* a = (int *)malloc(k * sizeof(int));
    int* b = (int *)malloc(k * sizeof(int));
    int* c = (int *)malloc(k * sizeof(int));

    for (int x = 0; x < k; ++x){
        a[x] = 1;
        b[x] = 1;
        c[x] = 0;
    }

    #pragma acc data copyin(a[0:k], b[0:k]) no_create(c[0:k])
    {
        #pragma acc parallel
        {
            #pragma acc loop
            for (int x = 0; x < k; ++x){
                c[x] += a[x] + b[x];
            }
        }
    }

    for (int x = 0; x < k; ++x){
        if (fabs(c[x] - 2) > 2*PRECISION){
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