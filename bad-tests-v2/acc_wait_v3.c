#include "acc_testsuite.h"
#ifndef T1
// T1:acc wait,V:2.7-3.3
int test1(){
    int err = 0;
    int a=5, b=10;
    srand(SEED);

    #pragma acc parallel copyin(a,b)
    {
        #pragma acc loop independent
        for (int i =0; i< 10; i++){
            a += b;
        }
    }
    
    #pragma acc wait 

    #pragma acc parallel copy(a)
    {
        #pragma acc loop independent
        for (int i =0; i< 10; i++){
            a += b;
        }
    }

    if(a != 105) {
        err = 1;  // Error if 'a' is not equal to 105
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