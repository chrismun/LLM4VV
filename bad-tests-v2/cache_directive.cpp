#include "acc_testsuite.h"

#define LENGTH 1024

#ifndef T1
/*T1:cache directive,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);

    float arr[LENGTH] = {0};

    #pragma acc data copy(arr)
    {
        #pragma acc parallel loop
        for(int i = 0; i < LENGTH; ++i){
            arr[i] = rand() / (float)RAND_MAX;
        }
        
        #pragma acc parallel loop cache(arr[0:LENGTH])
        for(int i = 1; i < LENGTH; ++i) {
            arr[i] = arr[i] * arr[i - 1];
            
            if (arr[i] > 1){
                err = 1;
            }
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