#include "acc_testsuite.h"
#ifndef T1
//T1:kernels,loop,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    real_t * restrict a = new real_t[4096];
    real_t * restrict b = new real_t[4096];

    for (int x = 0; x < 4096; ++x){
        a[x] = 0;
    }

    #pragma acc data copy(a[0:4096]) copyout(b[0:4096])
    {
        #pragma acc kernels loop default(present)
        for (int x = 0; x < 4096; ++x){
            b[x] = a[x];
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