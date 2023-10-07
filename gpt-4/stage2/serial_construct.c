#include "acc_testsuite.h"
#include <stdlib.h>

#ifndef T1
/*T1:serial construct,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);
    int a = 10;
    int b[10];
    int actual[10];
    int expected[10];

    //initialize arrays on host side
    for (int i = 0; i < a; ++i){
        b[i] = rand() % 100;
        expected[i] = b[i] * 2;
    }

    //compute on the device
    #pragma acc serial copyin(b[0:a]) copyout(actual[0:a])
    for (int i = 0; i < a; ++i) {
        actual[i] = b[i] * 2;
    }

    //compare results
    for (int i = 0; i < a; ++i) {
        if (actual[i] != expected[i]) {
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