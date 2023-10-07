#include "acc_testsuite.h"
#ifndef T1
//T1:acc wait,V:2.7-3.3
int test1(){
    int err = 0;
    int async_id = 1;
    int async_id_2 = 2;

    #pragma acc enter data copyin(async_id)
    #pragma acc enter data copyin(async_id_2)

    #pragma acc parallel async(async_id)
    {
        // Do some work
    }

    #pragma acc parallel async(async_id_2)
    {
        // Do some work
    }

    #pragma acc wait(async_id)
    #pragma acc wait(async_id_2)

    #pragma acc exit data delete(async_id)
    #pragma acc exit data delete(async_id_2)

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