#include "acc_testsuite.h"
#include <stdlib.h>
#include <stdio.h>

#ifdef _OPENACC
#pragma acc declare device_resident(data)
#endif

#ifndef T1
/*T1: declare directive device_resident clause, V:2.0-2.7*/
int test1(){
    int err = 0;
    int *data = (int*)malloc(10 * sizeof(int));
    srand(SEED);

    #pragma acc parallel copyout(data[0:10])
    {
        for(int i=0; i<10; i++){
            data[i] = i;
        }
    }

    for(int i=0; i<10; i++){
        if(data[i] != i) {
            err = 1;
            break;
        }
    }

    free(data);

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