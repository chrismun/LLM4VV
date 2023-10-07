#include "acc_testsuite.h"
#include <iostream>

#ifndef T1
/*T1:acc wait any,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);
    int asyncList[2];
    int numAsync = 2;
    
    #pragma acc parallel num_gangs(100) async(asyncList[0])
    {
        // Arbitrary compute task
        double result = 0;
        for(int i=0; i<10000; i++) 
            result += i;
    }
    
    #pragma acc parallel num_gangs(200) async(asyncList[1])
    {
        // Another arbitrary compute task
        double result = 0;
        for(int i=0; i<50000; i++)
            result += i;
    }

    int asyncId = acc_wait_any(numAsync, asyncList);

    if(asyncId < 0 || asyncId >= numAsync){
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