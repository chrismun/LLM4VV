#include "acc_testsuite.h"

#ifndef T1
//T1:data construct,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    int *a = (int *)malloc(sizeof(int) * 10);
    int *b = (int *)malloc(sizeof(int) * 10);

    #pragma acc data copy(a[0:10], b[0:10])
    {
        #pragma acc parallel loop
        for (int i = 0; i < 10; i++) {
            a[i] = i;
            b[i] = i * 2;
        }
    }

    for (int i = 0; i < 10; i++) {
        if (a[i] != i || b[i] != i * 2) {
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