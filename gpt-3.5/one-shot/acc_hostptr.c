#include "acc_testsuite.h"
#ifndef T1
//T1:data,data-region,V:1.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    int * a = (int *)malloc(N * sizeof(int));
    int * b = (int *)malloc(N * sizeof(int));

    #pragma acc data copyin(a[0:N]) create(b[0:N])
    {
        #pragma acc parallel
        {
            #pragma acc loop
            for (int x = 0; x < N; ++x){
                b[x] = a[x];
            }
        }
    }

    for (int x = 0; x < N; ++x){
        if (b[x] != a[x]){
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