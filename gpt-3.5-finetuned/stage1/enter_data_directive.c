#include "acc_testsuite.h"
#ifndef T1
//T1:enter data directive,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    int *a = (int *)malloc(10 * sizeof(int));
    for (int x = 0; x < 10; ++x){
        a[x] = 1;
    }

    #pragma acc enter data copyin(a[0:10])
    #pragma acc parallel loop
    for (int x = 0; x < 10; ++x){
        a[x] = a[x] + 1;
    }

    #pragma acc exit data copyout(a[0:10])

    for (int x = 0; x < 10; ++x){
        err += a[x] - 1;
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