#include "acc_testsuite.h"
#include <stdlib.h>

//T1:compute construct async clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    int a = rand()%100; // getting any random number between 0 to 99
    int b = 0;

    #pragma acc parallel async copyin(a) copyout(b)
     {
        b = a;
     }
    #pragma acc wait
    if(a!=b){
        err = 1;
    }

    return err;
}

int main(){
    int failcode = 0;
    int failed;

    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
    
    return failcode;
}