#include "acc_testsuite.h"
#ifndef T1
/*T1:loop construct auto clause,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);
    float a[N];
    float b = (float)rand() / (float)RAND_MAX;
    
    #pragma acc parallel copy(a) 
    {
        #pragma acc loop auto
        for(int i = 0; i < N; i++) {
            a[i] = (float)i + b;
        }
    }

    #pragma acc parallel copy(a) 
    {
        #pragma acc loop auto
        for(int i = 0; i < N; i++) {
            if(a[i] != (float)i + b) {
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