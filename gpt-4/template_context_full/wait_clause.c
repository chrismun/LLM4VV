#include "acc_testsuite.h"
#include <stdlib.h>
#include <stdio.h>

#ifndef T1
/*T1:wait clause,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);
    int data_host[1024], data_device[1024];
    
    for(int i = 0; i < 1024; i++)
        data_host[i] = rand() % 100;
    
    #pragma acc data copy(data_host[0:1024]) async(1)
    #pragma acc kernels present(data_host[0:1024]) async(1)
    for(int i = 0; i < 1024; i++)
        data_device[i] = data_host[i] * 2;

    #pragma acc wait

    for(int i = 0; i < 1024; i++)
        if(data_host[i] * 2 != data_device[i])
            err = 1; // if there is a mistake in copying

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