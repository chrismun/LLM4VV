#include "acc_testsuite.h"
#ifndef T1
//T1:compute construct private clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    int a[SIZE], b[SIZE];
    for (int i = 0; i < SIZE; ++i) {
        a[i] = (rand() % SIZE);
    }

    #pragma acc parallel loop private(b)
    for (int i = 0; i < SIZE; i++) {
        b[i] = a[i>0 ? i-1 : 0];
        a[i] = b[i>0 ? i-1 : 0] + b[i];
    }

    for(int i = 1; i < SIZE; i++) {
        if (a[i] != (2 * a[i-1]) + a[i]) {
            err = 1;
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