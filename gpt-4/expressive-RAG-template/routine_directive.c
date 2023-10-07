#include "acc_testsuite.h"
#ifndef T1
//T1:routine directive,V:2.7-3.3

//A simple child function to be used with routine directive
#pragma acc routine seq
int addNums(int a, int b){
    return a+b;
}


int test1(){
    int err = 0;
    srand(SEED);

    int a = rand() % 10;
    int b = rand() % 10;

    int result;
        
    #pragma acc parallel
    {
        result = addNums(a, b);
    }

    // Validate if return value from routine is correct
    if(result != (a + b)){
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