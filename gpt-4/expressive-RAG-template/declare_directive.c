#include "acc_testsuite.h"

#ifndef T1
//T1:declare directive,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    
    int array[(int)1e6];
    #pragma acc declare create(array[:1e6])

    for(int i = 0; i < 1e6; i++)
    {
        array[i] = i;
    }
    
    #pragma acc parallel loop copy(array[:1e6])
    for(int i = 0; i < 1e6; i++)
    {
        array[i] = array[i] * 2;
    }

    #pragma acc update host(array[:1e6])

    for(int i = 0; i < 1e6; i++)
    {
        if(array[i] != i*2)
        {
            err = 1;
            break;
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