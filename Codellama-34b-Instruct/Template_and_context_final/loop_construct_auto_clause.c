#include "acc_testsuite.h"

#ifndef T1
//T1:loop construct auto clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    int data[100];
    for (int i = 0; i < 100; i++) {
        data[i] = rand() % 100;
    }

    #pragma acc parallel loop auto
    for (int i = 0; i < 100; i++) {
        data[i] += 1;
    }

    for (int i = 0; i < 100; i++) {
        if (data[i] != i + 1) {
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