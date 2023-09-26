#include "acc_testsuite.h"
#include <stdio.h>

#ifndef T1
/*T1:wait directive,V:2.0-2.7*/

int test1(){
    int err = 0;
    volatile int a = 10;
    volatile int b = 5;
    int ref, compute;

    // Reference Value
    ref = a + b;

#pragma acc parallel num_gangs(1) vector_length(32) async(1)
    {
        b = a + b;
    }


#pragma acc wait async(2)

#pragma acc parallel present(b) async(2)
    {
        a = b;
    }

#pragma acc wait 

    if(a != ref){
        err = 1;
    }

    return err;
}
#endif

int main(){
    int errcode = 0;
    int failed;
#ifndef T1
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    // If there is failed test, code will return non-zero error code
    if (failed != 0){
        errcode = errcode + (1 << 0);
    }
#endif
    return errcode;
}