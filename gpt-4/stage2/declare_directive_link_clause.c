#include "acc_testsuite.h"

#ifndef SIXTEEN_MB
#define SIXTEEN_MB 16777216
#endif

#pragma acc declare link(x) /* declare directive link clause */
int x[SIXTEEN_MB];

int test1(){
    int err = 0;
    srand(SEED);

    /* Initialize host data */
    for (int i = 0; i < SIXTEEN_MB; i++){
        x[i] = rand() % SIXTEEN_MB;
    }
    /* Transfer data to device */
    #pragma acc enter data copyin(x[:SIXTEEN_MB])

    /* Run on device and check each element */
    #pragma acc parallel loop reduction(max:err)
    for (int i = 0; i < SIXTEEN_MB; i++){
        if (x[i] != i)
            err = 1; 
    }
    /* Transfer data back to host */
    #pragma acc exit data delete(x[:SIXTEEN_MB])

    return err;
}

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