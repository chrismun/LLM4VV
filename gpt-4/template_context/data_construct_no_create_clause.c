#include "acc_testsuite.h"

#ifndef T1
int test1(){
    int err = 0;
    srand(SEED);
    
    // Array on the host
    float* h_array = (float*)malloc(N * sizeof(float));
    for(int i = 0; i < N; i++) {
       h_array[i] = rand() / (float)RAND_MAX;
    }
      
    // Array on the device 
    float* d_array;
    #pragma acc enter data create(d_array[0:N])
        
    // Now we do some operation on the device with a data construct and no_create clause
    #pragma acc parallel loop no_create(h_array)
    for (int i = 0; i < N; i++) {
        d_array[i] = h_array[i] * 2.0f;
    }

    // Now, we want to make sure that the original host array hasn't been modified.
    for(int i = 0; i < N; i++) {
        if(abs(h_array[i] - d_array[i]) > PRECISION) {
            err = 1;
        }
    }
    
    // Free and prevent memory leaks
    #pragma acc exit data delete(d_array)
    free(h_array);

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