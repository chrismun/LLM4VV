#include "acc_testsuite.h"

// T1:acc unmap data,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    int size = 1024;
    float *a = (float*)malloc(size * sizeof(float));
    float *b = (float*)malloc(size * sizeof(float));
    
    // Initialize data
    for(int i = 0; i < size; i++){
        a[i] = rand() / (float)RAND_MAX;
        b[i] = rand() / (float)RAND_MAX;
    }
    
    #pragma acc data copyin(a[0:size], b[0:size])
    {
        #pragma acc unmap_data(a, b)
    }

    // Check if data is correctly unmapped
    if(acc_is_present(a, size * sizeof(float)) || acc_is_present(b, size * sizeof(float))){
        err = 1;
    }

    free(a);
    free(b);
    
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