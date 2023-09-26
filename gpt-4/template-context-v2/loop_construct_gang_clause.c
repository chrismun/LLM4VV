#include "acc_testsuite.h"
#include <openacc.h>

#ifndef T1
//T1:loop construct gang clause,V:2.7-3.3
int test1(){
    int err = 0;
    float arr[NUM_ELEMS];
    float gain = (float)rand() / RAND_MAX;

    #pragma acc parallel copy(arr)
    {
        #pragma acc loop gang
        for(int i = 0; i < NUM_ELEMS; i++)
        {
            arr[i] = gain * i;
        }
    }

    for( int i = 0; i < NUM_ELEMS; i++ )
    {
        if(arr[i] != gain * i){
            err = 1;
        }
    }

    return err;
}
#endif

int main(){
    srand(SEED);
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