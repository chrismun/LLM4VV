#include <stdlib.h>
#include <stdio.h>
#include "acc_testsuite.h"

#ifndef T1
//T1:serial, construct default clause, V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    int a = 10;
    int b = 0;

    #pragma acc serial default(none) copyin(a) private(b)
    {
        b = a + 5;
    }

    // Since `b` is private, its modifications inside the serial region should not affect its value outside
    if (b != 0) {
        err += 1;
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