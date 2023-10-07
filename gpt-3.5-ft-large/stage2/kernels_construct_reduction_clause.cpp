#include "acc_testsuite.h"
#ifndef T1
//T1:kernels construct reduction clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    int material;
    int a[10];
    material = 45;
    for (int x = 0; x < 10; ++x){
	a[x] = 0;
    }
    #pragma acc data copy(a[0:10])
    {
        #pragma acc kernels loop reduction(+:a[0:10])
        for (int x = 0; x < n; ++x){
            a[x] += material;
        }
    }
    for (int x = 0; x < 10; ++x){
        if(a[x] != material && a[x] != 0){
            err += 1;
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