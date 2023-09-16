#include "acc_testsuite.h"
#include <stdlib.h>

#ifndef T1
//T1:data construct detach clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    int length = 1<<10;
    float* a = (float*)malloc(length*sizeof(float));
    float* b = (float*)malloc(length*sizeof(float));
    float* c = (float*)malloc(length*sizeof(float));

    for(int i=0; i<length; ++i){
        a[i] = (float)rand()/(float)RAND_MAX;
        b[i] = (float)rand()/(float)RAND_MAX;
    }

    #pragma acc data copyin(a[0:length], b[0:length]) copy(c[0:length])
    {
        #pragma acc parallel loop
        for(int i=0; i<length; ++i){
            c[i] = a[i] + b[i];
        }        
    }

    for(int i=0; i<length; ++i){
        if(fabs(c[i] - (a[i] + b[i])) > PRECISION)
            err = 1;
    }
    
    free(a);
    free(b);
    free(c);

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