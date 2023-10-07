#include "acc_testsuite.h"
#ifndef T1
//T1:acc wait async,V:2.7-3.3
int test1(){
    int err = 0;
    float a[100], b[100], ref[100];
    
    //Initialise arrays
    for(int i = 0; i < 100; ++i){
        a[i] = (float)rand() / RAND_MAX;
        b[i] = (float)rand() / RAND_MAX;
        ref[i] = a[i] + b[i];
    }
    
    //Compute on device
    #pragma acc parallel loop async
    for(int i = 0; i < 100; ++i){
        a[i] += b[i];
    }
    
    #pragma acc wait //wait for completion of the previous async compute
    
    //Check results
    for(int i = 0; i < 100; ++i){
        if(a[i] != ref[i]){
            err = 1; //error if any result is incorrect
        }
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