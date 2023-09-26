#include "acc_testsuite.h"
#ifndef T1
//T1:wait directive,V:2.7-3.3
int test1(){
    int err = 0;
    int x = 10;

    #pragma acc parallel num_gangs(1) num_workers(1)
    #pragma acc loop gang worker
    for (int i = 0; i < 10; i++){
        x--;
    }

    #pragma acc wait
    if (x != 0){
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
    for (int i = 0; i < NUM_TEST_CALLS; i++){
        failed += test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}