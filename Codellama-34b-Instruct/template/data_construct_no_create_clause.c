#include "acc_testsuite.h"

#ifndef T1
//T1:data construct no_create clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    int *a = (int *)malloc(10 * sizeof(int));
    int *b = (int *)malloc(10 * sizeof(int));

    #pragma acc data no_create(a, b)
    {
        #pragma acc parallel loop
        for (int i = 0; i < 10; i++) {
            a[i] = i;
            b[i] = i;
        }
    }

    if (a[0] != 0 || b[0] != 0) {
        err = 1;
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