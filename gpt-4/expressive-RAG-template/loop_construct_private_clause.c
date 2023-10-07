#include "acc_testsuite.h"
#ifndef T1
//T1:loop construct private clause,V:2.7-3.3
int test1(){
    int i;
    int err = 0;
    srand(SEED);

    int num = 100;  // number of iteration
    int result = 0;
    int host_result = 0;

    #pragma acc parallel loop reduction(+:result) private(i)
    for(i = 0; i < num; i++){
        result += i;
    }
    
    for(i = 0; i < num; i++){
        host_result += i;
    }

    // compare host result with target result
    if(result != host_result){
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