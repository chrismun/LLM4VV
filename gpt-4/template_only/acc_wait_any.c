#include "openacc.h"
#include "acc_testsuite.h"
#include <stdlib.h>

#ifndef T1
//T1:acc wait any,V:2.7-3.3
int test1(){
    int err = 0;
    int num_gangs = 10, num_workers = 5, vector_length = 32;

    float *a = (float*)malloc(sizeof(float)*num_gangs*num_workers*vector_length);
    float *b = (float*)malloc(sizeof(float)*num_gangs*num_workers*vector_length);

    for(int i=0; i<num_gangs*num_workers*vector_length; i++)
    {
        a[i] = i;
        b[i] = 0.0;
    }
    
    #pragma acc parallel num_gangs(num_gangs) num_workers(num_workers) vector_length(vector_length)
    {
        #pragma acc loop gang worker vector
        for(int i=0; i<num_gangs*num_workers*vector_length; i++)
        {
            b[i] = __acc_test_wait_any(a[i]);
            if(a[i] != b[i])
                err = 1;
        }
    }
    
    free(a);
    free(b);

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