#include "openacc.h"
#include "acc_testsuite.h"
#ifndef T1
/*T1:data construct detach clause,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);
    float* host_array;
    float* dev_array;

    host_array = (float*)malloc(SIZE * sizeof(float*));
    for(int i=0; i<SIZE; i++) {
        host_array[i] = rand();
    }

    #pragma acc enter data copyin(host_array[0:SIZE])
    #pragma acc parallel loop present(host_array[0:SIZE]) 
    for(int i=0; i<SIZE; i++) { 
        dev_array[i] = host_array[i] * 2.0; 
    }
    
    #pragma acc exit data detach(host_array[0:SIZE])
     
    // Detach action should have moved memory from device to host, so it should
    // no longer exist on the device.
    if(acc_is_present(host_array, SIZE * sizeof(float)) != 0){
        err = 1;
    }

    free(host_array);
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