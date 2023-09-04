#include "acc_testsuite.h"
#ifndef T1
//T1:init,V:1.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    int * a = (int *)malloc(n * sizeof(int));

    #pragma acc data copyout(a[0:n])
    {
        #pragma acc init
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                a[x] = 0;
            }
        }
    }

    for (int x = 0; x < n; ++x){
        if (a[x] != 0){
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