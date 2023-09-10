#include "acc_testsuite.h"
#ifndef T1
/*T1:kernels construct wait clause,V:2.0-2.7*/
int test1(){
    int err = 0;
    
    const int size = 100000;
    float* hst_data = (float*)malloc(size * sizeof(float));
    float* hst_result = (float*)malloc(size * sizeof(float));
    for(int idx = 0; idx < size; idx++){
        hst_data[idx] = rand()/(float)RAND_MAX;
    }
    
    //OpenACC compute kernel
    #pragma acc kernels async(1)
    for(int idx = 0; idx < size; idx++){
        hst_result[idx] = hst_data[idx] * 2.0;
    }
    
    // wait for device computation
    #pragma acc wait(1)

    // Error checking
    for(int idx = 0; idx < size; idx++){
        if(hst_result[idx] != hst_data[idx] * 2.0)
            err += 1;
    }
    
    // clean dynamically allocated memory
    free(hst_data);
    free(hst_result);

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