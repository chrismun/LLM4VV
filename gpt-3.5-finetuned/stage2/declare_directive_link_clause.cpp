#include "acc_testsuite.h"
#ifndef T1
//T1:declare directive link clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    int * p;
    #pragma acc enter data copyin(p[0:10])
    #pragma acc declare copyin(p[0:10])
    p = (int *)malloc(n * sizeof(int));
    if (p == NULL) {
        for (int x = 0; x < 10; ++x){
            p[x] = 1;
        }
    }
    for (int x = 0; x < 10; ++x){
        if (p[x] != 1){
            err += 1;
        }
    }
    #pragma acc exit data copyout(p[0:10])

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