#include <stdlib.h>
#include <openacc.h>
#include "acc_testsuite.h"

#ifndef T1
//T1: variable implicit data attributes, V: 2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    unsigned int* vector = (unsigned int*)malloc(sizeof(unsigned int)*1024*1024);

    #pragma acc parallel loop copy(vector[0:1024*1024])
    for(unsigned int i = 0; i < 1024*1024; ++i){
         vector[i] = i;
    }

    // Check if vector[i] == i for all i in [0, 1024*1024)
    for(unsigned int i = 0; i < 1024*1024; ++i){
        if (vector[i] != i){
            err = 1;
            break;
        }
    }

    free(vector);
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