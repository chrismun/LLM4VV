#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Data clause test
    int *a = (int *)malloc(sizeof(int) * 10);
    int *b = (int *)malloc(sizeof(int) * 10);
    int *c = (int *)malloc(sizeof(int) * 10);

    #pragma acc data copy(a[0:10]) copyin(b[0:10]) copyout(c[0:10])
    {
        #pragma acc parallel loop
        for (int i = 0; i < 10; i++) {
            a[i] = b[i] + c[i];
        }
    }

    for (int i = 0; i < 10; i++) {
        if (a[i] != b[i] + c[i]) {
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