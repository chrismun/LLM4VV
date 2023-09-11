#include "acc_testsuite.h"

#ifndef T1
//T1:kernels construct reduction clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    int a[100];
    int b[100];
    int c[100];

    #pragma acc kernels reduction(+:a,b,c)
    {
        for (int i = 0; i < 100; i++) {
            a[i] = i;
            b[i] = i;
            c[i] = i;
        }
    }

    for (int i = 0; i < 100; i++) {
        if (a[i] != b[i] + c[i]) {
            err = 1;
            break;
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