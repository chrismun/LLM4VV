#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    int *a = (int *)malloc(10 * sizeof(int));
    int *b = (int *)malloc(10 * sizeof(int));

    #pragma acc parallel loop self(a[0:10])
    for (int i = 0; i < 10; i++) {
        a[i] = i;
    }

    #pragma acc parallel loop self(b[0:10])
    for (int i = 0; i < 10; i++) {
        b[i] = i;
    }

    #pragma acc parallel loop self(a[0:10], b[0:10])
    for (int i = 0; i < 10; i++) {
        a[i] += b[i];
    }

    #pragma acc parallel loop self(a[0:10])
    for (int i = 0; i < 10; i++) {
        if (a[i] != i + i) {
            err = 1;
            break;
        }
    }

    free(a);
    free(b);

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