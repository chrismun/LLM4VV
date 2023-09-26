#include "acc_testsuite.h"
#include <stdlib.h>
#include <stdio.h>

#ifndef T1
//T1:data construct attach clause,V:2.7-3.3
int test1() {
    int err = 0;
    int length = 10;
    srand(SEED);
    
    int* pointerA = (int*)malloc(length * sizeof(int));
    int* pointerB = (int*)malloc(length * sizeof(int));

    // initialization
    for(int i = 0; i < length; i++) {
        pointerA[i] = rand() % 100;
        pointerB[i] = 0;
    }

    #pragma acc enter data create(pointerB[0:length])
    #pragma acc data attach(pointerB)
    #pragma acc parallel loop copy(pointerA[0:length])
    for(int i = 0; i < length; i++) {
        pointerB[i] = pointerA[i];
    }
    #pragma acc exit data detach(pointerB)

    // validate data
    for(int i = 0; i < length; i++) {
        if(pointerA[i] != pointerB[i]){
            err = 1;
            break;
        }
    }

    // free memory
    free(pointerA);
    free(pointerB);

    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed;
#ifndef T1
    failed = 0;
    for(int x = 0; x < NUM_TEST_CALLS; ++x){
        failed += test1();
    }
    if(failed != 0){
        failcode += (1 << 0);
    }
#endif
    return failcode;
}