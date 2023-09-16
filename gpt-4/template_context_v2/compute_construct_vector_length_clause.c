#include "acc_testsuite.h"
#include <stdlib.h>
#include <openacc.h>

#ifndef T1
//T1:compute construct vector_length clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    unsigned int vector_length = 128;
    float* a = (float*)malloc(vector_length * sizeof(float));

    for (unsigned int x = 0; x < vector_length; ++x){
        a[x] = x;
    }

    #pragma acc parallel copy(a[0:vector_length]) vector_length(vector_length)
    {
        #pragma acc loop vector
        for(unsigned int x = 0; x < vector_length; ++x){
            a[x] = a[x]*2;
        }
    }

    for(unsigned int x = 0; x < vector_length; ++x){
        if(a[x] != x*2){
            err = 1;
        }
    }

    free(a);

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