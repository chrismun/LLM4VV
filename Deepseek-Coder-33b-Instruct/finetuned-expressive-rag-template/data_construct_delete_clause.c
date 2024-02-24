#include <stdlib.h>
#include <stdio.h>
#include "acc_testsuite.h"

#ifndef T1
//T1:data construct delete clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    int *ptr = (int*)malloc(sizeof(int));
    *ptr = 10;

    #pragma acc data create(ptr[0:1])
    {
        ptr[0] = 20;
    }

    if (ptr[0] != 20) {
        err++;
        printf("Error: ptr[0] is not 20\n");
    }

    #pragma acc exit data delete(ptr[0:1]) finalize

    if (ptr[0] != 20) {
        err++;
        printf("Error: ptr[0] is not 20 after delete\n");
    }

    free(ptr);

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