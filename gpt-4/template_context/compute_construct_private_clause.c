#include "openacc.h"
#include "acc_testsuite.h"
#ifndef T1
//T1:compute construct private clause,V:2.7-3.3
int test1(){
    int err = 0;
    int len = 100;
    int a[len];
    
    srand(SEED);
    
    for(int i=0; i<len; i++){
        a[i] = rand()%10;
    }
    
    int original = a[0];
    
    #pragma acc parallel private(a)
    {
        a[0] += 1;
    }
        
    if(a[0] != original){
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