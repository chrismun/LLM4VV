#include "acc_testsuite.h"
#include <stdlib.h>

#ifndef T1
/* Validation of Parallel Construct firstprivate Clause */
int test1(){
    int err = 0;
    srand(SEED);

    int a = rand();
    int b[1];

    #pragma acc parallel firstprivate (a)
    {
        b[0] = a;
    }

    if (a != b[0]){
        err = 1;
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