#include "acc_testsuite.h"
#ifndef T1
//T1:async clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    int size = 10000;
    int *a = (int*)malloc(sizeof(int)*size);
    int *c = (int*)malloc(sizeof(int)*size);
    for (int x = 0; x < size; ++x) {
        a[x] = rand() / (int)RAND_MAX;
        c[x] = 0;
    }

    #pragma acc data copyin(a[0:size]) copy(c[0:size])
    {
    #pragma acc kernels async
        for (int x = 0; x < size; ++x) {
            c[x] = a[x] * 2;
        }
    #pragma acc wait
    }

    for (int x = 0; x < size; ++x) {
        if (abs(c[x] - a[x] *2) > PRECISION) {
            err = 1;
            break;
        }
    }

    free(a);
    free(c);

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