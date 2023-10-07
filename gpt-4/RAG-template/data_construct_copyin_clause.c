#include "acc_testsuite.h"
#include <stdlib.h>

//T1:data construct copyin clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    int a = 10;
    int b[10];

    #pragma acc data copyin(a)
    {
        #pragma acc parallel loop
        for (int i = 0; i < 10; i++) {
            b[i] = a;
        }
    }

    for (int i = 0; i < 10; i++) {
        if (b[i] != a) {
            err = 1;
            break;
        }
    }

    return err;
}

int main(){
    int failcode = 0;
    int failed;
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
    return failcode;
}