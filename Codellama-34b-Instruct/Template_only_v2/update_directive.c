#include "acc_testsuite.h"

#ifndef T1
//T1:update directive,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    int a[10];
    int b[10];
    int c[10];

    #pragma acc parallel loop
    for (int i = 0; i < 10; i++) {
        a[i] = i;
        b[i] = i;
        c[i] = i;
    }

    #pragma acc update(a[0:10], b[0:10], c[0:10])

    for (int i = 0; i < 10; i++) {
        if (a[i] != b[i] || a[i] != c[i]) {
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