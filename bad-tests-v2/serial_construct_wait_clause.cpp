#include "acc_testsuite.h"
#include <stdlib.h>
#include <time.h>

#ifndef T1
/*T1:serial construct,wait clause,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(time(0)); 

    int a[10000]; 
    int b[10000];
    
    #pragma acc data create(a[0:10000])
    {
        #pragma acc serial
        for(int i = 0; i < 10000; i++){
            a[i] = rand();
        }

        #pragma acc wait
     
        #pragma acc serial 
        for(int i = 0; i < 10000; i++){
            b[i] = a[i];
        }
    }

    for(int i = 0; i < 10000; i++){
        if(a[i] != b[i]){
            err = 1;
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