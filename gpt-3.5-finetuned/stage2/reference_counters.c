#include "acc_testsuite.h"
#ifndef T1
//T1:reference counters,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    unsigned int * a = (unsigned int *)malloc(n * sizeof(unsigned int));
    for (int x = 0; x < n; ++x){
        a[x] = 0;
    }

    #pragma acc enter data create(a[0:n])
    #pragma acc update device(a[0:n])
    #pragma acc exit data delete(a[0:n])

    for (int x = 0; x < n; ++x){
        if (a[x] != 0){
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