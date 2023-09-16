#include "acc_testsuite.h"
#ifndef T1
//T1:set directive,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    int a = 0;
    int b = 1;

    #pragma acc set device_type(nvidia)
    #pragma acc parallel num_gangs(1) num_workers(1) vector_length(1)
    {
        a = a + b;

        if (a != 1)
            err = 1;
    }

    #pragma acc set device_type(any)
    #pragma acc parallel num_gangs(1) num_workers(1) vector_length(1)
    {
        a = a + b;

        if (a != 2)
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