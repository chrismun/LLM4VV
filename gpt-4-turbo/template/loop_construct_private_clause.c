#include <stdlib.h>
#include <stdio.h>
#include "acc_testsuite.h"
#ifndef T1
//T1:runtime,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    const int length = 128;
    int *results = (int*)malloc(sizeof(int)*length);

    #pragma acc parallel num_gangs(1) vector_length(128)
    {
        int private_var = 0; // This variable is supposed to be private to each thread

        #pragma acc loop private(private_var)
        for (int i = 0; i < length; ++i){
            private_var = i;
            results[i] = private_var;
        }
    }

    for (int i = 0; i < length; ++i){
        if (results[i] != i){
            err += 1;
        }
    }
    
    free(results);
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