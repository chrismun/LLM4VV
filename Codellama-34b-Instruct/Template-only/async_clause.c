#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    int *a = (int *)malloc(10 * sizeof(int));
    int *b = (int *)malloc(10 * sizeof(int));
    int *c = (int *)malloc(10 * sizeof(int));

    #pragma acc parallel loop async(a)
    for (int i = 0; i < 10; i++) {
        a[i] = i;
    }

    #pragma acc parallel loop async(b)
    for (int i = 0; i < 10; i++) {
        b[i] = i;
    }

    #pragma acc parallel loop async(c)
    for (int i = 0; i < 10; i++) {
        c[i] = i;
    }

    #pragma acc wait

    for (int i = 0; i < 10; i++) {
        if (a[i] != i || b[i] != i || c[i] != i) {
            err = 1;
            break;
        }
    }

    free(a);
    free(b);
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